#ifndef ENTIDADES-H
#define ENTIDADES-H


#include <stdlib.h>

#define ERROR_NULL_POINTER -67

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

#endif