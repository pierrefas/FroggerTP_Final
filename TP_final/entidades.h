#ifndef ENTIDADES_H
#define ENTIDADES_H


#include <stdlib.h>
#include <time.h>


#define ADJCOORDFROG(n) (n * 16) //Esta macro me permite ajustar la coordenada de la rana a la coordenada de la pantalla, ya que la rana se mueve en pasos de 16 pixeles.
#define ERROR_NULL_POINTER -67 //Esta macro me permite definir un error de puntero nulo, que se usa en las funcioens del backend
#define ENDWORLD (14*16) //Esta macro me permite definir el final del mundo, que se usa para resetear las entidades cuando salen de la pantalla.

extern int lentypes[];


typedef struct {    //Defino todos los tipos de entidades que voy a usar en el juego, tanto enemigos como soportes y la rana.

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
    int orientation;

} frog_player;


#endif