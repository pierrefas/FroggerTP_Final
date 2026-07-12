#ifndef LEVELSET-H
#define LEVELSET-H

int level;

#include <stdlib.h>

#define ERROR_NIVEL_INVALIDO -404

int nextLevel(int level, enemy_entity* enemigos, support_entity* soportes, int heightspeed[],frog_player* rana);

#endif