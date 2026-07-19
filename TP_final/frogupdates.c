//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que actualizan  //
//  al jugador y resguardan que este permanezaca en la zona         //
//  jugable                                                         //
//                                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////





#include "frogupdates.h"

int FollowingSupp = 0;
int FlagDied = 0;
int MovedUP = 0;
int MovedDOWN = 0;
int MovedRIGHT = 0;
int MovedLEFT = 0;

int followSupport(game_state * game){

    if(game == NULL||game->psoport == NULL||game->prana == NULL){

        return ERROR_NULL_POINTER;

    }

    if(isDeadLake(game) == 0){//Si esta sobre un soporte hacer que siga dicho soporte
        
        game->prana->startcoord+=(game->pspeedheight)[game->prana->height];
        game->prana->endcoord+=(game->pspeedheight)[game->prana->height];

        if(!isInBounds(game)){

            game->prana->startcoord-=(game->pspeedheight)[game->prana->height];
            game->prana->endcoord-=(game->pspeedheight)[game->prana->height];

        }

    }

    return 0;

}

int deathOfFrog(game_state * game){

    if(game->psoport == NULL|| game->penemies == NULL || game == NULL || game->prana == NULL){

        return ERROR_NULL_POINTER;

    }



    if(isDeadFromEnemy(game) == 1||isDeadLake(game) == 1){

        game->prana->lives--;
        game->prana->height = 0;
        game->prana->startcoord = ADJCOORDFROG(3);
        game->prana->endcoord = game->prana->startcoord + ADJCOORDFROG(1);
        FlagDied = 1;
    }

    return 0;

}

int frogStepUp(game_state * game){

   if(game->prana == NULL || game == NULL){

        return ERROR_NULL_POINTER;

    }
   
    MovedUP = 1;
    game->prana->height++;
    game->prana->orientation = 0;

    if(!isInBounds(game)){

        game->prana->height--;

    }

    return 0;

}

int frogStepDown(game_state * game){

    if(game->prana == NULL || game == NULL){

        return ERROR_NULL_POINTER;

    }

    MovedDOWN = 1;
    game->prana->height--;
    game->prana->orientation = 2;

    if(!isInBounds(game)){

        game->prana->height++;

    }

    return 0;

}

int frogStepRight(game_state * game){

    if(game->prana == NULL || game == NULL){

        return ERROR_NULL_POINTER;

    }
    MovedRIGHT = 1;
    game->prana->orientation = 1;
    game->prana->startcoord+=ADJCOORDFROG(1);
    game->prana->endcoord+=ADJCOORDFROG(1);

    if(!isInBounds(game)){

        game->prana->startcoord-=ADJCOORDFROG(1);
        game->prana->endcoord-=ADJCOORDFROG(1);

    }

    return 0;


}

int frogStepLeft(game_state * game){

    if(game->prana == NULL || game == NULL){

        return ERROR_NULL_POINTER;

    }
    MovedLEFT = 1;
    game->prana->orientation = 2;
    game->prana->startcoord-=ADJCOORDFROG(1);
    game->prana->endcoord-=ADJCOORDFROG(1);

    if(!isInBounds(game)){

        game->prana->startcoord+=ADJCOORDFROG(1);
        game->prana->endcoord+=ADJCOORDFROG(1);

    }


    return 0;

}

int isInBounds(game_state * game){

    if((game->prana->startcoord<0)||(game->prana->endcoord>ENDWORLD)||(game->prana->height<0)||(!isAtEnd(game))){

        return 0;

    }
    else{

        return 1;

    }

}
