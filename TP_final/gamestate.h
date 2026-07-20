#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <stdlib.h>
#include <stdio.h>
#include "checking.h"


#define ADJCOORDFROG(n) ((n) * 16) //Comvierte casilleros a pixeles, sirve para los saltos de la rana

#define ERROR_NULL_POINTER -67
#define ENDWORLD ADJCOORDFROG(14)


#define NUM_HEIGHT_LEVELS 13
#define MAX_ENTITIES 40

typedef struct {

    int startcoord;
    int endcoord;
    int height;
    int type;

} enemy_entity;

typedef struct {

    int startcoord;
    int endcoord;
    int height;
    int type;
    int supporting; // sirve para determinar si la rana esta siendo sostenida por el soporte
    int divetimer;  // fase del ciclo de buceo de una tortuga, si es -1 es tronco y no se unde

} support_entity;

typedef struct {

    int startcoord;
    int endcoord;
    int height;
    int lives;
    int orientation; /* 0 arriba, 1 derecha, 2 abajo, 3 izquierda (solo front-end) */

} frog_player;

typedef struct {
    frog_player * prana;
    support_entity * psoport; /* lista terminada con type == -1 */
    enemy_entity * penemies;  /* lista terminada con type == -1 */
    int * pspeedheight;       /* velocidad (px/tick) por fila, NUM_HEIGHT_LEVELS entradas */
    int * safespaces;         /* huecos-meta ya ocupados (NUM_GOAL_SLOTS entradas) */
    int score;
} game_state;

game_state * createGame(void);
int endGame(game_state * game);

#endif
