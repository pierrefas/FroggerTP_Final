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


int isDeadFromEnemy(game_state * state){

    if(!state || !state->penemies || !state->prana){

        return ERROR_NULL_POINTER; //Chequeo que los posibles obstaculos y la rana sean validos

    }

    frog_player * rana = state->prana;
    int i;

    for(i = 0; (state->penemies + i)->type != -1; i++){

        if ((rana->height == (state->penemies + i)->height) && (rana->endcoord >= (state->penemies + i)->startcoord) && (rana->startcoord <= (state->penemies + i)->endcoord)){

            return 1; //Si esta en el mismo lugar que un enemigo muere, esto es independiente de donde este en el juego

        }

    }

    return 0;

}

int isDeadLake(game_state * state){

    if(!state || !state->psoport || !state->prana){

        return ERROR_NULL_POINTER; //Chequeo que los posibles soportes y la rana sean validos

    }

    frog_player * rana = state->prana;
    int i;


    for(i = 0; (state->psoport + i)->type != -1; i++){

        if((rana->height < STARTLAKE) || ((state->psoport + i)->supporting && (rana->startcoord >= (state->psoport + i)->startcoord) && (rana->endcoord <= (state->psoport + i)->endcoord) && (rana->height == (state->psoport + i)->height))){

            return 0; //Si estando en el lago esta sobre un soporte vive

        }

    }
    
    return 1; //Si esta en el lago y no esta sobre un soporte muere

}

int isAtEnd(game_state* state){

    if(!state || !state->prana){

        return ERROR_NULL_POINTER;

    }

    frog_player * rana = state->prana;

    if(ISINSAFEZONE(rana)){

        if((state->prana->startcoord>=12)&&(state->prana->endcoord<=28)&&((state->safespaces)[0] != 1)){

            (state->safespaces)[0] = 1;
            return 1;

        }
        else if((state->prana->startcoord>=52)&&(state->prana->endcoord<=68)&&((state->safespaces)[1] != 1)){

            (state->safespaces)[1] = 1;
            return 1;

        }
        else if((state->prana->startcoord>=92)&&(state->prana->endcoord<=108)&&((state->safespaces)[2] != 1)){

            (state->safespaces)[2] = 1;
            return 1;

        }
        else if((state->prana->startcoord>=132)&&(state->prana->endcoord<=148)&&((state->safespaces)[3] != 1)){

            (state->safespaces)[3] = 1;
            return 1;

        }
        else if((state->prana->startcoord>=172)&&(state->prana->endcoord<=188)&&((state->safespaces)[4] != 1)){

            (state->safespaces)[4] = 1;
            return 1;

        }
        else{

            return 0;

        }
        

    }
    else{

        return 0;

    }
}