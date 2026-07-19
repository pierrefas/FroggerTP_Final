#ifndef DRAWLEDS_H
#define DRAWLEDS_H

#include "disdrv.h"

/*******************************************************************************
 * ZONAS DEL DISPLAY
 *
 * El display de 16x16 no se usa completo como "campo de juego": la columna
 * 15 queda reservada para el indicador de vidas, la fila 14 para la barra
 * de tiempo, y la columna 14 queda en blanco como separador. Estas
 * constantes centralizan esos limites para que rana, autos/troncos y la
 * barra de tiempo respeten siempre la misma zona (antes el limite "14"
 * estaba repetido como numero magico en mas de un lugar, y la rana no lo
 * respetaba).
 ******************************************************************************/
#define PLAY_FIELD_MAX_X    13   // ultima columna de la zona de juego (0 a 13)
#define TIME_BAR_ROW        14   // fila fija de la barra de tiempo
#define LIVES_COLUMN        15   // columna fija del indicador de vidas

// Cantidad de tipos de entidad soportados. DEBE coincidir con
// lentypes[] para no leer fuera de rango.
#define NUM_ENTITY_TYPES    10

// Funciones de dibujo
void led_draw_frog(int x_px, int y_height);
void led_draw_entity(int x_px, int y_height, int type);
void led_draw_time(int time_val);
void led_draw_lives(int lives_val);

#endif
