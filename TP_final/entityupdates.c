//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que actualizan  //
//  el estado de las entidades del juego                            //
//                                                                  //
//                                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "entityupdates.h"


int stepEntites(game_state * game){

    int i;

    if(game->penemies == NULL || game->psoport == NULL || game->pspeedheight == NULL || game == NULL){

        return ERROR_NULL_POINTER;

    }

    for(i = 0; (game->psoport + i)->type != -1; i++){

        (game->psoport + i)->startcoord += (game->pspeedheight)[(game->psoport + i)->height];
        (game->psoport + i)->endcoord += (game->pspeedheight)[(game->psoport + i)->height];

    }
    for(i = 0; (game->penemies + i)->type != -1; i++){

        (game->penemies + i)->startcoord += (game->pspeedheight)[(game->penemies + i)->height];
        (game->penemies + i)->endcoord += (game->pspeedheight)[(game->penemies + i)->height];

    }


    return 0;

}

int resetEntites(game_state * game){

    int i;

    if(game == NULL || game->psoport == NULL || game->pspeedheight == NULL || game->penemies == NULL){
        return ERROR_NULL_POINTER;
    }

    for(i = 0; (game->psoport + i)->type != -1; i++){

        if(game->pspeedheight[(game->psoport + i)->height] < 0){

            if((game->psoport + i)->endcoord < 0){

                int temp = (game->psoport + i)->startcoord - (game->psoport + i)->endcoord; 

                (game->psoport + i)->startcoord = ENDWORLD;
                (game->psoport + i)->endcoord = ENDWORLD + temp;


            }

        }
        else if(game->pspeedheight[(game->psoport + i)->height] > 0){

            if((game->psoport + i)->startcoord > ENDWORLD){

                int temp = (game->psoport + i)->endcoord - (game->psoport + i)->startcoord; 

                (game->psoport + i)->endcoord = 0;
                (game->psoport + i)->startcoord = 0 - temp;

            }

        }

    }
    for(i = 0; (game->penemies + i)->type != -1; i++){

        if(game->pspeedheight[(game->penemies + i)->height] < 0){

            if((game->penemies + i)->endcoord < 0){

                int temp = (game->penemies + i)->startcoord - (game->penemies + i)->endcoord; 

                (game->penemies + i)->startcoord = ENDWORLD;
                (game->penemies + i)->endcoord = ENDWORLD + temp;
            }
        }
        else if(game->pspeedheight[(game->penemies + i)->height] > 0){

            if((game->penemies + i)->startcoord > ENDWORLD){

                int temp = (game->penemies + i)->endcoord - (game->penemies + i)->startcoord; 

                (game->penemies + i)->endcoord = 0;
                (game->penemies + i)->startcoord = 0 - temp;

            }

        }

    }

    return 0;

}
