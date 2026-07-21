//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que verfican    //
//  si el jugador esta vivo o muerto, y si esta en una casilla      //
//  segura del final                                                //
//                                                                  //
//////////////////////////////////////////////////////////////////////
#include "checking.h"


int goalSlotAt(const frog_player * rana){

    if(rana == NULL){
        return -1;
    }

    int i;

    for(i = 0; i < NUM_GOAL_SLOTS; i++){

        if(rana->startcoord + HITBOX_MARGIN*4  >= GOAL_SLOT_X(i) && rana->endcoord - HITBOX_MARGIN*4 < GOAL_SLOT_X(i) + ADJCOORDFROG(1)){
            return i;
        }

    }

    return -1;

}

int isDeadFromEnemy(game_state * state){

    if(!state || !state->penemies || !state->prana){
        return ERROR_NULL_POINTER;
    }

    frog_player * rana = state->prana;
    int i;

    for(i = 0; (state->penemies + i)->type != -1; i++){

        enemy_entity * enemigo = state->penemies + i;

        if(rana->height == enemigo->height && rana->endcoord - HITBOX_MARGIN > enemigo->startcoord &&
           rana->startcoord + HITBOX_MARGIN < enemigo->endcoord){

            return 1; //Si se solapa con un enemigo de su misma fila, muere

        }

    }

    return 0;

}

int isDeadLake(game_state * state){

    if(!state || !state->psoport || !state->prana){
        return ERROR_NULL_POINTER;
    }

    frog_player * rana = state->prana;

    if(rana->height < STARTLAKE || rana->height > ENDLAKE){
        return 0; //Fuera del lago no se puede ahogar
    }

    int center = rana->startcoord + ADJCOORDFROG(1) / 2;
    int i;

    for(i = 0; (state->psoport + i)->type != -1; i++){

        support_entity * soporte = state->psoport + i;

        if(soporte->supporting && rana->height == soporte->height &&
           center >= soporte->startcoord && center <= soporte->endcoord){

            return 0; //El centro de la rana esta sobre un soporte: flota

        }

    }

    return 1; //Esta en el lago y sin soporte debajo: se ahoga

}

int isAtEnd(game_state * state){

    if(!state || !state->prana || !state->safespaces){
        return ERROR_NULL_POINTER;
    }

    if(state->prana->height < GOALROW){
        return 0;
    }

    int slot = goalSlotAt(state->prana);

    if(slot >= 0 && (state->safespaces)[slot] == 0){

        (state->safespaces)[slot] = 1; //Reclamo el hueco-meta
        return 1;

    }

    return 0;

}

int isLevelFinished(game_state * game){

    if(game == NULL || game->safespaces == NULL){
        return ERROR_NULL_POINTER;
    }

    int i;

    for(i = 0; i < NUM_GOAL_SLOTS; i++){

        if((game->safespaces)[i] == 0){
            return 0;
        }

    }

    return 1;

}
