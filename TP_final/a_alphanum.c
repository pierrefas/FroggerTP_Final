/*
 * a_alphanum.c
 *
 * Texto con la fuente del propio spritesheet del arcade. La zona de
 * fuente de la hoja arranca en y=250: bloques de un color cada 28 px
 * (0 blanco, 1 amarillo, 2 rojo, 3 magenta, 4 cian), cada bloque con 3
 * filas de 17 glifos de 7x7 separados cada 9 px:
 *   fila 0: 0123456789ABCDEFG   fila 1: HIJKLMNOPQRSTUVWX   fila 2: YZ-...
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

int index_disp(const char *text, int start_x, int start_y, int color)
{
    if (!text) return -1;
    ALLEGRO_BITMAP *sheet = get_spritesheet();
    if (!sheet) return -2;

    if (start_x < 0 || start_y < 0) return -3;
    if (color < 0) color = 0;
    if (color >= NUM_FONT_COLORS) color = NUM_FONT_COLORS - 1;

    int x = start_x;
    int y = start_y;

    for (size_t i = 0; text[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char) text[i];

        if (ch == '\n') {
            x = start_x;
            y += GLYPH_ADVANCE;
            continue;
        }

        if (ch == ' ') {
            x += GLYPH_ADVANCE;
            if (x + GLYPH_SIZE > GAME_WIDTH) { x = start_x; y += GLYPH_ADVANCE; }
            if (y > GAME_HEIGHT) break;
            continue;
        }

        int index;
        if (ch >= '0' && ch <= '9') index = ch - '0';
        else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) index = (toupper(ch) - 'A') + 10;
        else index = 36; /* glifo de relleno para caracteres sin dibujo */

        int row = index / SHEET_GLYPHS_PER_ROW;
        int col = index % SHEET_GLYPHS_PER_ROW;

        int src_x = SHEET_FONT_X + col * SHEET_GLYPH_PITCH;
        int src_y = SHEET_FONT_Y + color * SHEET_COLOR_PITCH + row * SHEET_GLYPH_PITCH;

        /* Clip/wrap check */
        if (x + GLYPH_SIZE > GAME_WIDTH) {
            x = start_x;
            y += GLYPH_ADVANCE;
        }
        if (y > GAME_HEIGHT) break; /* no more space */

        al_draw_bitmap_region(sheet, src_x, src_y, GLYPH_SIZE, GLYPH_SIZE, x, y, 0);

        x += GLYPH_ADVANCE;
    }

    return 0;
}

int index_disp_len(const char *text)
{
    return text ? (int)strlen(text) * GLYPH_ADVANCE : 0;
}
