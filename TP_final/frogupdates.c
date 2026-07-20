//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que actualizan  //
//  al jugador y resguardan que este permanezaca en la zona         //
//  jugable                                                         //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "frogupdates.h"

/* Columna donde arranca la rana (centro de la fila de salida) */
#define FROG_START_COL 6

int resetFrogPos(game_state * game){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    game->prana->height = 0;
    game->prana->startcoord = ADJCOORDFROG(FROG_START_COL);
    game->prana->endcoord = game->prana->startcoord + ADJCOORDFROG(1);
    game->prana->orientation = 0;

    return 0;

}

int loseLife(game_state * game){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    game->prana->lives--;
    resetFrogPos(game);

    return game->prana->lives < 1;

}

int followSupport(game_state * game){

    if(game == NULL || game->psoport == NULL || game->prana == NULL || game->pspeedheight == NULL){
        return ERROR_NULL_POINTER;
    }

    if(game->prana->height < STARTLAKE || game->prana->height > ENDLAKE){
        return 0; //Solo aplica en las filas del lago
    }

    if(isDeadLake(game) == 0){ //Si esta sobre un soporte, la arrastra con su velocidad

        int speed = (game->pspeedheight)[game->prana->height];

        game->prana->startcoord += speed;
        game->prana->endcoord += speed;

        if(!isInBounds(game)){ //En el borde del mundo se queda clavada (el soporte sigue)

            game->prana->startcoord -= speed;
            game->prana->endcoord -= speed;

        }

    }

    return 0;

}

int frogStepUp(game_state * game){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    game->prana->height++;
    game->prana->orientation = 0;

    if(!isInBounds(game)){
        game->prana->height--;
    }

    return 0;

}

int frogStepDown(game_state * game){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    game->prana->height--;
    game->prana->orientation = 2;

    if(!isInBounds(game)){
        game->prana->height++;
    }

    return 0;

}

int frogStepRight(game_state * game){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    game->prana->orientation = 1;
    game->prana->startcoord += ADJCOORDFROG(1);
    game->prana->endcoord += ADJCOORDFROG(1);

    if(!isInBounds(game)){
        game->prana->startcoord -= ADJCOORDFROG(1);
        game->prana->endcoord -= ADJCOORDFROG(1);
    }

    return 0;

}

int frogStepLeft(game_state * game){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    game->prana->orientation = 3;
    game->prana->startcoord -= ADJCOORDFROG(1);
    game->prana->endcoord -= ADJCOORDFROG(1);

    if(!isInBounds(game)){
        game->prana->startcoord += ADJCOORDFROG(1);
        game->prana->endcoord += ADJCOORDFROG(1);
    }

    return 0;

}

int isInBounds(game_state * game){

    if(game == NULL || game->prana == NULL || game->safespaces == NULL){
        return 0;
    }

    frog_player * rana = game->prana;

    if(rana->startcoord < 0 || rana->endcoord > ENDWORLD ||
       rana->height < 0 || rana->height > GOALROW){
        return 0;
    }

    /* A la fila de llegada solo se puede subir cayendo en un hueco-meta
     * libre; en cualquier otra posicion el movimiento es invalido. */
    if(rana->height == GOALROW){

        int slot = goalSlotAt(rana);

        if(slot < 0 || (game->safespaces)[slot] != 0){
            return 0;
        }

    }

    return 1;

}
