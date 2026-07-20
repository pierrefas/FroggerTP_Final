/*
 * a_PC_display.c
 *
 * Front-end de PC (Allegro 5). Dueño de la ventana, los eventos y el
 * timer; la logica del juego vive en el backend (levelset/checking/
 * frogupdates) y aca solo se traduce teclado -> movimientos y estado ->
 * dibujo. Maneja cuatro pantallas: menu, juego, pausa y game over.
 */

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>

#include "a_PC_display.h"
#include "a_map.h"
#include "a_sprites.h"
#include "a_alphanum.h"
#include "a_pause.h"
#include "a_render.h"
#include "gamestate.h"
#include "levelset.h"
#include "frogupdates.h"
#include "highscores.h"

#define FPS 30

/* Ticks de la barra de tiempo para un cruce (~30 segundos). */
#define LEVEL_TIME_TICKS (30 * FPS)

/* Parpadeo de la letra activa al cargar iniciales, en frames. */
#define INITIALS_BLINK_FRAMES 8

typedef enum {
    SCREEN_MENU,
    SCREEN_PLAYING,
    SCREEN_PAUSED,
    SCREEN_INITIALS,
    SCREEN_GAMEOVER
} screen_t;

/* inicializa Allegro y addons; no carga sprites aun */
int init_alegro(void)
{
    if (!al_init()) {
        fprintf(stderr, "allegro failed to initialize\n");
        return 0;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "allegro keyboard installation failed\n");
        return 0;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Failed to initialize primitives addon!\n");
        return 0;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "Failed to initialize font addon!\n");
        return 0;
    }

    /* image addon must be initialized before using al_load_bitmap */
    al_init_image_addon();

    return 1;
}

/* Titulo/encabezado centrado: con spritesheet usa la fuente del arcade
 * (index_disp, color 0 blanco / 1 amarillo / 2 rojo / 3 magenta / 4 cian);
 * sin hoja cae a la fuente builtin con fallback_col. */
static void draw_title_retro(ALLEGRO_FONT * font, const char * txt, int y,
                             int color, ALLEGRO_COLOR fallback_col)
{
    if (get_spritesheet()) {
        index_disp(txt, CENTER_X - index_disp_len(txt) / 2, y, color);
    } else {
        al_draw_text(font, fallback_col, CENTER_X, y, ALLEGRO_ALIGN_CENTER, txt);
    }
}

static void draw_menu(ALLEGRO_FONT * font)
{
    al_draw_filled_rectangle(0, 0, GAME_WIDTH, GAME_HEIGHT, al_map_rgb(0, 35, 10));

    draw_title_retro(font, "F R O G G E R", 28, 1, al_map_rgb(90, 230, 90));

    al_draw_text(font, al_map_rgb(255, 255, 255), CENTER_X, 56,
                 ALLEGRO_ALIGN_CENTER, "ENTER  JUGAR");
    al_draw_text(font, al_map_rgb(255, 255, 255), CENTER_X, 68,
                 ALLEGRO_ALIGN_CENTER, "ESC    SALIR");
    al_draw_text(font, al_map_rgb(160, 160, 160), CENTER_X, 88,
                 ALLEGRO_ALIGN_CENTER, "FLECHAS O WASD PARA MOVERSE");
    al_draw_text(font, al_map_rgb(160, 160, 160), CENTER_X, 100,
                 ALLEGRO_ALIGN_CENTER, "ESC PAUSA DURANTE EL JUEGO");

    /* top 10 */
    ScoreEntry list[HS_MAX_SCORES];
    int n = readHighScores(list, HS_MAX_SCORES);
    int i;

    draw_title_retro(font, "MEJORES PUNTAJES", 124, 1, al_map_rgb(235, 220, 60));

    if (n == 0) {
        al_draw_text(font, al_map_rgb(160, 160, 160), CENTER_X, 140,
                     ALLEGRO_ALIGN_CENTER, "TODAVIA NO HAY");
    }
    for (i = 0; i < n; i++) {
        al_draw_textf(font, al_map_rgb(255, 255, 255), CENTER_X, 140 + i * 10,
                      ALLEGRO_ALIGN_CENTER, "%2d  %-3s  %d",
                      i + 1, list[i].initials, list[i].score);
    }
}

