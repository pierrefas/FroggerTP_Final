#ifndef FUPDATE-H
#define FUPDATE-H


#include <stdlib.h>

#define ADJCOORDFROG(n) (n * 16)


void followSupport(frog_player * rana, support_entity * soporte, int speedheight[]);
int deathOfFrog(frog_player * rana, support_entity * soporte, enemy_entity * enemigos);
void frogStepUp(frog_player * rana);        
void frogStepDown(frog_player * rana);
void frogStepRight(frog_player * rana);
void frogStepLeft(frog_player * rana);
int isInBounds(frog_player * rana);


#endif