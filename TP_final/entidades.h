#ifndef ENTIDADES-H
#define ENTIDADES-H


#include <stdlib.h>
#include <time.h>


#define ADJCOORDFROG(n) (n * 16)
#define ERROR_NULL_POINTER -67

extern int lentypes[];


typedef struct {

    int startcoord;
    int endcoord;
    int height;
    int type;

} enemy_entity;

typedef struct {

    int startcoord;
    int endcoord;
    int height;
    int type;
    int supporting;

} support_entity;

typedef struct {

    int startcoord;
    int endcoord;
    int height;
    int lives;

} frog_player;

int nextLevel(int level, enemy_entity* enemigos, support_entity* soportes, int heightspeed[],frog_player* rana);

#endif