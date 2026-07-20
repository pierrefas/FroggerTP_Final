#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stdlib.h>
#include <stdio.h>

/* Conversion casillero -> pixeles: cada casillero mide 16 px. */
#define ADJCOORDFROG(n) ((n) * 16)

/* Error de puntero nulo, usado por las funciones del backend. */
#define ERROR_NULL_POINTER -67

/* Borde derecho del mundo en px (14 columnas de juego, 0..13). */
#define ENDWORLD ADJCOORDFROG(14)

/* Cantidad de "alturas" indexables en pspeedheight: filas 0..12
 * (ver el mapa de filas en checking.h). */
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
    int supporting; /* 1 si puede llevar a la rana (tronco/tortuga a flote) */

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
