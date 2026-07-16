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

int followSupport(frog_player * rana, support_entity * soporte, int speedheight[]){

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

int frogStepUp(frog_player * rana){

   if(rana == NULL){

        return ERROR_NULL_POINTER;

    }
   
   
    rana->height++;

    if(!isInBounds(rana)){

        rana->height--;

    }

    return 0;

}

int frogStepDown(frog_player * rana){

    if(rana == NULL){   

        return ERROR_NULL_POINTER;

    }


    rana->height--;

    if(!isInBounds(rana)){

        rana->height++;

    }

    return 0;

}

int frogStepRight(frog_player * rana){

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

int frogStepLeft(frog_player * rana){

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

    if((rana->startcoord<0)||(rana->endcoord>ENDWORLD)||(rana->height<0)||(!ISINSAFEZONE(rana))){

        return 0;

    }
    else{

        return 1;

    }

}
