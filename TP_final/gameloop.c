/*
 * gameloop.c
 *
 * Ver gameloop.h. Este archivo es nuevo (Mati / port Raspberry Pi).
 *
 * NO se toco ningun archivo del equipo para escribir esto. Varios de
 * esos archivos tienen bugs que impiden que este loop (y en algunos
 * casos el proyecto entero) compile o linkee; estan documentados en
 * el bloque de "PROTOTIPOS FALTANTES" de aca abajo y se los mande al
 * equipo por separado. Sacar ese bloque en cuanto los arreglen.
 */

#include "gameloop.h"

#include <unistd.h>

#include "gamestate.h"
#include "checking.h"
#include "frogupdates.h"
#include "joystick.h"
#include "joydrv.h"
#include "drawleds.h"
#include "disdrv.h"

/* -----------------------------------------------------------------------
 * PROTOTIPOS FALTANTES (bugs de headers del equipo, ver aviso aparte)
 *
 * - gamestate.h no declara createGame()/endGame() a pesar de definirlas
 *   en gamestate.c: cualquier archivo que las use (incluido levelset.c)
 *   depende de una declaracion implicita.
 * - levelset.h declara "int level;" (definicion, sin "extern") en vez de
 *   "extern int level;". Si yo incluyera levelset.h ademas de levelset.c,
 *   cada .c que lo incluya se trae su propia definicion de "level", y con
 *   gcc moderno (-fno-common, default desde gcc 10) el link falla con
 *   "multiple definition of level". Lo evito declarando yo mismo lo que
 *   necesito en vez de incluir levelset.h.
 * ----------------------------------------------------------------------- */
game_state * createGame(void);
int endGame(game_state * game);
extern int level;
int firstLevel(game_state * game);
int updateLevel(game_state * game, int time);

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

        /* updateLevel() llama a endGame(game) puertas adentro apenas
         * lives llega a 0 (levelset.c, rama "else if(game->prana->lives < 1)"),
         * liberando TODO el game_state en esa misma llamada. Para no leer
         * memoria ya liberada, predecimos si esta va a ser la ultima
         * vuelta repitiendo el mismo chequeo de muerte que hace
         * updateLevel puertas adentro, y si da que si, no volvemos a
         * tocar `game` depues de llamarlo. */
        int lives_before = game->prana->lives;
        int dying_this_tick = (isDeadFromEnemy(game) == 1) || (isDeadLake(game) == 1);

        updateLevel(game, time_left);

        if(dying_this_tick && lives_before <= 1){
            /* game ya fue liberado por updateLevel(). No tocar mas. */
            break;
        }

        draw_frame(game, time_left);

        usleep(TICK_US);
    }

    return 0;
}
