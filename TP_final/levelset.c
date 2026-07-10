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
#include "entidades.h"

int lentypes[] = {1,1,2,3,5,7};

createEnemy(enemy_entity* enemigo, int tipo, int height, int heightspeed[]);
createSupport(support_entity* soporte, int tipo, int height, int heightspeed[]);

static int createEnemy(enemy_entity* enemigo, int tipo, int height, int heightspeed[]){

    if(enemigo == NULL){
        return ERROR_NULL_POINTER;
    }

    enemy_entity* temp = enemigo;

    int i;

    for(i = 0; temp->type != -1; temp++); //Hago que apunte al ultimo enemigo de la lista

    temp->type = tipo;
    temp->height = height;
    temp->startcoord = rand(time(NULL)) % 186; //Genero un numero aleatorio entre 0 y 186 para que el enemigo no se salga de la pantalla
    temp->endcoord = temp->startcoord + lentypes[tipo];

    (temp+1)->type = -1; //Pongo el siguiente enemigo como vacio

    enemy_entity* new_enemy = temp;

    temp = enemigo;

    for(i = 0; temp->type != -1; temp++){
    
        if(temp->height == height && new_enemy->startcoord <= temp->endcoord && new_enemy->endcoord >= temp->startcoord){ //Si hay colision entre enemigos, se desplaza el nuevo enemigo a la derecha del ultimo enemigo que colisiona con el

            new_enemy->startcoord = temp->endcoord + 16;
            new_enemy->endcoord = new_enemy->startcoord + lentypes[tipo];
        }


    }
    
    return 0;

}

static int createSupport(support_entity* soporte, int tipo, int height, int heightspeed[]){

    if(soporte == NULL){
        return ERROR_NULL_POINTER;
    }

    support_entity* temp = soporte;

    int i;

    for(i = 0; temp->type != -1; temp++); //Hago que apunte al ultimo soporte de la lista

    temp->type = tipo;
    temp->height = height;
    temp->startcoord = rand(time(NULL)) % 256;
    temp->endcoord = temp->startcoord + lentypes[tipo];

    (temp+1)->type = -1; //Pongo el siguiente soporte como vacio

    support_entity* new_support = temp;

    temp = soporte;

    for(i = 0; temp->type != -1; temp++){
    
        if(temp->height == height && new_support->startcoord <= temp->endcoord && new_support->endcoord >= temp->startcoord){ //Si hay colision entre soportes, se desplaza el nuevo soporte a la derecha del ultimo soporte que colisiona con el

            new_support->startcoord = temp->endcoord + 16;
            new_support->endcoord = new_support->startcoord + lentypes[tipo];
        }
    }

    return 0;
}

int nextLevel(int level, enemy_entity* enemigos, support_entity* soportes, int heightspeed[],frog_player* rana){

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

    int i;

    for(i = 0; i < 13; i++){

        heightspeed[i] = rand(time(NULL)) % (level + 5) + level; //Aumento la velocidad de los enemigos y soportes en cada nivel

    }

    for(i = 0; i < 5; i++){

        int temp = rand(time(NULL)) % 4 + 1; //Genero un numero aleatorio entre 1 y 4 para ver cuantos enemigos genero

        for(i = 0; i < temp; i++){

            createEnemy(enemigos, rand(time(NULL)) % 3, i + 1, heightspeed); //Genero enemigos aleatorios

        }
    }

    for(i = 0; i < 5; i++){

        int temp = rand(time(NULL)) % 4 + 1; //Genero un numero aleatorio entre 1 y 4 para ver cuantos soportes genero

        for(i = 0; i < temp; i++){

            createSupport(soportes, rand(time(NULL)) % 3, i + 6, heightspeed); //Genero soportes aleatorios

        }
    }

}