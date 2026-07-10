#include "entidades.h"
#include "entityupdates.h"


int stepEntites(enemy_entity* enemigo, support_entity* soporte, int speedheight[]){

    int i;

    if(enemigo == NULL || soporte == NULL || speedheight == NULL){

        return ERROR_NULL_POINTER;

    }

    for(i = 0; (soporte + i)->type != -1; i++){

        (soporte + i)->startcoord += speedheight[(soporte + i)->height];
        (soporte + i)->endcoord += speedheight[(soporte + i)->height];

    }
    for(i = 0; (enemigo + i)->type != -1; i++){

        (enemigo + i)->startcoord += speedheight[(enemigo + i)->height];
        (enemigo + i)->endcoord += speedheight[(enemigo + i)->height];

    }

    return 0;

}

int resetEntites(enemy_entity* enemigo, support_entity* soporte, int speedheight[]){

    int i;

    if(enemigo == NULL || soporte == NULL || speedheight == NULL){

        return ERROR_NULL_POINTER;

    }

    for(i = 0; (soporte + i)->type != -1; i++){

        if(speedheight[(soporte + i)->height] < 0){

            if((soporte + i)->endcoord < 0){

                int temp = (soporte + i)->startcoord - (soporte + i)->endcoord; 

                (soporte + i)->startcoord = 256;
                (soporte + i)->endcoord = 256 + temp;


            }

        }
        else if(speedheight[(soporte + i)->height] > 0){

            if((soporte + i)->startcoord > 256){

                int temp = (soporte + i)->endcoord - (soporte + i)->startcoord; 

                (soporte + i)->endcoord = 0;
                (soporte + i)->startcoord = 0 - temp;

            }

        }

    }
    for(i = 0; (enemigo + i)->type != -1; i++){

        if(speedheight[(enemigo + i)->height] < 0){

            if((enemigo + i)->endcoord < 0){

                int temp = (enemigo + i)->startcoord - (enemigo + i)->endcoord; 

                (enemigo + i)->startcoord = 256;
                (enemigo + i)->endcoord = 256 + temp;
            }
        }
        else if(speedheight[(enemigo + i)->height] > 0){

            if((enemigo + i)->startcoord > 256){

                int temp = (enemigo + i)->endcoord - (enemigo + i)->startcoord; 

                (enemigo + i)->endcoord = 0;
                (enemigo + i)->startcoord = 0 - temp;

            }

        }

    }

    return 0;

}


