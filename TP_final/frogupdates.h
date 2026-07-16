#ifndef FUPDATE_H
#define FUPDATE_H


#include "entidades.h"
#include "checking.h"

int followSupport(frog_player * rana, support_entity * soporte, int speedheight[]);
int deathOfFrog(frog_player * rana, support_entity * soporte, enemy_entity * enemigos);
int frogStepUp(frog_player * rana);        
int frogStepDown(frog_player * rana);
int frogStepRight(frog_player * rana);
int frogStepLeft(frog_player * rana);
int isInBounds(frog_player * rana);


#endif