/*
 * sprites.h
 *
 * Created on: Jul 9, 2026
 * Author: peterfas
 */

#ifndef a_SPRITES_H
#define a_SPRITES_H

#define FRAMEWIDTH 16
#define FRAMEHEIGHT 16

#include <allegro5/allegro.h>

// Global pointer to the sprite sheet (declared as extern so other files can see it)
extern ALLEGRO_BITMAP* sprites;
extern ALLEGRO_BITMAP* frog_fwd;



// Game-specific dimensions
extern int framewidth;
extern int frameheight;

/**
 * @brief Initializes the image addon and loads the sprite sheet.
 * @return int Returns 1 on success, 0 on failure.
 */
int init_sprites(void);

/**
 * @brief Cleans up and destroys loaded sprite assets.
 */
void destroy_sprites(void);

#endif /* a_SPRITES_H */