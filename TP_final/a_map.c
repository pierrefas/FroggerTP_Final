#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "a_sprites.h"
#include "a_PC_display.h" /* provides GAME_WIDTH, GAME_HEIGHT */

#ifndef TILE_W
#define TILE_W 16
#endif
#ifndef TILE_H
#define TILE_H 16
#endif

/* Option A: if you export these bitmaps from a_sprites.c (recommended),
   keep these externs and a_sprites.c should create them as sub-bitmaps. */
extern ALLEGRO_BITMAP* bush_0;
extern ALLEGRO_BITMAP* bush_1;
extern ALLEGRO_BITMAP* tile_0;

/* Option B: alternatively you can draw directly from the spritesheet using
   get_spritesheet() and source coordinates (SRC_BUSH_X, SRC_BUSH_Y, ...).
   If you use Option A ignore the SRC_* constants below. */
#define SRC_BUSH_0_X  0 /* set to actual source X on spritesheet */
#define SRC_BUSH_0_Y  0 /* set to actual source Y on spritesheet */
#define SRC_BUSH_1_X  16
#define SRC_BUSH_1_Y  0
#define SRC_TILE_0_X  0
#define SRC_TILE_0_Y  32

void a_disp_map(void)
{
    /* draw sky/water (top half) */
    int midpoint_y = GAME_HEIGHT / 2;
    al_draw_filled_rectangle(0, 0, GAME_WIDTH, midpoint_y, al_map_rgb(0, 0, 150));

    /* compute how many tile slots we need across the width */
    int tiles_across = (GAME_WIDTH + TILE_W - 1) / TILE_W; /* ceiling division */

    /* Draw bushes/foliage strip at top using tile-sized sprites.
       Use a deterministic pattern rather than the previous ad-hoc increments */
    for (int i = 0; i < tiles_across; ++i) {
        int sx = i * (TILE_W / 2); /* previous code used i*8; adjust if your bush sprite is half-width */
        int sy = 0;

        if (bush_0 && bush_1) {
            /* alternate pattern: could be changed to any rule */
            if (i % 6 == 0) {
                al_draw_bitmap(bush_0, sx, sy, 0);
            } else {
                /* draw two variants to create variety, as original code did */
                al_draw_bitmap(bush_1, sx, sy, 0);
            }
        } else {
            /* fallback: if dedicated bitmaps not available, draw from spritesheet regions */
            ALLEGRO_BITMAP *sheet = get_spritesheet();
            if (sheet) {
                if (i % 6 == 0) {
                    al_draw_bitmap_region(sheet, SRC_BUSH_0_X, SRC_BUSH_0_Y, TILE_W/2, TILE_H/2, sx, sy, 0);
                } else {
                    al_draw_bitmap_region(sheet, SRC_BUSH_1_X, SRC_BUSH_1_Y, TILE_W/2, TILE_H/2, sx, sy, 0);
                }
            }
        }
    }

    /* Draw two ground rows near the bottom (as original code did at y=128 and y=240) */
    /* compute row Y positions using named constants instead of magic numbers */
    const int ROW_TOP_Y = 128;
    const int ROW_BOTTOM_Y = 240;

    for (int i = 0; i < tiles_across; ++i) {
        int x = i * TILE_W;
        if (tile_0) {
            al_draw_bitmap(tile_0, x, ROW_TOP_Y, 0);
            al_draw_bitmap(tile_0, x, ROW_BOTTOM_Y, 0);
        } else {
            ALLEGRO_BITMAP *sheet = get_spritesheet();
            if (sheet) {
                al_draw_bitmap_region(sheet, SRC_TILE_0_X, SRC_TILE_0_Y, TILE_W, TILE_H, x, ROW_TOP_Y, 0);
                al_draw_bitmap_region(sheet, SRC_TILE_0_X, SRC_TILE_0_Y, TILE_W, TILE_H, x, ROW_BOTTOM_Y, 0);
            }
        }
    }
}