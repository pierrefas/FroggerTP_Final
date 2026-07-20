#ifndef SCORES_H
#define SCORES_H

#include "gamestate.h"
#include "levelset.h" /* por el nivel actual (extern level) */

#define POINTS_CROSS_BASE 10 // por cruce, multiplicado por el nivel 
#define POINTS_TIME_MAX 20   // bonus maximo por cruzar con la barra llena
#define POINTS_LEVEL_BASE 100 // por nivel completado, multiplicado por el nive


// Suma los puntos de un cruce exitoso: base por nivel + bonus por el tiempo de llegada
int pointsForCross(game_state * game, int time_left, int time_total);

/* Suma el premio por completar los 5 huecos-meta del nivel actual. */
int pointForFinishingLevel(game_state * game);

#endif
