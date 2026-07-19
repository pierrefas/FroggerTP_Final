#include "gamestate.h"

game_state * createGame(void){

    game_state * newgame = (game_state*) malloc(sizeof(game_state));

    if(newgame == NULL){

        free(newgame);

        return NULL;


    }

    newgame->penemies = (enemy_entity*) malloc(40*sizeof(enemy_entity));

    if(newgame->penemies == NULL){

        free(newgame->penemies);
        free(newgame);

        return NULL;


    }

    newgame->psoport = (support_entity*) malloc(40*sizeof(support_entity));

    if(newgame->psoport == NULL){

        free(newgame->psoport);
        free(newgame->penemies);
        free(newgame);

        return NULL;


    }

    newgame->prana = (frog_player*) malloc(sizeof(frog_player));

    if(newgame->prana == NULL){

        free(newgame->prana);
        free(newgame->psoport);
        free(newgame->penemies);
        free(newgame);

        return NULL;


    }
    
    newgame->pspeedheight = (int*) malloc(NUM_HEIGHT_LEVELS*sizeof(int));

    if(newgame->pspeedheight == NULL){

        free(newgame->pspeedheight);
        free(newgame->prana);
        free(newgame->psoport);
        free(newgame->penemies);
        free(newgame);

        return NULL;


    }
    
    newgame->safespaces = (int*) malloc(5*sizeof(int));

    if(newgame->safespaces == NULL){

        free(newgame->safespaces);
        free(newgame->pspeedheight);
        free(newgame->prana);
        free(newgame->psoport);
        free(newgame->penemies);
        free(newgame);

        return NULL;


    }


    int i;

    for(i = 0; i < 5 ; i++){

        (newgame->safespaces)[i] = 0;


    }


    return newgame;

}

int endGame(game_state* game){

    if(game == NULL){

        return 1;

    }

    free(game->pspeedheight);
    free(game->prana);
    free(game->psoport);
    free(game->penemies);
    free(game);

    return 0;

}
