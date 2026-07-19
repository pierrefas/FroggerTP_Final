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

/* en TP_final/a_sprites.h — añadir después de los #define existentes */

#ifndef FRAME_W
#define FRAME_W 16
#endif
#ifndef FRAME_H
#define FRAME_H 16
#endif

/* optional exported tile/sub-bitmaps (may be NULL if not created) */
extern ALLEGRO_BITMAP *bush_0;
extern ALLEGRO_BITMAP *bush_1;
extern ALLEGRO_BITMAP *tile_0;

/* access to the parent spritesheet (may be NULL if load failed) */
ALLEGRO_BITMAP *get_spritesheet(void);

/* enums públicos para usar en el resto del código */
enum {
    FROG_IDLE = 0,
    FROG_LEFT,
    FROG_RIGHT,
    FROG_JUMP
};

/* si también quieres exponer los índices de enemigos */
enum {
    ENEMY_CAR = 0,
    ENEMY_TRUCK,
    ENEMY_BUS,
    ENEMY_BIKE
};

/* Exposed sprite arrays (sub-bitmaps created from the spritesheet) */
extern ALLEGRO_BITMAP *enemy_sprites[NUM_ENEMY_TYPES][ENEMY_FRAMES];
extern ALLEGRO_BITMAP *frog_sprites[NUM_FROG_FRAMES];

/* Load the spritesheet and create sub-bitmaps.
   - filename: path to the spritesheet PNG. If NULL, uses default inside a_sprites.c.
   - Returns 0 on success, -1 on failure. Caller must have initialized Allegro and the image addon. */
int load_sprites(const char *filename);

/* Destroy sub-bitmaps and the parent spritesheet. */
void destroy_sprites(void);

/* in a_sprites.h */
ALLEGRO_BITMAP *get_spritesheet(void);

#endif /* A_SPRITES_H */