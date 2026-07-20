#include "scores.h"
#include "levelset.h" /* por el nivel actual (extern level) */

#define POINTS_CROSS_BASE 10 /* por cruce, multiplicado por el nivel */
#define POINTS_TIME_MAX 20   /* bonus maximo por cruzar con la barra llena */
#define POINTS_LEVEL_BASE 100 /* por nivel completado, multiplicado por el nivel */

int pointsForCross(game_state * game, int time_left, int time_total){

    if(game == NULL || time_total <= 0){
        return 0;
    }

    if(time_left < 0){
        time_left = 0;
    }

    game->score += POINTS_CROSS_BASE * level + (POINTS_TIME_MAX * time_left) / time_total;

    return 1;

}

int pointForFinishingLevel(game_state * game){

    if(game == NULL){
        return 0;
    }

    game->score += POINTS_LEVEL_BASE * level;

    return 1;

}
