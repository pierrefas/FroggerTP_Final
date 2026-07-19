#include "scores.h"
#include "checking.h"

int pointForFinishingLevel(game_state * game){

    if(game == NULL){

        return 0;

    }

    if(isLevelFinished(game)){

        game->score += 100;
        return 1;

    }
    else{

        return 0;

    }

}

int pointsForTime(game_state * game, int time){

    if(game == NULL){

        return 0;

    }
    else{

        game->score += time;
        return 1;

    }

}

