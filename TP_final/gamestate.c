#include "gamestate.h"

game_state * createGame(void){

    game_state * newgame = (game_state *) malloc(sizeof(game_state));

    if(newgame == NULL){
        return NULL;
    }

    newgame->penemies = (enemy_entity *) malloc(MAX_ENTITIES * sizeof(enemy_entity));
    newgame->psoport = (support_entity *) malloc(MAX_ENTITIES * sizeof(support_entity));
    newgame->prana = (frog_player *) malloc(sizeof(frog_player));
    newgame->pspeedheight = (int *) malloc(NUM_HEIGHT_LEVELS * sizeof(int));
    newgame->safespaces = (int *) malloc(NUM_GOAL_SLOTS * sizeof(int));

    if(newgame->penemies == NULL || newgame->psoport == NULL || newgame->prana == NULL ||
       newgame->pspeedheight == NULL || newgame->safespaces == NULL){

        endGame(newgame); //free(NULL) es valido: libera solo lo que se consiguio
        return NULL;

    }

    /* Listas vacias y estado neutro hasta que firstLevel() arme el nivel */
    newgame->penemies->type = -1;
    newgame->psoport->type = -1;
    newgame->score = 0;

    int i;

    for(i = 0; i < NUM_GOAL_SLOTS; i++){
        (newgame->safespaces)[i] = 0;
    }

    for(i = 0; i < NUM_HEIGHT_LEVELS; i++){
        (newgame->pspeedheight)[i] = 0;
    }

    newgame->prana->lives = 0;
    newgame->prana->height = 0;
    newgame->prana->startcoord = 0;
    newgame->prana->endcoord = ADJCOORDFROG(1);
    newgame->prana->orientation = 0;

    return newgame;

}

int endGame(game_state * game){

    if(game == NULL){
        return 1;
    }

    free(game->safespaces);
    free(game->pspeedheight);
    free(game->prana);
    free(game->psoport);
    free(game->penemies);
    free(game);

    return 0;

}
