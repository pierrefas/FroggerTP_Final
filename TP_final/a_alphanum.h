#ifndef FROGGER_TEXT_H
#define FROGGER_TEXT_H

/**
 * @brief Imprime caracteres alfanuméricos en pantalla utilizando el spritesheet de Frogger.
 *
 * @param text  Puntero a la cadena de caracteres NUL-terminated a imprimir.
 * @param x     Posición inicial en el eje X.
 * @param y     Posición inicial en el eje Y.
 * @param color Selector de color (valores de 0 a 3).
 *
 * @return int  0: Éxito o fin de pantalla.
 *              <0: Error.
 */

#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "a_alphanum.h"
#include "a_sprites.h"
#include "a_PC_display.h"

#define GLYPH_SIZE    7   /* alto y ancho del glifo dibujado */
#define GLYPH_ADVANCE 8   /* avance por caracter en pantalla */

/* geometria de la zona de fuente dentro de la hoja */
#define SHEET_FONT_X      2
#define SHEET_FONT_Y      250
#define SHEET_GLYPH_PITCH 9
#define SHEET_COLOR_PITCH 28
#define SHEET_GLYPHS_PER_ROW 17
#define NUM_FONT_COLORS   5

int index_disp(const char *text, int x, int y, int color);

/**
 * @brief Ancho en pixeles que ocuparia text dibujado con index_disp
 * (para centrar). 0 si text es NULL.
 */
int index_disp_len(const char *text);

#endif // FROGGER_TEXT_H
