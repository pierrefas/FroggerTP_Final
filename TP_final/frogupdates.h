#ifndef FUPDATE_H
#define FUPDATE_H


#include "gamestate.h"
#include "checking.h"

int followSupport(game_state*);
int deathOfFrog(game_state*);
int frogStepUp(game_state*);        
int frogStepDown(game_state*);
int frogStepRight(game_state*);
int frogStepLeft(game_state*);
int isInBounds(game_state*);


#endif