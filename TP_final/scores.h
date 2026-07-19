#ifndef SCORES_H
#define SCORES_H

#include "gamestate.h"

// addLevelScores nunca se implemento en scores.c; se deja declarada por si
// la logica original la necesitaba, pero nada la llama hoy. Las que
// existen de verdad son estas dos:
int addLevelScores(game_state * game, int points);
int pointForFinishingLevel(game_state * game);
int pointsForTime(game_state * game, int time);

#endif