static void draw_initials_screen(ALLEGRO_FONT * font, int score,
                                 const char * initials, int pos, int blink_on)
{
    al_draw_filled_rectangle(0, 0, GAME_WIDTH, GAME_HEIGHT, al_map_rgb(0, 20, 40));

    draw_title_retro(font, "ENTRASTE AL TOP 10", CENTER_Y - 56, 1,
                     al_map_rgb(235, 220, 60));
    al_draw_textf(font, al_map_rgb(255, 255, 255), CENTER_X, CENTER_Y - 36,
                  ALLEGRO_ALIGN_CENTER, "PUNTAJE  %d", score);

    /* las tres iniciales, espaciadas; la activa parpadea y va subrayada */
    int i;
    for (i = 0; i < 3; i++) {

        int x = CENTER_X + (i - 1) * 20;

        if (i != pos || blink_on) {
            char letra[2] = {initials[i], '\0'};
            if (get_spritesheet()) {
                index_disp(letra, x - 4, CENTER_Y - 4, 1);
            } else {
                al_draw_text(font, al_map_rgb(90, 230, 90), x, CENTER_Y - 4,
                             ALLEGRO_ALIGN_CENTER, letra);
            }
        }
        if (i == pos) {
            al_draw_filled_rectangle(x - 6, CENTER_Y + 8, x + 6, CENTER_Y + 10,
                                     al_map_rgb(90, 230, 90));
        }
    }

    al_draw_text(font, al_map_rgb(200, 200, 200), CENTER_X, CENTER_Y + 32,
                 ALLEGRO_ALIGN_CENTER, "FLECHAS O LETRAS PARA ELEGIR");
    al_draw_text(font, al_map_rgb(200, 200, 200), CENTER_X, CENTER_Y + 44,
                 ALLEGRO_ALIGN_CENTER, "ENTER  CONFIRMAR");
}

static void draw_gameover(ALLEGRO_FONT * font, int score, int hs_rank)
{
    al_draw_filled_rectangle(0, 0, GAME_WIDTH, GAME_HEIGHT, al_map_rgb(40, 0, 0));

    draw_title_retro(font, "GAME OVER", CENTER_Y - 48, 2, al_map_rgb(230, 70, 70));
    al_draw_textf(font, al_map_rgb(255, 255, 255), CENTER_X, CENTER_Y - 20,
                  ALLEGRO_ALIGN_CENTER, "PUNTAJE  %d", score);

    if (hs_rank >= 0) {
        al_draw_textf(font, al_map_rgb(235, 220, 60), CENTER_X, CENTER_Y - 4,
                      ALLEGRO_ALIGN_CENTER, "ENTRASTE AL TOP 10: PUESTO %d", hs_rank + 1);
    }

    al_draw_text(font, al_map_rgb(200, 200, 200), CENTER_X, CENTER_Y + 24,
                 ALLEGRO_ALIGN_CENTER, "ENTER  VOLVER AL MENU");
}

