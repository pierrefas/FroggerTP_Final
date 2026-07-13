//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que verfican    //
//  si el jugador esta vivo o muerto, y si esta en una casilla      //
//  segura del final                                                //
//                                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////
#include "checking.h"


int isDeadFromEnemy(frog_player * rana, enemy_entity * enemigos){

    if(!enemigos){

        return ERROR_NULL_POINTER; //Chequeo que los posibles obstaculos sean validos

    }

    int i;

    for(i = 0; (enemigos + i)->type != -1; i++){

        if ((rana->height == (enemigos + i)->height)&&(rana->endcoord>=enemigos->startcoord)&&(rana->startcoord<=enemigos->endcoord)){

            return 1; //Si esta en el mismo lugar qeu un enemigo muere, esto es independiente de donde este en el juego

        }

    }

    return 0;

}

int isDeadLake(frog_player * rana, support_entity * soporte){

    if(!soporte){

        return ERROR_NULL_POINTER; //Chequeo que los posibles soportes sean validos

    }

    int i;

    if(rana->height >= STARTLAKE){

        for(i = 0; (soporte + i)->type != -1; i++){

            if((soporte->supporting)&&(rana->startcoord>=(soporte + i)->startcoord)&&(rana->endcoord<=(soporte + i)->endcoord)&&(rana->height == (soporte + i)->height)){

                return 0; //Si estando en el lago esta sobre un soporte vive

            }

        }
    }
    
    return 1; //Si esta en el lago y no esta sobre un soporte muere

}