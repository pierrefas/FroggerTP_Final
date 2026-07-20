#ifndef FUPDATE_H
#define FUPDATE_H

#include "gamestate.h"
#include "checking.h"

#define FROG_START_COL 6 //Defino la 6ta columna como columna de inicio del juego

typedef enum{

    LOOKUP,
    LOOKRIGHT,
    LOOKDOWN,
    LOOKLEFT

} orientations;

int followSupport(game_state *); //Sirve para que la rana no se caiga de las entidades

int frogStepUp(game_state *); //Movimiento de la rana
int frogStepDown(game_state *);
int frogStepRight(game_state *);
int frogStepLeft(game_state *);

int isInBounds(game_state *);

int resetFrogPos(game_state *);
int loseLife(game_state *);

#endif