int display(void)
{
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    int desktop_h = info.y2 - info.y1;

    /* escala entera para que el pixel art quede nitido */
    int scale = (desktop_h / 2) / GAME_HEIGHT;
    if (scale < 1) scale = 1;

    int scaled_w = GAME_WIDTH * scale;
    int scaled_h = GAME_HEIGHT * scale;

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    ALLEGRO_BITMAP * buffer = al_create_bitmap(GAME_WIDTH, GAME_HEIGHT);
    ALLEGRO_DISPLAY * disp = al_create_display(scaled_w, scaled_h);
    ALLEGRO_FONT * font = al_create_builtin_font();

    if (!timer || !queue || !buffer || !disp || !font) {
        fprintf(stderr, "Failed to create display resources\n");
        if (font) al_destroy_font(font);
        if (disp) al_destroy_display(disp);
        if (buffer) al_destroy_bitmap(buffer);
        if (queue) al_destroy_event_queue(queue);
        if (timer) al_destroy_timer(timer);
        return 0;
    }

    al_set_window_title(disp, "Frogger");

    /* los sprites son opcionales: sin spritesheet se dibuja con primitivas */
    if (load_sprites(NULL) != 0) {
        fprintf(stderr, "aviso: sin spritesheet, se dibuja con primitivas\n");
    }

    game_state * gs = createGame();
    if (!gs) {
        fprintf(stderr, "Failed to create game state\n");
        destroy_sprites();
        al_destroy_font(font);
        al_destroy_display(disp);
        al_destroy_bitmap(buffer);
        al_destroy_event_queue(queue);
        al_destroy_timer(timer);
        return 0;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    screen_t screen = SCREEN_MENU;
    int running = 1;
    int redraw = 1;
    int time_left = 0;
    int hs_rank = -1;
    int anim = 0; /* contador de frames para el parpadeo de las iniciales */
    char initials[4] = "AAA";
    int initials_pos = 0;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while (running) {

        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {

            if (screen == SCREEN_PLAYING) {

                int result = LEVEL_RUNNING;

                if (--time_left <= 0) {
                    /* se acabo la barra de tiempo: cuesta una vida */
                    result = loseLife(gs) ? GAME_OVER : FROG_DIED;
                }

                if (result == LEVEL_RUNNING) {
                    result = updateLevel(gs, time_left, LEVEL_TIME_TICKS);
                }

                if (result == GAME_OVER) {
                    if (hsQualifies(gs->score)) {
                        initials[0] = initials[1] = initials[2] = 'A';
                        initials_pos = 0;
                        screen = SCREEN_INITIALS;
                    } else {
                        hs_rank = -1; /* no entro al top 10: no se guarda nada */
                        screen = SCREEN_GAMEOVER;
                    }
                } else if (result != LEVEL_RUNNING) {
                    /* murio, cruzo o subio de nivel: barra de nuevo */
                    time_left = LEVEL_TIME_TICKS;
                }

            }

            anim++;
            redraw = 1;

        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

            running = 0;

        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {

            int key = event.keyboard.keycode;

            switch (screen) {

            case SCREEN_MENU:
                if (key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_SPACE) {
                    firstLevel(gs);
                    time_left = LEVEL_TIME_TICKS;
                    screen = SCREEN_PLAYING;
                } else if (key == ALLEGRO_KEY_ESCAPE || key == ALLEGRO_KEY_Q) {
                    running = 0;
                }
                break;

            case SCREEN_PLAYING:
                if (key == ALLEGRO_KEY_UP || key == ALLEGRO_KEY_W) frogStepUp(gs);
                else if (key == ALLEGRO_KEY_DOWN || key == ALLEGRO_KEY_S) frogStepDown(gs);
                else if (key == ALLEGRO_KEY_RIGHT || key == ALLEGRO_KEY_D) frogStepRight(gs);
                else if (key == ALLEGRO_KEY_LEFT || key == ALLEGRO_KEY_A) frogStepLeft(gs);
                else if (key == ALLEGRO_KEY_ESCAPE || key == ALLEGRO_KEY_P) screen = SCREEN_PAUSED;
                break;

            case SCREEN_PAUSED:
                if (key == ALLEGRO_KEY_ESCAPE || key == ALLEGRO_KEY_ENTER) {
                    screen = SCREEN_PLAYING;
                } else if (key == ALLEGRO_KEY_R) {
                    firstLevel(gs); /* reiniciar la partida */
                    time_left = LEVEL_TIME_TICKS;
                    screen = SCREEN_PLAYING;
                } else if (key == ALLEGRO_KEY_M) {
                    screen = SCREEN_MENU; /* salir del juego sin cerrar el programa */
                }
                break;

            case SCREEN_INITIALS:
                if (key == ALLEGRO_KEY_ENTER) {
                    hs_rank = updateHighScores(initials, gs->score);
                    screen = SCREEN_GAMEOVER;
                } else if (key == ALLEGRO_KEY_UP) {
                    initials[initials_pos] = (initials[initials_pos] == 'Z') ? 'A' : initials[initials_pos] + 1;
                } else if (key == ALLEGRO_KEY_DOWN) {
                    initials[initials_pos] = (initials[initials_pos] == 'A') ? 'Z' : initials[initials_pos] - 1;
                } else if (key == ALLEGRO_KEY_RIGHT) {
                    if (initials_pos < 2) initials_pos++;
                } else if (key == ALLEGRO_KEY_LEFT) {
                    if (initials_pos > 0) initials_pos--;
                } else if (key >= ALLEGRO_KEY_A && key <= ALLEGRO_KEY_Z) {
                    /* tipear la letra directamente tambien vale */
                    initials[initials_pos] = 'A' + (key - ALLEGRO_KEY_A);
                    if (initials_pos < 2) initials_pos++;
                }
                break;

            case SCREEN_GAMEOVER:
                if (key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_SPACE) {
                    screen = SCREEN_MENU;
                } else if (key == ALLEGRO_KEY_ESCAPE || key == ALLEGRO_KEY_Q) {
                    running = 0;
                }
                break;

            }

        }

        if (redraw && al_is_event_queue_empty(queue)) {

            al_set_target_bitmap(buffer);
            al_clear_to_color(al_map_rgb(0, 0, 0));

            switch (screen) {

            case SCREEN_MENU:
                draw_menu(font);
                break;

            case SCREEN_PLAYING:
            case SCREEN_PAUSED:
                a_disp_map();
                draw_game_state(gs);
                draw_hud(gs, font, time_left, LEVEL_TIME_TICKS);
                if (screen == SCREEN_PAUSED) {
                    draw_pause_overlay(font);
                }
                break;

            case SCREEN_INITIALS:
                draw_initials_screen(font, gs->score, initials, initials_pos,
                                     (anim / INITIALS_BLINK_FRAMES) % 2 == 0);
                break;

            case SCREEN_GAMEOVER:
                draw_gameover(font, gs->score, hs_rank);
                break;

            }

            /* escalo el buffer de baja resolucion a la ventana */
            al_set_target_bitmap(al_get_backbuffer(disp));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_scaled_bitmap(buffer, 0, 0, GAME_WIDTH, GAME_HEIGHT,
                                  0, 0, scaled_w, scaled_h, 0);
            al_flip_display();

            redraw = 0;

        }

    }

    /* cleanup */
    destroy_sprites();
    endGame(gs);
    al_destroy_font(font);
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 1;
}
