#ifndef SCORES_H
#define SCORES_H

#include "gamestate.h"

/* Suma los puntos de un cruce exitoso: base por nivel + bonus por el
 * tiempo que quedaba en la barra (time_left sobre time_total). */
int pointsForCross(game_state * game, int time_left, int time_total);

/* Suma el premio por completar los 5 huecos-meta del nivel actual. */
int pointForFinishingLevel(game_state * game);

#endif
