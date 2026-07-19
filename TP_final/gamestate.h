#ifndef GAMESTATE_H
#define GAMESTATE_H

#define ADJCOORDFROG(n) (n * 16) //Esta macro me permite ajustar la coordenada de la rana a la coordenada de la pantalla, ya que la rana se mueve en pasos de 16 pixeles.
#define ERROR_NULL_POINTER -67 //Esta macro me permite definir un error de puntero nulo, que se usa en las funcioens del backend
#define ENDWORLD (14*16) //Esta macro me permite definir el final del mundo, que se usa para resetear las entidades cuando salen de la pantalla.

// Cantidad de "alturas" indexables en pspeedheight (alturas de enemigos:
// 1-5, de soportes: 5-11, y la rana llega a leer/escribir hasta la fila
// segura, altura >= 12). Antes pspeedheight se reservaba con malloc(10 *
// sizeof(int)) pero se escribian/leian los indices 0..12: heap overflow
// en cada inicio de nivel. Usar esta constante en gamestate.c y
// levelset.c para que ambos coincidan siempre.
#define NUM_HEIGHT_LEVELS 13

#include <stdlib.h>
#include <stdio.h>

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



typedef struct{

    frog_player* prana;
    support_entity* psoport;
    enemy_entity* penemies;
    int * pspeedheight;
    int score;
    int * safespaces;

}game_state;

game_state * createGame(void);
int endGame(game_state* game);

#endif