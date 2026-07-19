/*
 * sprites.h
 *
 * Created on: Jul 9, 2026
 * Author: peterfas
 */

#ifndef A_SPRITES_H
#define A_SPRITES_H

#include <allegro5/allegro.h>

/* Public constants — keep in sync with a_sprites.c */
#define NUM_ENEMY_TYPES  4
#define ENEMY_FRAMES     2
#define NUM_FROG_FRAMES  4

/* Exposed sprite arrays (sub-bitmaps created from the spritesheet) */
extern ALLEGRO_BITMAP *enemy_sprites[NUM_ENEMY_TYPES][ENEMY_FRAMES];
extern ALLEGRO_BITMAP *frog_sprites[NUM_FROG_FRAMES];

/* Load the spritesheet and create sub-bitmaps.
   - filename: path to the spritesheet PNG. If NULL, uses default inside a_sprites.c.
   - Returns 0 on success, -1 on failure. Caller must have initialized Allegro and the image addon. */
int load_sprites(const char *filename);

/* Destroy sub-bitmaps and the parent spritesheet. */
void destroy_sprites(void);

#endif /* A_SPRITES_H */