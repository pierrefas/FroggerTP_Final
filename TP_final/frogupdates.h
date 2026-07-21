/*
 * frogupdates.h
 *
 * Movimiento de la rana: los cuatro pasos direccionales, arrastrarla
 * junto con el soporte cuando esta sobre el lago (followSupport), volver
 * a la fila de salida al morir o al cruzar (resetFrogPos) y descontar una
 * vida (loseLife). isInBounds centraliza el chequeo de limites (no salir
 * del mundo ni pisar un hueco-meta ya ocupado) que usa cada paso antes de
 * confirmarse.
 */

#ifndef FUPDATE_H
#define FUPDATE_H

#include "gamestate.h"
#include "checking.h"

#define FROG_START_COL 6 //Defino la 6ta columna como columna de inicio del juego

enum{

    LOOKUP = 0,
    LOOKRIGHT,
    LOOKDOWN,
    LOOKLEFT

};

int followSupport(game_state *); //Sirve para que la rana no se caiga de las entidades

int frogStepUp(game_state *); //Movimiento de la rana
int frogStepDown(game_state *);
int frogStepRight(game_state *);
int frogStepLeft(game_state *);

int isInBounds(game_state *);

int resetFrogPos(game_state *);
int loseLife(game_state *);

#endif
