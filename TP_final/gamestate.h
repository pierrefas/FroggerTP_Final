#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "entidades.h"


typedef struct{

    frog_player* prana;
    support_entity* psoport;
    enemy_entity* penemies;
    int * pspeedheight;
    int score;

}game_state;


#endif