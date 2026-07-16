/*
 * sprites.c
 *
 * Created on: Jul 9, 2026
 * Author: peterfas
 */

#include "a_sprites.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>

// Define the global variables here
int framewidth = 16;
int frameheight = 16;
ALLEGRO_BITMAP *sprites = NULL;
ALLEGRO_BITMAP* frog_fwd = NULL;

int init_sprites(void)
{
    // Initialize the image addon required to load PNGs
    if (!al_init_image_addon()) {
        printf("Failed to initialize allegro image addon!\n");
        return 0;
    }

    // Load the sprite sheet
    sprites = al_load_bitmap("sprites.png");
    if (!sprites) {
        printf("Failed to load sprites.png\n");
        return 0;
    }

    frog_fwd = al_create_sub_bitmap(sprites, 1, 1, framewidth, frameheight);

    return 1;
}

void destroy_sprites(void)
{   

    if (sprites) {
        al_destroy_bitmap(frog_fwd);
        al_destroy_bitmap(sprites);

    }
}
