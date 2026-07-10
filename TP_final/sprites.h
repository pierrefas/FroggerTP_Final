/*
 * sprites.h
 *
 * Created on: Jul 9, 2026
 * Author: peterfas
 */

#ifndef SPRITES_H
#define SPRITES_H

#include <allegro5/allegro.h>

// Global pointer to the sprite sheet (declared as extern so other files can see it)
extern ALLEGRO_BITMAP *sprites;

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

#endif /* SPRITES_H */