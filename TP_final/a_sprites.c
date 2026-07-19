/*
 * sprites.c
 *
 * Created on: Jul 9, 2026
 * Author: peterfas
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "a_sprites.h"

/* Default spritesheet path (change if needed) */
#ifndef DEFAULT_SPRITESHEET_FILE
#define DEFAULT_SPRITESHEET_FILE "assets/spritesheet.png"
#endif

/* Frame size in pixels: set these to the tile/frame size in your sheet */
#ifndef FRAME_W
#define FRAME_W 16
#endif
#ifndef FRAME_H
#define FRAME_H 16
#endif

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

/* Layout assumption (change logic below if your sheet differs):
   - rows 0..NUM_ENEMY_TYPES-1 : each row contains ENEMY_FRAMES frames for that enemy type
       (columns 0..ENEMY_FRAMES-1)
   - rows NUM_ENEMY_TYPES .. NUM_ENEMY_TYPES+NUM_FROG_FRAMES-1 : each row contains one frog frame
       (we take the first column for frog frames)
   If your spritesheet packs frames differently (multiple cols for frog frames, or different row order),
   modify the x/y calculations in load_sprites accordingly.
*/

/* Parent spritesheet bitmap (kept private) */
static ALLEGRO_BITMAP *spritesheet = NULL;

/* Exported sub-bitmaps */
ALLEGRO_BITMAP *enemy_sprites[NUM_ENEMY_TYPES][ENEMY_FRAMES] = { { NULL } };
ALLEGRO_BITMAP *frog_sprites[NUM_FROG_FRAMES] = { NULL };

ALLEGRO_BITMAP *bush_0 = NULL;
ALLEGRO_BITMAP *bush_1 = NULL;
ALLEGRO_BITMAP *tile_0 = NULL;

/* Load the spritesheet and create sub-bitmaps.
   Caller must have called al_init() and al_init_image_addon(). */
int load_sprites(const char *filename)
{
    const char *file = filename ? filename : DEFAULT_SPRITESHEET_FILE;

    spritesheet = al_load_bitmap(file);
    if (!spritesheet) {
        fprintf(stderr, "a_sprites: Failed to load spritesheet '%s'\n", file);
        return -1;
    }

    /* Validate sheet is at least large enough for our grid (optional) */
    int sheet_w = al_get_bitmap_width(spritesheet);
    int sheet_h = al_get_bitmap_height(spritesheet);
    int needed_w = ENEMY_FRAMES * FRAME_W;
    int needed_h = (NUM_ENEMY_TYPES + NUM_FROG_FRAMES) * FRAME_H;
    if (sheet_w < needed_w || sheet_h < needed_h) {
        fprintf(stderr,
                "a_sprites: spritesheet too small (%dx%d) for required grid (%dx%d)\n",
                sheet_w, sheet_h, needed_w, needed_h);
        goto error;
    }

    /* Create enemy sub-bitmaps: each enemy type occupies a row, frames per columns */
    for (int t = 0; t < NUM_ENEMY_TYPES; ++t) {
        int row = t;
        for (int f = 0; f < ENEMY_FRAMES; ++f) {
            int x = f * FRAME_W;
            int y = row * FRAME_H;
            enemy_sprites[t][f] = al_create_sub_bitmap(spritesheet, x, y, FRAME_W, FRAME_H);
            if (!enemy_sprites[t][f]) {
                fprintf(stderr, "a_sprites: Failed to create enemy sub-bitmap type=%d frame=%d\n", t, f);
                goto error;
            }
        }
    }

    /* Create frog sub-bitmaps: one frog frame per row in this layout */
    for (int f = 0; f < NUM_FROG_FRAMES; ++f) {
        int row = NUM_ENEMY_TYPES + f;
        int x = 0; /* if frog frames are in the first column of each row */
        int y = row * FRAME_H;
        frog_sprites[f] = al_create_sub_bitmap(spritesheet, x, y, FRAME_W, FRAME_H);
        if (!frog_sprites[f]) {
            fprintf(stderr, "a_sprites: Failed to create frog sub-bitmap frame=%d\n", f);
            goto error;
        }
    }

    return 0;

error:
    /* Clean up any sub-bitmaps that were created */
    for (int t = 0; t < NUM_ENEMY_TYPES; ++t) {
        for (int f = 0; f < ENEMY_FRAMES; ++f) {
            if (enemy_sprites[t][f]) {
                al_destroy_bitmap(enemy_sprites[t][f]);
                enemy_sprites[t][f] = NULL;
            }
        }
    }
    for (int f = 0; f < NUM_FROG_FRAMES; ++f) {
        if (frog_sprites[f]) {
            al_destroy_bitmap(frog_sprites[f]);
            frog_sprites[f] = NULL;
        }
    }
    if (spritesheet) {
        al_destroy_bitmap(spritesheet);
        spritesheet = NULL;
    }
    return -1;
}

/* Destroy sub-bitmaps first, then the parent spritesheet */
void destroy_sprites(void)
{
    for (int t = 0; t < NUM_ENEMY_TYPES; ++t) {
        for (int f = 0; f < ENEMY_FRAMES; ++f) {
            if (enemy_sprites[t][f]) {
                al_destroy_bitmap(enemy_sprites[t][f]);
                enemy_sprites[t][f] = NULL;
            }
        }
    }
    for (int f = 0; f < NUM_FROG_FRAMES; ++f) {
        if (frog_sprites[f]) {
            al_destroy_bitmap(frog_sprites[f]);
            frog_sprites[f] = NULL;
        }
    }
    if (spritesheet) {
        al_destroy_bitmap(spritesheet);
        spritesheet = NULL;
    }
}

ALLEGRO_BITMAP *get_spritesheet(void)
{
    return spritesheet;
}