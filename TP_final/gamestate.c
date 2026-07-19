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
    
    newgame->pspeedheight = (int*) malloc(10*sizeof(int));

    if(newgame->pspeedheight == NULL){

        free(newgame->pspeedheight);
        free(newgame->prana);
        free(newgame->psoport);
        free(newgame->penemies);
        free(newgame);

        return NULL;


    }    
    
    newgame->score = 0;
   
    newgame->penemies->type = -1;
    newgame->psoport->type = -1;

    return newgame;

}
