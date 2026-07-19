#ifndef LEVELSET_H
#define LEVELSET_H

// "int level;" (sin extern) definia una variable nueva en cada .c que
// incluyera este header; con gcc moderno (-fno-common) eso rompe el link
// con "multiple definition of level" apenas un segundo archivo lo incluye.
// La definicion real ahora vive en levelset.c.
extern int level;

#include "gamestate.h"
#include "checking.h"

#define ERROR_NIVEL_INVALIDO -404
#define ERROR_TIPO_INVALIDO -405
#define ERROR_ALTURA_INVALIDA -406
#define ERROR_ENTIDAD_INCOLOCABLE -137

// Codigo de retorno de updateLevel() para indicarle al llamador que el
// juego termino: en esa rama updateLevel ya llamo a endGame(game) y liberó
// toda la memoria, asi que el llamador no debe volver a tocar `game`.
#define GAME_OVER 1

int nextLevel(game_state*);
int firstLevel(game_state*);
int updateLevel(game_state*,int);

#endif