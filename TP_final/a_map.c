#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "a_sprites.h"
#include "a_PC_display.h"

#ifndef TILE_W
#define TILE_W 16
#endif
#ifndef TILE_H
#define TILE_H 16
#endif

/* Source coordinates on the sheet for fallback; adjust if needed */
#ifndef SRC_BUSH_0_X
#define SRC_BUSH_0_X 0
#endif
#ifndef SRC_BUSH_0_Y
#define SRC_BUSH_0_Y 0
#endif
#ifndef SRC_BUSH_1_X
#define SRC_BUSH_1_X 8
#endif
#ifndef SRC_BUSH_1_Y
#define SRC_BUSH_1_Y 0
#endif
#ifndef SRC_TILE_0_X
#define SRC_TILE_0_X 0
#endif
#ifndef SRC_TILE_0_Y
#define SRC_TILE_0_Y 32
#endif

void a_disp_map (void){

    int midpoint_y =  GAME_HEIGHT / 2;
    al_draw_filled_rectangle(0, 0, GAME_WIDTH, midpoint_y, al_map_rgb(0, 0, 150));

    int tiles_across = (GAME_WIDTH + (TILE_W/2) - 1) / (TILE_W/2);

    /* draw some foliage/bush pattern */
    ALLEGRO_BITMAP *sheet = get_spritesheet();
    for (int i = 0; i < tiles_across; ++i) {
        int sx = i * (TILE_W / 2);
        int sy = 0;
        if (bush_0 && bush_1) {
            if (i % 6 == 0) 
            {
                al_draw_bitmap(bush_0, sx, sy, 0);
                i+=3;
            }
            else 
            {
                al_draw_bitmap(bush_1, sx, sy, 0);
            }
        } else if (sheet) {
            if (i % 6 == 0) al_draw_bitmap_region(sheet, SRC_BUSH_0_X, SRC_BUSH_0_Y, TILE_W/2, TILE_H/2, sx, sy, 0);
            else al_draw_bitmap_region(sheet, SRC_BUSH_1_X, SRC_BUSH_1_Y, TILE_W/2, TILE_H/2, sx, sy, 0);
        }
    }

    const int ROW_TOP_Y = 128;
    const int ROW_BOTTOM_Y = 240;
    int tiles_full = (GAME_WIDTH + TILE_W - 1) / TILE_W;
    for (int i = 0; i < tiles_full; ++i) {
        int x = i * TILE_W;
        if (tile_0) {
            al_draw_bitmap(tile_0, x, ROW_TOP_Y, 0);
            al_draw_bitmap(tile_0, x, ROW_BOTTOM_Y, 0);
        } else if (sheet) {
            al_draw_bitmap_region(sheet, SRC_TILE_0_X, SRC_TILE_0_Y, TILE_W, TILE_H, x, ROW_TOP_Y, 0);
            al_draw_bitmap_region(sheet, SRC_TILE_0_X, SRC_TILE_0_Y, TILE_W, TILE_H, x, ROW_BOTTOM_Y, 0);
        } else {
            al_draw_filled_rectangle(x, ROW_TOP_Y, x + TILE_W, ROW_TOP_Y + TILE_H, al_map_rgb(100,100,100));
            al_draw_filled_rectangle(x, ROW_BOTTOM_Y, x + TILE_W, ROW_BOTTOM_Y + TILE_H, al_map_rgb(100,100,100));
        }
    }
}
