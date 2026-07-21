/*
 * a_alphanum.h
 *
 * Texto en pantalla para el front-end de PC, usando la fuente propia del
 * spritesheet del arcade (glifos de 7x7 recortados de la zona y=250 de la
 * hoja, en 5 colores) en vez de una fuente de sistema. La usan el menu,
 * el HUD y la pantalla de carga de iniciales.
 */

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
int index_disp_len(const char *text);

#endif 
