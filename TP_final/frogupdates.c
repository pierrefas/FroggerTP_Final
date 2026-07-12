//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que actalizan   //
//  al jugador y resguardan que este permanezaca en la zona         //
//  jugable                                                         //
//                                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////





#include "frogupdates.h"
#include "checking.h"
#include "entidades.h"

void followSupport(frog_player * rana, support_entity * soporte, int speedheight[]){

    if(soporte == NULL){

        return ERROR_NULL_POINTER;

    }

    if(isDeadLake(rana,soporte) == 0){//Si esta sobre un soporte hacer que siga dicho soporte

        rana->startcoord+=speedheight[rana->height];
        rana->endcoord+=speedheight[rana->height];
    }

    return 0;

}

int deathOfFrog(frog_player * rana, support_entity * soporte, enemy_entity * enemigos){

    if(soporte == NULL||enemigos == NULL){

        return ERROR_NULL_POINTER;

    }



    if(isDeadFromEnemy(rana,enemigos) == 1||isDeadLake(rana, soporte) == 1){

        rana->lives--;
        rana->height = 0;
        rana->startcoord = ADJCOORDFROG(3);
        rana->endcoord = rana->startcoord + ADJCOORDFROG(1);

    }

    return 0;

}

void frogStepUp(frog_player * rana){

   if(rana == NULL){

        return ERROR_NULL_POINTER;

    }
   
   
    rana->height++;

    if(!isInBounds(rana)){

        rana->height--;

    }

    return 0;

}

void frogStepDown(frog_player * rana){

    if(rana == NULL){   

        return ERROR_NULL_POINTER;

    }


    rana->height--;

    if(!isInBounds(rana)){

        rana->height++;

    }

    return 0;

}

void frogStepRight(frog_player * rana){

    if(rana == NULL){

        return ERROR_NULL_POINTER;

    }


    rana->startcoord+=ADJCOORDFROG(1);
    rana->endcoord+=ADJCOORDFROG(1);

    if(!isInBounds(rana)){

        rana->startcoord-=ADJCOORDFROG(1);
        rana->endcoord-=ADJCOORDFROG(1);

    }

    return 0;


}

void frogStepLeft(frog_player * rana){

    if(rana == NULL){

        return ERROR_NULL_POINTER;

    }


    rana->startcoord-=ADJCOORDFROG(1);
    rana->endcoord-=ADJCOORDFROG(1);

    if(!isInBounds(rana)){

        rana->startcoord+=ADJCOORDFROG(1);
        rana->endcoord+=ADJCOORDFROG(1);

    }


    return 0;

}

int isInBounds(frog_player * rana){

    if((rana->startcoord<0)||(rana->endcoord>ENDWORLD)||(rana->height<0)||
    ((rana->height>11)&&
    !(((rana->startcoord>=12)&&(rana->endcoord<=28))
    ||((rana->startcoord>=52)&&(rana->endcoord<=68))) //Si la rana NO esta en una casilla del final y se quiere mover a la ultima fila
    ||((rana->startcoord>=92)&&(rana->endcoord<=108))
    ||((rana->startcoord>=132)&&(rana->endcoord<=148))
    ||((rana->startcoord>=172)&&(rana->endcoord<=188)))){


        return 0;

    }
    else{

        return 1;

    }

}
