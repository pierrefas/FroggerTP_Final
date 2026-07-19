//aca voy a poner los "sprites" de las letras del frogger

#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "a_sprites.h"
#include "a_PC_display.h"

#define FRAME_WH_8_BIT 8

#define POSITION_16_BIT 232 // todos los sprites estan defazados en 1 pixel en x, asi que lo unico que importa es el y

#define POSITION_8_BIT 250

#define COLOR_OFFSET 28 //puedo cambiar el color de las letras sabiendo que todas varian en 28 px del siguiente color. Capaz lo use, capaz no.

extern ALLEGRO_BITMAP* sprites;

//pienso hacer dos funciones (una para las letras de 16*16 y otra para las de 8*8) que reciban un array y que
// vaya leyendo los ints de ese array, por ejemplo si el valor es 0 en el de 16*16 devuelve o imprime en pantalla el bitmap
//  de la F. Lo hago vla porque no se cuantas veces lo voy a usar y para que.

int index_disp(const char *text, int start_x, int start_y, int color)
{
    if (!text) return -1;
    ALLEGRO_BITMAP *sheet = get_spritesheet();
    if (!sheet) return -2;

    if (start_x < 0 || start_y < 0) return -3;
    if (color < 0) color = 0;
    if (color > 3) color = 3;

    int x = start_x;
    int y = start_y;

    for (size_t i = 0; text[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char) text[i];

        if (ch == '\n') {
            x = start_x;
            y += FRAME_WH_8_BIT;
            continue;
        }

        if (ch == ' ') {
            x += FRAME_WH_8_BIT;
            if (x + FRAME_WH_8_BIT > GAME_WIDTH) { x = start_x; y += FRAME_WH_8_BIT; }
            if (y > GAME_HEIGHT) break;
            continue;
        }

        int index;
        if (ch >= '0' && ch <= '9') index = ch - '0';
        else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) index = (toupper(ch) - 'A') + 10;
        else index = 38; /* fallback glyph index */

        int row = index / 16;
        int col = index % 16;

        int src_x = 1 + col * FRAME_WH_8_BIT; /* +1 if your sheet has 1px left margin */
        int src_y = POSITION_8_BIT + color * COLOR_OFFSET + row * FRAME_WH_8_BIT;

        /* Clip/wrap check */
        if (x + FRAME_WH_8_BIT > GAME_WIDTH) {
            x = start_x;
            y += FRAME_WH_8_BIT;
        }
        if (y > GAME_HEIGHT) break; /* no more space */

        al_draw_bitmap_region(sheet, src_x, src_y, FRAME_WH_8_BIT, FRAME_WH_8_BIT, x, y, 0);

        x += FRAME_WH_8_BIT;
    }

    return 0;
}