/*
 * gameloop.c
 *
 * Ver gameloop.h. Conecta el joystick con el movimiento de la rana y
 * con el dibujado en el display de LEDs. Usa el mismo backend que la
 * version de PC (levelset/checking/frogupdates): aca solo se traduce
 * joystick -> movimientos y estado -> LEDs.
 *
 * TODO (fase Raspberry): menu de pausa/reinicio con el switch del
 * joystick, y game over mostrando el puntaje en el display.
 */

#include "gameloop.h"

#include <unistd.h>

#include "gamestate.h"
#include "checking.h"
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

/* Iniciales grabadas en el top 10 desde la Pi. */
#define PLAYER_INITIALS "PI-"

static void draw_frame(game_state * game, int time_left)
{
    int i;

    disp_clear();

    for (i = 0; (game->psoport + i)->type != -1; i++) {
        led_draw_entity((game->psoport + i)->startcoord, (game->psoport + i)->height, (game->psoport + i)->type);
    }
    for (i = 0; (game->penemies + i)->type != -1; i++) {
        led_draw_entity((game->penemies + i)->startcoord, (game->penemies + i)->height, (game->penemies + i)->type);
    }

    led_draw_frog(game->prana->startcoord, game->prana->height);
    led_draw_lives(game->prana->lives);
    led_draw_time((time_left * (PLAY_FIELD_MAX_X + 1)) / LEVEL_TIME_TICKS);

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

    if (firstLevel(game) != 0) {
        endGame(game);
        return -1;
    }

    int time_left = LEVEL_TIME_TICKS;
    int result = LEVEL_RUNNING;

    while (result != GAME_OVER) {

        joystic_update();

        if (isUp)        frogStepUp(game);
        else if (isDwn)  frogStepDown(game);
        else if (isRgt)  frogStepRight(game);
        else if (isLft)  frogStepLeft(game);

        result = LEVEL_RUNNING;

        if (--time_left <= 0) {
            /* se acabo la barra de tiempo: cuesta una vida */
            result = loseLife(game) ? GAME_OVER : FROG_DIED;
        }

        if (result == LEVEL_RUNNING) {
            result = updateLevel(game, time_left, LEVEL_TIME_TICKS);
        }

        if (result != LEVEL_RUNNING) {
            time_left = LEVEL_TIME_TICKS; /* murio, cruzo o subio de nivel */
        }

        draw_frame(game, time_left);

        usleep(TICK_US);
    }

    /* updateLevel ya no libera el estado: el duenio es este loop */
    updateHighScores(PLAYER_INITIALS, game->score);
    endGame(game);

    return 0;
}
