#ifndef LEVELSET-H
#define LEVELSET-H

int level;

#include <stdlib.h>

#define ERROR_NIVEL_INVALIDO -404
#define ERROR_TIPO_INVALIDO -405
#define ERROR_ALTURA_INVALIDA -406

int nextLevel(int level, enemy_entity* enemigos, support_entity* soportes, int heightspeed[],frog_player* rana);

#endif