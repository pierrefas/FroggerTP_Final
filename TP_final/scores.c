#include "scores.h"

int addLevelScores(game_state * game, int points){

    if(game == NULL){

        return ERROR_NULL_POINTER;

    }

    game->score += points;

    return 0;

}