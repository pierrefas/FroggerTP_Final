#ifndef CHECKING_H
#define CHECKING_H

#include "gamestate.h"

/* Filas del mapa (alturas de la rana):
 * 0 = fila de salida, 1..5 = calle (enemigos), 6 = franja segura,
 * 7..11 = lago (soportes), 12 = fila de llegada (huecos-meta). */
#define STARTLAKE 7
#define ENDLAKE 11
#define GOALROW (ENDLAKE + 1)
#define SAFEROW (STARTLAKE - 1)

/* Huecos-meta: NUM_GOAL_SLOTS huecos de un casillero de ancho, el primero
 * en la columna 1 y despues uno cada 3 columnas (columnas 1, 4, 7, 10, 13). */
#define NUM_GOAL_SLOTS 5
#define GOAL_SLOT_X(i) (ADJCOORDFROG(1)/2 + (i) * ADJCOORDFROG(3))

/* Devuelve el indice del hueco-meta (0..NUM_GOAL_SLOTS-1) sobre el que esta
 * el centro de la rana, o -1 si no esta sobre ninguno. Consulta pura: no
 * modifica nada. */
int goalSlotAt(const frog_player * rana);

int isDeadFromEnemy(game_state *);
int isDeadLake(game_state *);

/* Si la rana esta en la fila de llegada sobre un hueco libre, LO RECLAMA
 * (marca safespaces) y devuelve 1. Llamarla solo desde updateLevel(). */
int isAtEnd(game_state *);

int isLevelFinished(game_state *);

#endif
