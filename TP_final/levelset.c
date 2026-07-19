//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que             //
//  inicilaizan y actualizan el nivel, sus entidades y el jugador   //
//  Y tiene en cuenta la dificultad progresiva                      //
//                                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////




#include "levelset.h"
#include "scores.h"
#include "highscores.h"
#include "entityupdates.h"
#include "frogupdates.h"
#include <time.h>
#include <stdlib.h>

int level;

int lentypes[] = {1,1,1,1,2,3,3,7,2,5};


static int createEnemy(enemy_entity* enemigo, int tipo, int height, int heightspeed[]);
static int createSupport(support_entity* soporte, int tipo, int height, int heightspeed[]);

static int createEnemy(enemy_entity* enemigo, int tipo, int height, int heightspeed[]){

    if(enemigo == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(tipo < 0 || tipo >= 5){
        return ERROR_TIPO_INVALIDO;
    }
    else if(height < 1 || height > 5){
        return ERROR_ALTURA_INVALIDA;
    }

    enemy_entity* new_enemy = enemigo;

    for(; new_enemy->type != -1; new_enemy++); //Hago que apunte al ultimo enemigo de la lista

    new_enemy->type = tipo;
    new_enemy->height = height;

    (new_enemy+1)->type = -1; //Pongo el siguiente enemigo como vacio

    int supperposition = 1;

    while(supperposition < 50 && supperposition != 0){

        enemy_entity* temp = enemigo;

        new_enemy->startcoord = rand() % (ENDWORLD - 3 ); //Genero un numero aleatorio entre 0 y ENDWORLD para que el soporte no se salga de la pantalla
        new_enemy->endcoord = new_enemy->startcoord + ADJCOORDFROG(lentypes[tipo]);

        for(; temp->type != -1; temp++){
        
            if(temp->height == height && new_enemy->startcoord <= temp->endcoord && new_enemy->endcoord >= temp->startcoord){ //Si hay colision entre soportes, se desplaza el nuevo soporte a la derecha del ultimo soporte que colisiona con el

                supperposition++;
                break;

            }
            else{
                supperposition = 0;
            }

        }

    }

    if(supperposition == 50){

        new_enemy->type = -1;
        return ERROR_ENTIDAD_INCOLOCABLE; 

    }
    else{
    
        return 0;
    }
}

static int createSupport(support_entity* soporte, int tipo, int height, int heightspeed[]){

    if(soporte == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(tipo < 5){
        return ERROR_TIPO_INVALIDO;
    }
    else if(height < 7 || height > 11){
        return ERROR_ALTURA_INVALIDA;
    }

    support_entity* new_support = soporte;

    for(; new_support->type != -1; new_support++); //Hago que apunte al ultimo soporte de la lista

    new_support->type = tipo;
    new_support->height = height;

    (new_support+1)->type = -1; //Pongo el siguiente soporte como vacio

    int supperposition = 1;

    while(supperposition < 50 && supperposition != 0){

        support_entity* temp = soporte;

        new_support->startcoord = rand() % (ENDWORLD - 3 ); //Genero un numero aleatorio entre 0 y ENDWORLD para que el soporte no se salga de la pantalla
        new_support->endcoord = new_support->startcoord + ADJCOORDFROG(lentypes[tipo]);

        for(; temp->type != -1; temp++){
        
            if(temp->height == height && new_support->startcoord <= temp->endcoord && new_support->endcoord >= temp->startcoord){ //Si hay colision entre soportes, se desplaza el nuevo soporte a la derecha del ultimo soporte que colisiona con el

                supperposition++;
                break;

            }
            else{
                supperposition = 0;
            }

        }

    }

    if(supperposition == 50){

        new_support->type = -1;
        return ERROR_ENTIDAD_INCOLOCABLE; 

    }
    else{
    
        return 0;
    }
}

int nextLevel(game_state * game){

    srand(time(NULL));

    if(game->penemies == NULL || game->psoport == NULL|| game->prana == NULL|| game->pspeedheight == NULL || game == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(level < 1){
        return ERROR_NIVEL_INVALIDO;
    }

    game->penemies->type = -1; //Pongo el primer enemigo como vacio
    game->psoport->type = -1; //Pongo el primer soporte como vacio
    game->prana->height = 0; //Pongo la rana en la primera fila
    game->prana->startcoord = ADJCOORDFROG(3); //Pongo la rana en el inicio
    game->prana->endcoord = game->prana->startcoord + ADJCOORDFROG(1);

    int i;

    // Sin esto, isLevelFinished() seguia viendo los safespaces marcados
    // del nivel anterior y el nivel nuevo se daba por terminado antes de
    // que la rana se moviera.
    for(i = 0; i < 5; i++){
        (game->safespaces)[i] = 0;
    }

    for(i = 0; i < NUM_HEIGHT_LEVELS; i++){

        (game->pspeedheight)[i] = rand()%2 ? -(rand() % (level + 5) + level) : (rand() % (level + 5) + level); //Aumento la velocidad de los enemigos y soportes en cada nivel

    }

    for(i = 0; i<3; i++){

        createEnemy(game->penemies,0,1,game->pspeedheight);
        createEnemy(game->penemies,1,2,game->pspeedheight);
        createEnemy(game->penemies,2,3,game->pspeedheight);
        createEnemy(game->penemies,3,4,game->pspeedheight);
        createEnemy(game->penemies,4,5,game->pspeedheight);
        createSupport(game->psoport,9,11,game->pspeedheight);
        createSupport(game->psoport,6,8,game->pspeedheight);

    }

    for(i = 0; i<2; i++){

        createSupport(game->psoport,7,9,game->pspeedheight);

    }

    for(i = 0; i<4; i++){

        createSupport(game->psoport,5,7,game->pspeedheight);
        createSupport(game->psoport,8,10,game->pspeedheight);

    }

    return 0;

}

int firstLevel(game_state * game){

    srand(time(NULL));

    if(game->penemies == NULL || game->psoport == NULL|| game->prana == NULL|| game->pspeedheight == NULL|| game == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(level < 1){
        return ERROR_NIVEL_INVALIDO;
    }


    game->penemies->type = -1;
    game->psoport->type = -1;
    game->score = 0;
    game->penemies->type = -1; //Pongo el primer enemigo como vacio
    game->psoport->type = -1; //Pongo el primer soporte como vacio
    game->prana->lives = 3; // Inicializa las vidas
    game->prana->height = 0; //Pongo la rana en la primera fila
    game->prana->startcoord = ADJCOORDFROG(3); //Pongo la rana en el inicio
    game->prana->endcoord = game->prana->startcoord + ADJCOORDFROG(1); 

    int i,j;

    for(i = 0; i < 5; i++){
        (game->safespaces)[i] = 0;
    }

    for(i = 0; i < NUM_HEIGHT_LEVELS; i++){

        (game->pspeedheight)[i] = rand()%2 ? (rand() % (5) + 1) : -(rand() % (5) + 1); //Aumento la velocidad de los enemigos y soportes en cada nivel

    }

    for(i = 0; i<3; i++){

        createEnemy(game->penemies,0,1,game->pspeedheight);
        createEnemy(game->penemies,1,2,game->pspeedheight);
        createEnemy(game->penemies,2,3,game->pspeedheight);
        createEnemy(game->penemies,3,4,game->pspeedheight);
        createEnemy(game->penemies,4,5,game->pspeedheight);
        createSupport(game->psoport,9,11,game->pspeedheight);
        createSupport(game->psoport,6,8,game->pspeedheight);

    }

    for(i = 0; i<2; i++){

        createSupport(game->psoport,7,9,game->pspeedheight);

    }

    for(i = 0; i<4; i++){

        createSupport(game->psoport,5,7,game->pspeedheight);
        createSupport(game->psoport,8,10,game->pspeedheight);

    }

    return 0;

}

int updateLevel(game_state * game,int time){

    if(game == NULL){

        return ERROR_NULL_POINTER;

    }
    
    if(isDeadLake(game) == 1 || isDeadFromEnemy(game) == 1){

        game->prana->lives--; //Le saco una vida
        game->prana->height = 0; //Pongo la rana en la primera fila
        game->prana->startcoord = ADJCOORDFROG(3); //Pongo la rana en el inicio
        game->prana->endcoord = game->prana->startcoord + ADJCOORDFROG(1); 
    }
    else if(isAtEnd(game)){

        game->prana->height = 0; //Pongo la rana en la primera fila
        game->prana->startcoord = ADJCOORDFROG(3); //Pongo la rana en el inicio
        game->prana->endcoord = game->prana->startcoord + ADJCOORDFROG(1);
        pointsForTime(game,time); 

    }


    if(isLevelFinished(game)){

        pointForFinishingLevel(game); //Añado puntos por terminar , subo el nivel

        level++;

        nextLevel(game);

    }
    else if(game->prana->lives < 1){

        updateHighScores("AAA",game->score);

        endGame(game); // libera todo game_state: el llamador NO debe volver a tocar `game` despues de esto.

        return GAME_OVER;

    }
    else{

        stepEntites(game);
        resetEntites(game);
        if(game->prana->height>=STARTLAKE){

            followSupport(game);

        }

    }

    return 0;

}
