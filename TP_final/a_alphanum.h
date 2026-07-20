#ifndef FROGGER_TEXT_H
#define FROGGER_TEXT_H

#include "a_sprites.h"
#include "a_PC_display.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define GLYPH_SIZE    7   // alto y ancho del glifo dibujado
#define GLYPH_ADVANCE 8   // avance por caracter en pantalla

// geometria de la zona de fuente dentro de la hoja
#define SHEET_FONT_X      2
#define SHEET_FONT_Y      250
#define SHEET_GLYPH_PITCH 9
#define SHEET_COLOR_PITCH 28
#define SHEET_GLYPHS_PER_ROW 17
#define NUM_FONT_COLORS   5


int index_disp(const char *text, int x, int y, int color);
int index_disp_len(const char *text);

#endif 
