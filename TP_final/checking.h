#ifndef CHECKING_H
#define CHECKING_H

#include "gamestate.h"


#define STARTLAKE 7
#define ENDLAKE 11
#define GOALROW (ENDLAKE + 1)
#define SAFEROW (STARTLAKE - 1)

#define HITBOX_MARGIN 2 //Nos dimos cuenta que el entrar a la casilla final era muy dificl asi que le dimos un margen para que puedan entrar


#define GOAL_SLOT_X(i) (ADJCOORDFROG(1)/2 + (i) * ADJCOORDFROG(3)) //Defino el inicio de las zonas de llegada


int goalSlotAt(const frog_player * rana); //Chequea en cual slot final esta
int isDeadFromEnemy(game_state *);//Chequea si muere por agua o por un enemigo
int isDeadLake(game_state *); 
int isAtEnd(game_state *); //Chequea si esta en el final o si termino el nivel
int isLevelFinished(game_state *);

#endif
