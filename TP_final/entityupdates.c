//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que actualizan  //
//  el estado de las entidades del juego                            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "entityupdates.h"

int stepEntites(game_state * game){

    int i;

    if(game == NULL || game->penemies == NULL || game->psoport == NULL || game->pspeedheight == NULL){
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

        support_entity * soporte = game->psoport + i;
        int len = soporte->endcoord - soporte->startcoord;
        int speed = (game->pspeedheight)[soporte->height];

        if(speed < 0 && soporte->endcoord < 0){

            /* Salio por la izquierda: reaparece pegado al borde derecho */
            soporte->startcoord = ENDWORLD;
            soporte->endcoord = ENDWORLD + len;

        }
        else if(speed > 0 && soporte->startcoord > ENDWORLD){

            /* Salio por la derecha: reaparece pegado al borde izquierdo */
            soporte->endcoord = 0;
            soporte->startcoord = -len;

        }

    }

    for(i = 0; (game->penemies + i)->type != -1; i++){

        enemy_entity * enemigo = game->penemies + i;
        int len = enemigo->endcoord - enemigo->startcoord;
        int speed = (game->pspeedheight)[enemigo->height];

        if(speed < 0 && enemigo->endcoord < 0){

            enemigo->startcoord = ENDWORLD;
            enemigo->endcoord = ENDWORLD + len;

        }
        else if(speed > 0 && enemigo->startcoord > ENDWORLD){

            enemigo->endcoord = 0;
            enemigo->startcoord = -len;

        }

    }

    return 0;

}
