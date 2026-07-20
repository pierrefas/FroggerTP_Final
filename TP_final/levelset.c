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

int level;


int lentypes[] = {1, 1, 1, 1, 2, 3, 3, 7, 3, 2}; //Los largos de cada entidad segun su fila

static int createEnemy(enemy_entity * enemigo, int tipo, int height);
static int createSupport(support_entity * soporte, int tipo, int height, int can_dive);
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

            if(temp != new_enemy && temp->height == height &&
               new_enemy->startcoord <= temp->endcoord + ENTITY_MIN_GAP &&
               new_enemy->endcoord >= temp->startcoord - ENTITY_MIN_GAP){

                placed = 0; //Pisa a otro de su fila reintento en otra posicion, tambien me aseguro de que no sea la misma entidad
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

static int createSupport(support_entity * soporte, int tipo, int height, int can_dive){

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
    new_support->supporting = 1; //Todos arrancan a flote

    /* Solo las tortugas marcadas con can_dive se hunden ciclicamente
     * (ver entityupdates.h): setupLevel habilita UNA por fila, con fase
     * inicial al azar. El resto (y los troncos) queda en -1: a flote
     * para siempre. */
    new_support->divetimer = (SUPPORT_IS_TURTLE(tipo) && can_dive) ? rand() % DIVE_CYCLE_TICKS : -1;

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

            if(temp != new_support && temp->height == height &&
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

static int rowSpeed(void){

    int speed = 1 + level/2 + rand() % (level) ;

    if(speed > MAX_ROW_SPEED){
        speed = MAX_ROW_SPEED;
    }

    return (rand() % 2) ? speed : -speed;

}

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
        (game->safespaces)[i] = 0; //Libero las endozones
    }

    for(i = 0; i < NUM_HEIGHT_LEVELS; i++){
        (game->pspeedheight)[i] = rowSpeed();
    }

    (game->pspeedheight)[0] = 0; //Claramente las filas seguras no se mueven
    (game->pspeedheight)[SAFEROW] = 0;
    (game->pspeedheight)[GOALROW] = 0;

    if(level == 1){ //En el nivel 1 todas las filas comparten velocidad 1, distingo un poco la 3ra hilera de troncos (altura 11) de la 1ra (altura 8)
        (game->pspeedheight)[11] = ((game->pspeedheight)[8] > 0) ? (game->pspeedheight)[8] + 1 : (game->pspeedheight)[8] - 1;
    }

    for(i = 0; i < 3; i++){

        createEnemy(game->penemies, 0, 1); //Los autos y los camiones de la ultima calle
        createEnemy(game->penemies, 1, 2);
        createEnemy(game->penemies, 2, 3);
        createEnemy(game->penemies, 3, 4);
        createEnemy(game->penemies, 4, 5);

    }

    for(i = 0; i < 3; i++){

        createSupport(game->psoport, 8, 7, i == 0);  //3 grupos de 3 tortugas
        createSupport(game->psoport, 6, 8, 0);       //3 troncos de 3

    }

    for(i = 0; i < 2; i++){

        createSupport(game->psoport, 7, 9, 0);       //2 troncos largos de 7

    }

    for(i = 0; i < 5; i++){

        createSupport(game->psoport, 9, 10, i == 0); //5 grupos de 2 tortugas

    }

    for(i = 0; i < 4; i++){

        createSupport(game->psoport, 5, 11, 0);      //4 troncos de 3

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

    level ++;

    return setupLevel(game);

}

int skipLevel(game_state * game){

    if(game == NULL){
        return ERROR_NULL_POINTER;
    }

    return nextLevel(game);

}

int updateLevel(game_state * game, int time_left, int time_total){

    if(game == NULL || game->prana == NULL){
        return ERROR_NULL_POINTER;
    }

    stepEntites(game);
    resetEntites(game);
    updateSupportDive(game); //Las tortugas avanzan su ciclo de buceo
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
            nextLevel(game);

            return LEVEL_UP;

        }

        return FROG_CROSSED;

    }

    return LEVEL_RUNNING;

}
