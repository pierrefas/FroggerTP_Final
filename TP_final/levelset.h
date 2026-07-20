#ifndef LEVELSET_H
#define LEVELSET_H

#include "gamestate.h"
#include "checking.h"
#include "scores.h"
#include "entityupdates.h"
#include "frogupdates.h"
#include <time.h>
#include <stdlib.h>


extern int level;

#define STARTING_LIVES 3

#define ERROR_NIVEL_INVALIDO -404
#define ERROR_TIPO_INVALIDO -405
#define ERROR_ALTURA_INVALIDA -406
#define ERROR_ENTIDAD_INCOLOCABLE -137


#define MAX_ROW_SPEED 6 //Velocidad maxima para que no sea imposibles los niveles ademas de que no genera bugs con las colisiones y el render
#define ENTITY_MIN_GAP 8 //Misma idea pero para que los autos no esten todos apilados
#define PLACE_ATTEMPTS 200 // Intentos para generar una entidad sin que se superponga con otra

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


int skipLevel(game_state *); //Funcion cheat creada para hacer el testear la jugabilidad

int updateLevel(game_state *, int time_left, int time_total);

#endif
