//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Consultas a:  Juanga                                            //
//                                                                  //
//  En este archivo van a estar todas las funciones que             //
//  inicilaizan el nivel, sus entidades y el jugador                //
//  Y tiene en cuenta la dificultad progresiva                      //
//                                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////




#include "levelset.h"
#include <time.h>

int lentypes[] = {1,1,2,3,5,7};


static int createEnemy(enemy_entity* enemigo, int tipo, int height, int heightspeed[]);
static int createSupport(support_entity* soporte, int tipo, int height, int heightspeed[]);
static support_entity * iniSupEntities(void);
static enemy_entity * iniEneEntities(void);

static int createEnemy(enemy_entity* enemigo, int tipo, int height, int heightspeed[]){

    if(enemigo == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(tipo < 0 || tipo >= 2){
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

    while(supperposition++ < 50 && supperposition > 0){

        enemy_entity* temp = enemigo;

        new_enemy->startcoord = rand() % (ENDWORLD - 3 ); //Genero un numero aleatorio entre 0 y ENDWORLD para que el soporte no se salga de la pantalla
        new_enemy->endcoord = new_enemy->startcoord + lentypes[tipo];

        for(; temp->type != -1; temp++){
        
            if(temp->height == height && new_enemy->startcoord <= temp->endcoord && new_enemy->endcoord >= temp->startcoord){ //Si hay colision entre soportes, se desplaza el nuevo soporte a la derecha del ultimo soporte que colisiona con el

                supperposition = 1;
                break;

            }
            else{
                supperposition = 0;
            }

        }

    }

    if(supperposition>=50){

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
    else if(tipo < 2){
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

    while(supperposition++ < 50 && supperposition > 0){

        support_entity* temp = soporte;

        new_support->startcoord = rand() % (ENDWORLD - 3 ); //Genero un numero aleatorio entre 0 y ENDWORLD para que el soporte no se salga de la pantalla
        new_support->endcoord = new_support->startcoord + lentypes[tipo];

        for(; temp->type != -1; temp++){
        
            if(temp->height == height && new_support->startcoord <= temp->endcoord && new_support->endcoord >= temp->startcoord){ //Si hay colision entre soportes, se desplaza el nuevo soporte a la derecha del ultimo soporte que colisiona con el

                supperposition = 1;
                break;

            }
            else{
                supperposition = 0;
            }

        }

    }

    if(supperposition>=50){

        new_support->type = -1;
        return ERROR_ENTIDAD_INCOLOCABLE; 

    }
    else{
    
        return 0;
    }
}

int nextLevel(int level, enemy_entity* enemigos, support_entity* soportes, int heightspeed[],frog_player* rana){

    srand(time(NULL));

    if(enemigos == NULL || soportes == NULL|| rana == NULL|| heightspeed == NULL){
        return ERROR_NULL_POINTER;
    }
    else if(level < 1){
        return ERROR_NIVEL_INVALIDO;
    }

    enemigos->type = -1; //Pongo el primer enemigo como vacio
    soportes->type = -1; //Pongo el primer soporte como vacio
    rana->height = 0; //Pongo la rana en la primera fila
    rana->startcoord = ADJCOORDFROG(3); //Pongo la rana en el inicio
    rana->endcoord = rana->startcoord + ADJCOORDFROG(1); 

    int i,j;

    for(i = 0; i < 13; i++){

        heightspeed[i] = rand() % (level + 5) + level; //Aumento la velocidad de los enemigos y soportes en cada nivel

    }

    for(i = 1; i < 6; i++){

        int temp = rand() % 4 + 1; //Genero un numero aleatorio entre 1 y 4 para ver cuantos enemigos genero

        for(j = 0; j < temp; j++){

            createEnemy(enemigos, rand() % 3, i, heightspeed); //Genero enemigos aleatorios

        }
    }

    for(i = 7; i < 12; i++){

        int temp = rand() % 4 + 1; //Genero un numero aleatorio entre 1 y 4 para ver cuantos soportes genero

        for(j = 0; j < temp; j++){

            createSupport(soportes, rand() % 3 , i , heightspeed); //Genero soportes aleatorios

        }
    }

    return 0;

}

static enemy_entity * iniEneEntities(void){

    enemy_entity * enemies = (enemy_entity*) malloc(25*sizeof(enemy_entity));

    if(!enemies){

        free(enemies);
        return NULL;

    }

    return enemies;

}

static support_entity * iniSupEntities(void){

    support_entity * support = (support_entity*) malloc(25*sizeof(support_entity));

    if(!support){

        free(support);
        return NULL;

    }

    return support;

}