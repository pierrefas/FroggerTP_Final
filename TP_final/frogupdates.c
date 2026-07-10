#include "frogupdates.h"
#include "checking.h"
#include "entidades.h"

void followSupport(frog_player * rana, support_entity * soporte, int speedheight[]){

    if(soporte == NULL){

        return;

    }

    if(isDeadLake(rana,soporte) == 0){//Si esta sobre un soporte hacer que siga dicho soporte

        rana->startcoord+=speedheight[rana->height];
        rana->endcoord+=speedheight[rana->height];
    }

}

int deathOfFrog(frog_player * rana, support_entity * soporte, enemy_entity * enemigos){

    if(soporte == NULL||enemigos == NULL){

        return ERROR_CHECK;

    }



    if(isDeadFromEnemy(rana,enemigos) == 1||isDeadLake(rana, soporte) == 1){

        rana->lives--;
        rana->height = 0;
        rana->startcoord = ADJCOORDFROG(3);
        rana->endcoord = rana->startcoord + ADJCOORDFROG(1);

    }

}

void frogStepUp(frog_player * rana){

    rana->height++;

    if(!isInBounds(rana)){

        rana->height--;

    }


}

void frogStepDown(frog_player * rana){

    rana->height--;

    if(!isInBounds(rana)){

        rana->height++;

    }

}

void frogStepRight(frog_player * rana){


    rana->startcoord+=ADJCOORDFROG(1);
    rana->endcoord+=ADJCOORDFROG(1);

    if(!isInBounds(rana)){

        rana->startcoord-=ADJCOORDFROG(1);
        rana->endcoord-=ADJCOORDFROG(1);

    }

}

void frogStepLeft(frog_player * rana){

    rana->startcoord-=ADJCOORDFROG(1);
    rana->endcoord-=ADJCOORDFROG(1);

    if(!isInBounds(rana)){

        rana->startcoord+=ADJCOORDFROG(1);
        rana->endcoord+=ADJCOORDFROG(1);

    }


}

int isInBounds(frog_player * rana){

    if((rana->startcoord<0)||(rana->endcoord>256)||(rana->height<0)||
    ((rana->height>12)&&
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
