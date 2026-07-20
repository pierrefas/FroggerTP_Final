#ifndef FUPDATE_H
#define FUPDATE_H

#include "gamestate.h"
#include "checking.h"

int followSupport(game_state *);
int frogStepUp(game_state *);
int frogStepDown(game_state *);
int frogStepRight(game_state *);
int frogStepLeft(game_state *);
int isInBounds(game_state *);

/* Repone la rana en la casilla de salida (no toca vidas ni puntaje). */
int resetFrogPos(game_state *);

/* Resta una vida y repone la rana en la salida.
 * Devuelve 1 si no quedan vidas (game over), 0 si el juego sigue. */
int loseLife(game_state *);

#endif
