//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que             //
//  inicilaizan y actualizan el nivel, sus entidades y el jugador   //
//  Y tiene en cuenta la dificultad progresiva                      //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "levelset.h"
#include "scores.h"
#include "entityupdates.h"
#include "frogupdates.h"
#include <time.h>
#include <stdlib.h>

int level;

/* Largo (en casilleros) de cada tipo de entidad: 0..4 enemigos, 5..9
 * soportes. drawleds.c (Raspberry Pi) tambien lo usa via extern. */
int lentypes[] = {1, 1, 1, 1, 2, 3, 3, 7, 2, 5};

/* Tope de velocidad por fila (px/tick) para que los niveles altos sigan
 * siendo jugables; la dificultad progresiva sube el promedio, no el tope. */
#define MAX_ROW_SPEED 6

/* Separacion minima (px) entre entidades de una misma fila. */
#define ENTITY_MIN_GAP 8

/* Intentos de ubicacion aleatoria antes de dar por incolocable. */
#define PLACE_ATTEMPTS 50

static int createEnemy(enemy_entity * enemigo, int tipo, int height);
static int createSupport(support_entity * soporte, int tipo, int height);
static int setupLevel(game_state * game);
static int rowSpeed(void);

static int createEnemy(enemy_entity * enemigo, int tipo, int height){

    if(enemigo == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(tipo < 0 || tipo >= 5){
        return ERROR_TIPO_INVALIDO;
    }
    else if(height < 1 || height > 5){
        return ERROR_ALTURA_INVALIDA;
    }

    enemy_entity * new_enemy = enemigo;

    for(; new_enemy->type != -1; new_enemy++); //Apunto al primer lugar libre

    if(new_enemy - enemigo >= MAX_ENTITIES - 1){
        return ERROR_ENTIDAD_INCOLOCABLE; //Sin lugar para la entidad + centinela
    }

    new_enemy->type = tipo;
    new_enemy->height = height;
    (new_enemy + 1)->type = -1; //Nuevo centinela de fin de lista

    int len = ADJCOORDFROG(lentypes[tipo]);
    int attempt;
    int placed = 0;

    for(attempt = 0; attempt < PLACE_ATTEMPTS && !placed; attempt++){

        new_enemy->startcoord = rand() % (ENDWORLD - len); //Posicion al azar dentro del mundo
        new_enemy->endcoord = new_enemy->startcoord + len;

        placed = 1;

        enemy_entity * temp;

        for(temp = enemigo; temp->type != -1; temp++){

            if(temp == new_enemy){
                continue; //No compararse consigo mismo
            }

            if(temp->height == height &&
               new_enemy->startcoord <= temp->endcoord + ENTITY_MIN_GAP &&
               new_enemy->endcoord >= temp->startcoord - ENTITY_MIN_GAP){

                placed = 0; //Pisa a otro de su fila: reintento en otra posicion
                break;

            }

        }

    }

    if(!placed){
        new_enemy->type = -1;
        return ERROR_ENTIDAD_INCOLOCABLE;
    }

    return 0;

}

static int createSupport(support_entity * soporte, int tipo, int height){

    if(soporte == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(tipo < 5 || tipo >= 10){
        return ERROR_TIPO_INVALIDO;
    }
    else if(height < STARTLAKE || height > ENDLAKE){
        return ERROR_ALTURA_INVALIDA;
    }

    support_entity * new_support = soporte;

    for(; new_support->type != -1; new_support++); //Apunto al primer lugar libre

    if(new_support - soporte >= MAX_ENTITIES - 1){
        return ERROR_ENTIDAD_INCOLOCABLE;
    }

    new_support->type = tipo;
    new_support->height = height;
    new_support->supporting = 1; //Por ahora todos los soportes llevan a la rana
    (new_support + 1)->type = -1;

    int len = ADJCOORDFROG(lentypes[tipo]);
    int attempt;
    int placed = 0;

    for(attempt = 0; attempt < PLACE_ATTEMPTS && !placed; attempt++){

        new_support->startcoord = rand() % (ENDWORLD - len);
        new_support->endcoord = new_support->startcoord + len;

        placed = 1;

        support_entity * temp;

        for(temp = soporte; temp->type != -1; temp++){

            if(temp == new_support){
                continue;
            }

            if(temp->height == height &&
               new_support->startcoord <= temp->endcoord + ENTITY_MIN_GAP &&
               new_support->endcoord >= temp->startcoord - ENTITY_MIN_GAP){

                placed = 0;
                break;

            }

        }

    }

    if(!placed){
        new_support->type = -1;
        return ERROR_ENTIDAD_INCOLOCABLE;
    }

    return 0;

}

/* Velocidad aleatoria de una fila: el rango crece con el nivel. */
static int rowSpeed(void){

    int speed = 1 + rand() % (level + 2);

    if(speed > MAX_ROW_SPEED){
        speed = MAX_ROW_SPEED;
    }

    return (rand() % 2) ? speed : -speed;

}

/* Arma un nivel: limpia listas y huecos-meta, repone la rana, sortea
 * velocidades y crea las entidades. Comun a firstLevel y nextLevel. */
static int setupLevel(game_state * game){

    if(game == NULL || game->penemies == NULL || game->psoport == NULL ||
       game->prana == NULL || game->pspeedheight == NULL || game->safespaces == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(level < 1){
        return ERROR_NIVEL_INVALIDO;
    }

    game->penemies->type = -1; //Listas vacias
    game->psoport->type = -1;
    resetFrogPos(game);

    int i;

    for(i = 0; i < NUM_GOAL_SLOTS; i++){
        (game->safespaces)[i] = 0;
    }

    for(i = 0; i < NUM_HEIGHT_LEVELS; i++){
        (game->pspeedheight)[i] = rowSpeed();
    }

    /* Las filas seguras no arrastran nada */
    (game->pspeedheight)[0] = 0;
    (game->pspeedheight)[SAFEROW] = 0;
    (game->pspeedheight)[GOALROW] = 0;

    for(i = 0; i < 3; i++){

        createEnemy(game->penemies, 0, 1);
        createEnemy(game->penemies, 1, 2);
        createEnemy(game->penemies, 2, 3);
        createEnemy(game->penemies, 3, 4);
        createEnemy(game->penemies, 4, 5);
        createSupport(game->psoport, 9, 11);
        createSupport(game->psoport, 6, 8);

    }

    for(i = 0; i < 2; i++){
        createSupport(game->psoport, 7, 9);
    }

    for(i = 0; i < 4; i++){
        createSupport(game->psoport, 5, 7);
        createSupport(game->psoport, 8, 10);
    }

    return 0;

}

int firstLevel(game_state * game){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    srand(time(NULL));

    level = 1;
    game->score = 0;
    game->prana->lives = STARTING_LIVES;

    return setupLevel(game);

}

int nextLevel(game_state * game){

    return setupLevel(game);

}

int updateLevel(game_state * game, int time_left, int time_total){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    stepEntites(game);
    resetEntites(game);
    followSupport(game); //Solo actua si la rana esta en el lago

    if(isDeadLake(game) == 1 || isDeadFromEnemy(game) == 1){

        if(loseLife(game)){
            return GAME_OVER; //El llamador decide que hacer con game (NO se libera aca)
        }

        return FROG_DIED;

    }

    if(isAtEnd(game) == 1){ //Reclama el hueco-meta

        pointsForCross(game, time_left, time_total);
        resetFrogPos(game);

        if(isLevelFinished(game) == 1){

            pointForFinishingLevel(game);
            level++;
            nextLevel(game);

            return LEVEL_UP;

        }

        return FROG_CROSSED;

    }

    return LEVEL_RUNNING;

}
