#include "scores.h"

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
