#ifndef LEVELSET_H
#define LEVELSET_H

#include "gamestate.h"
#include "checking.h"

/* Nivel actual del juego. La definicion real vive en levelset.c;
 * firstLevel() lo resetea a 1 y updateLevel() lo incrementa. */
extern int level;

#define STARTING_LIVES 3

#define ERROR_NIVEL_INVALIDO -404
#define ERROR_TIPO_INVALIDO -405
#define ERROR_ALTURA_INVALIDA -406
#define ERROR_ENTIDAD_INCOLOCABLE -137

/* Codigos de retorno de updateLevel(). El llamador (front-end) los usa
 * para reiniciar la barra de tiempo o cortar la partida. updateLevel NO
 * libera memoria: tras GAME_OVER el game_state sigue vivo (para mostrar
 * el puntaje final) y el duenio debe llamar a endGame() cuando termine. */
#define LEVEL_RUNNING 0
#define GAME_OVER 1
#define FROG_DIED 2
#define FROG_CROSSED 3
#define LEVEL_UP 4

int firstLevel(game_state *);
int nextLevel(game_state *);

/* Cheat/debug de los front-ends (tecla E en PC, pausa+arriba en la Pi):
 * salta al nivel siguiente sin dar los puntos de premio. */
int skipLevel(game_state *);

/* Avanza un tick de juego: mueve entidades, arrastra a la rana en los
 * troncos, resuelve muertes/cruces y el cambio de nivel.
 * time_left/time_total: estado de la barra de tiempo del front-end
 * (se usa para el bonus de puntaje al cruzar). */
int updateLevel(game_state *, int time_left, int time_total);

#endif
