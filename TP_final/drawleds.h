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

/*******************************************************************************
 * TEXTO 3x3
 *
 * Letras A-Z y digitos 0-9 en glifos de 3x3 LEDs (mayusculas; minusculas
 * se convierten, cualquier otro caracter sale en blanco). Cada caracter
 * ocupa LED_CHAR_PITCH columnas: 3 del glifo + 1 de separacion.
 ******************************************************************************/
#define LED_GLYPH_H      3
#define LED_CHAR_PITCH   4

// Dibuja msg con la primera columna del primer glifo en x (puede ser
// negativa: lo que caiga fuera del display se recorta) y la fila superior
// de los glifos en top_row.
void led_draw_text(const char * msg, int x, int top_row);

/* Marquesina no bloqueante: el mensaje entra por la derecha, cruza el
 * display y sale por la izquierda. No tiene loop propio: el ciclo de juego
 * llama a led_scroll_step() una vez por tick entre disp_clear() y
 * disp_update(), asi el joystick se sigue leyendo mientras el texto pasa. */
typedef struct {
    const char * msg; /* debe seguir vivo mientras se scrollea */
    int len;
    int offset;       /* columna del strip virtual visible en el borde izquierdo */
    int tick;
} led_scroll;

void led_scroll_start(led_scroll * s, const char * msg);

// Dibuja un frame y avanza. Devuelve 1 cuando el texto ya salio entero
// (el llamador decide si reiniciarlo con led_scroll_start o cambiar de
// pantalla), 0 mientras siga pasando.
int led_scroll_step(led_scroll * s, int top_row);

#endif
