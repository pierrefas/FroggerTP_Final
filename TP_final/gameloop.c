/*
 * gameloop.c
 *
 * Ver gameloop.h. Conecta el joystick con el movimiento de la rana y
 * con el dibujado en el display de LEDs, algo que hasta ahora ningun
 * archivo hacia: joystick.c, drawleds.c, frogupdates.c, entityupdates.c
 * y levelset.c ya existian por separado, pero nada los llamaba juntos
 * en un mismo ciclo.
 */

#include "gameloop.h"

#include <unistd.h>

#include "gamestate.h"
#include "checking.h"
#include "frogupdates.h"
#include "levelset.h"
#include "joystick.h"
#include "joydrv.h"
#include "drawleds.h"
#include "disdrv.h"

/* Cuantos ticks de este loop entran en una "vuelta" de la barra de tiempo.
 * No hay ninguna unidad documentada para el parametro "time" de
 * updateLevel()/pointsForTime() en el codigo del equipo: esto es una
 * eleccion propia, a confirmar con quien escribio levelset.c/scores.c. */
#define LEVEL_TIME_TICKS    400

/* ~20 ticks por segundo. Ajustar segun que tan responsive se sienta el
 * joystick contra que tan rapido corren los autos/troncos. */
#define TICK_US             50000

static void draw_frame(game_state * game, int time_left){
    int i;

    disp_clear();

    for(i = 0; (game->psoport + i)->type != -1; i++){
        led_draw_entity((game->psoport + i)->startcoord, (game->psoport + i)->height, (game->psoport + i)->type);
    }
    for(i = 0; (game->penemies + i)->type != -1; i++){
        led_draw_entity((game->penemies + i)->startcoord, (game->penemies + i)->height, (game->penemies + i)->type);
    }

    led_draw_frog(game->prana->startcoord, game->prana->height);
    led_draw_lives(game->prana->lives);
    led_draw_time((time_left * (PLAY_FIELD_MAX_X + 1)) / LEVEL_TIME_TICKS);

    disp_update();
}

int run_headless_game(void){

    game_state * game = createGame();
    if(game == NULL){
        return -1;
    }

    disp_init();
    joy_init();

    level = 1;
    if(firstLevel(game) != 0){
        endGame(game);
        return -1;
    }

    int time_left = LEVEL_TIME_TICKS;

    while(1){

        joystic_update();

        if(isUp)        frogStepUp(game);
        else if(isDwn)  frogStepDown(game);
        else if(isRgt)  frogStepRight(game);
        else if(isLft)  frogStepLeft(game);

        if(--time_left <= 0){
            time_left = LEVEL_TIME_TICKS;
        }
        if(game->prana->height > ENDLAKE){
            /* Llegar a la zona segura reinicia la barra. Aproximacion propia:
             * ver el aviso sobre el semantica real de "time". */
            time_left = LEVEL_TIME_TICKS;
        }

        if(updateLevel(game, time_left) == GAME_OVER){
            /* updateLevel() ya llamo a endGame(game) y libero todo el
             * game_state. No tocar `game` de nuevo. */
            break;
        }

        draw_frame(game, time_left);

        usleep(TICK_US);
    }

    return 0;
}
