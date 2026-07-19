#ifndef LEVELSET_H
#define LEVELSET_H

int level;

#include "gamestate.h"

#define ERROR_NIVEL_INVALIDO -404
#define ERROR_TIPO_INVALIDO -405
#define ERROR_ALTURA_INVALIDA -406
#define ERROR_ENTIDAD_INCOLOCABLE -137


int nextLevel(int,game_state*);
int firstLevel(game_state*);

#endif