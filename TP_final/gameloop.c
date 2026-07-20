/*
 * gameloop.c
 *
 * Ver gameloop.h. Conecta el joystick con el movimiento de la rana y
 * con el dibujado en el display de LEDs. Usa el mismo backend que la
 * version de PC (levelset/checking/frogupdates): aca solo se traduce
 * joystick -> movimientos y estado -> LEDs.
 *
 * Pantallas (espejo de las del front-end de Allegro):
 *   MENU      "FROGGER" en marquesina. Switch: jugar. Abajo: salir.
 *   PLAYING   el juego. Switch: pausa.
 *   PAUSED    "PAUSA" en marquesina. Switch: seguir. Arriba: reiniciar.
 *             Abajo: abandonar y volver al menu.
 *   INITIALS  solo si el puntaje entra al top 10: elegir 3 iniciales.
 *             Arriba/abajo: cambiar letra. Izq/der: cambiar posicion.
 *             Switch: confirmar.
 *   GAMEOVER  "GAME OVER <puntaje>" en marquesina. Switch: al menu.
 */

#include "gameloop.h"

#include <unistd.h>
#include <stdio.h>

#include "gamestate.h"
#include "checking.h"
#include "entityupdates.h" /* supportDivePhase: parpadeo de tortugas */
#include "frogupdates.h"
#include "levelset.h"
#include "highscores.h"
#include "joystick.h"
#include "joydrv.h"
#include "drawleds.h"
#include "disdrv.h"

/* Ticks de la barra de tiempo para un cruce (a ~20 ticks/seg, ~30 seg;
 * mismo criterio que LEVEL_TIME_TICKS del front-end de Allegro). */
#define LEVEL_TIME_TICKS 600

/* ~20 ticks por segundo. Ajustar segun que tan responsive se sienta el
 * joystick contra que tan rapido corren los autos/troncos. */
#define TICK_US 50000

/* Fila superior de los textos 3x3 (centrados verticalmente). */
#define TEXT_ROW 6

/* Iniciales: columna del primer glifo (3 letras ocupan 11 columnas) y
 * cadencia del parpadeo de la letra activa, en ticks. */
#define INITIALS_X 2
#define INITIALS_BLINK_TICKS 5

typedef enum {
    PI_MENU,
    PI_PLAYING,
    PI_PAUSED,
    PI_INITIALS,
    PI_GAMEOVER
} pi_screen;

static void draw_frame(game_state * game, int time_left)
{
    int i;

    disp_clear();

    for (i = 0; (game->psoport + i)->type != -1; i++) {

        support_entity * s = game->psoport + i;
        dive_phase phase = supportDivePhase(s);

        /* sumergida no se dibuja (se ve el "agua": LED apagado); mientras
         * se hunde parpadea como aviso de que hay que saltar de ahi */
        if (phase == SUPPORT_DIVED || (phase == SUPPORT_SINKING && (s->divetimer / 3) % 2)) {
            continue;
        }

        led_draw_entity(s->startcoord, s->height, s->type);
    }
    for (i = 0; (game->penemies + i)->type != -1; i++) {
        led_draw_entity((game->penemies + i)->startcoord, (game->penemies + i)->height, (game->penemies + i)->type);
    }

    led_draw_frog(game->prana->startcoord, game->prana->height);
    led_draw_lives(game->prana->lives);
    led_draw_time((time_left * (PLAY_FIELD_MAX_X + 1)) / LEVEL_TIME_TICKS);

    disp_update();
}

static void draw_initials(const char * initials, int pos, int blink_on)
{
    disp_clear();

    char shown[4] = {initials[0], initials[1], initials[2], '\0'};

    if (!blink_on) {
        shown[pos] = ' '; /* la letra activa parpadea */
    }

    led_draw_text(shown, INITIALS_X, TEXT_ROW);

    /* subrayado fijo bajo la letra activa, para ubicarse aunque parpadee */
    for (int c = 0; c < 3; c++) {
        dcoord_t coord = {(uint8_t)(INITIALS_X + pos * LED_CHAR_PITCH + c), TEXT_ROW + LED_GLYPH_H + 1};
        disp_write(coord, D_ON);
    }

    disp_update();
}

