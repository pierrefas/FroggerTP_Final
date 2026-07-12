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
#include "entidades.h"




int isDeadFromEnemy(frog_player * rana, enemy_entity * enemigos){

    if(!enemigos){

        return ERROR_NULL_POINTER; //Chequeo que los posibles obstaculos sean validos

    }

    int i;

    for(i = 0; (enemigos + i)->type != -1; i++){

        if ((rana->height == (enemigos + i)->height)&&
        ((rana->startcoord <= (enemigos + i)->endcoord)&&(rana->startcoord >= (enemigos + i)->startcoord))
        ||((rana->endcoord <= (enemigos + i)->endcoord)&&(rana->endcoord >= (enemigos + i)->startcoord))){

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

            if((rana->startcoord>=(soporte + i)->startcoord)&&(rana->endcoord<=(soporte + i)->endcoord)&&(rana->height == (soporte + i)->height)){

                return 0; //Si estando en el lago esta sobre un soporte vive

            }

        }
    }
    
<<<<<<< HEAD
    return 1; // <- chiche OJO con esto !!!!
=======
    return 1;
>>>>>>> fe8d770eb3902547aa9245293c7435904d2a9a17

}