int run_headless_game(void)
{
    game_state * game = createGame();

    if (game == NULL) {
        return -1;
    }

    disp_init();
    joy_init();

    pi_screen screen = PI_MENU;
    int running = 1;
    int time_left = 0;
    int final_score = 0;
    int prev_sw = 0;

    char initials[4] = "AAA";
    int initials_pos = 0;
    int blink = 0;

    char gameover_msg[32];
    led_scroll marquee;

    led_scroll_start(&marquee, "FROGGER");

    while (running) {

        int sw = joystic_update();
        int sw_press = sw && !prev_sw; /* flanco: recien apretado */
        prev_sw = sw;

        switch (screen) {

        case PI_MENU:
            if (sw_press) {
                if (firstLevel(game) != 0) {
                    endGame(game);
                    return -1;
                }
                time_left = LEVEL_TIME_TICKS;
                screen = PI_PLAYING;
            } else if (isDwn) {
                running = 0; /* unica salida del programa sin cortar la alimentacion */
            } else {
                disp_clear();
                if (led_scroll_step(&marquee, TEXT_ROW)) {
                    led_scroll_start(&marquee, "FROGGER");
                }
                disp_update();
            }
            break;

        case PI_PLAYING: {

            if (sw_press) {
                led_scroll_start(&marquee, "PAUSA");
                screen = PI_PAUSED;
                break;
            }

            if (isUp)        frogStepUp(game);
            else if (isDwn)  frogStepDown(game);
            else if (isRgt)  frogStepRight(game);
            else if (isLft)  frogStepLeft(game);

            int result = LEVEL_RUNNING;

            if (--time_left <= 0) {
                /* se acabo la barra de tiempo: cuesta una vida */
                result = loseLife(game) ? GAME_OVER : FROG_DIED;
            }

            if (result == LEVEL_RUNNING) {
                result = updateLevel(game, time_left, LEVEL_TIME_TICKS);
            }

            if (result == GAME_OVER) {

                final_score = game->score;
                sprintf(gameover_msg, "GAME OVER %d", final_score);

                if (hsQualifies(final_score)) {
                    initials[0] = initials[1] = initials[2] = 'A';
                    initials_pos = 0;
                    blink = 0;
                    screen = PI_INITIALS;
                } else {
                    led_scroll_start(&marquee, gameover_msg);
                    screen = PI_GAMEOVER;
                }

            } else if (result != LEVEL_RUNNING) {
                time_left = LEVEL_TIME_TICKS; /* murio, cruzo o subio de nivel */
            }

            if (screen == PI_PLAYING) {
                draw_frame(game, time_left);
            }

            break;
        }

        case PI_PAUSED:
            if (sw_press) {
                screen = PI_PLAYING;
            } else if (isUp) {
                if (firstLevel(game) != 0) {
                    endGame(game);
                    return -1;
                }
                time_left = LEVEL_TIME_TICKS;
                screen = PI_PLAYING;
            } else if (isDwn) {
                led_scroll_start(&marquee, "FROGGER");
                screen = PI_MENU; /* abandona: el puntaje no se guarda */
            } else {
                disp_clear();
                if (led_scroll_step(&marquee, TEXT_ROW)) {
                    led_scroll_start(&marquee, "PAUSA");
                }
                disp_update();
            }
            break;

        case PI_INITIALS:
            if (sw_press) {
                updateHighScores(initials, final_score);
                led_scroll_start(&marquee, gameover_msg);
                screen = PI_GAMEOVER;
            } else {
                if (isUp)        initials[initials_pos] = (initials[initials_pos] == 'Z') ? 'A' : initials[initials_pos] + 1;
                else if (isDwn)  initials[initials_pos] = (initials[initials_pos] == 'A') ? 'Z' : initials[initials_pos] - 1;
                else if (isRgt && initials_pos < 2) initials_pos++;
                else if (isLft && initials_pos > 0) initials_pos--;

                blink++;
                draw_initials(initials, initials_pos, (blink / INITIALS_BLINK_TICKS) % 2 == 0);
            }
            break;

        case PI_GAMEOVER:
            if (sw_press) {
                led_scroll_start(&marquee, "FROGGER");
                screen = PI_MENU;
            } else {
                disp_clear();
                if (led_scroll_step(&marquee, TEXT_ROW)) {
                    led_scroll_start(&marquee, gameover_msg);
                }
                disp_update();
            }
            break;

        }

        usleep(TICK_US);
    }

    disp_clear();
    disp_update();
    endGame(game);

    return 0;
}
