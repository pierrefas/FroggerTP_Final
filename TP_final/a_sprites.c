/*
 * a_sprites.c
 *
 * Ver a_sprites.h. La hoja es el rip del arcade (154x487): los sprites
 * NO estan en una grilla regular, asi que cada uno se recorta por sus
 * coordenadas medidas en el PNG. El fondo de la hoja (gris 64,64,64 y
 * negro) se convierte a transparente al cargar.
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "a_sprites.h"

#ifndef DEFAULT_SPRITESHEET_FILE
#define DEFAULT_SPRITESHEET_FILE "sprites.png"
#endif

static ALLEGRO_BITMAP *spritesheet = NULL;

ALLEGRO_BITMAP *frog_sprites[4] = { NULL };
ALLEGRO_BITMAP *frog_jump_sprites[4] = { NULL };
ALLEGRO_BITMAP *death_sprites[NUM_DEATH_FRAMES] = { NULL };
ALLEGRO_BITMAP *vehicle_sprites[NUM_VEHICLE_TYPES] = { NULL };
ALLEGRO_BITMAP *log_left = NULL, *log_mid = NULL, *log_right = NULL;
ALLEGRO_BITMAP *turtle_sprite = NULL, *turtle_dive = NULL;
ALLEGRO_BITMAP *home_frog = NULL;
ALLEGRO_BITMAP *sidewalk_tile = NULL, *bush_arch = NULL, *bush_fill = NULL;

/* Region de la hoja + puntero destino, para recortar todo en un fruityloopy. */
typedef struct {
    ALLEGRO_BITMAP **dst;
    int x, y, w, h;
} sheet_region;

/*
    la siguiente estructura fue crada con ia ( claudia ), para agilizar la creacion de sub_bitmaps 
    y ademas dada la monotoneidad de definir cada item del mismo array
*/

static const sheet_region regions[] = {
    // rana sentada mirando: arriba, derecha, abajo, izquierda 
    { &frog_sprites[0],     3,   4, 12,  9 },
    { &frog_sprites[1],   113,   3,  9, 12 },
    { &frog_sprites[2],    75,   5, 12,  9 },
    { &frog_sprites[3],    40,   3,  9, 12 },
    // rana saltando (patas estiradas), mismas orientaciones
    { &frog_jump_sprites[0],  21, 3, 12, 13 },
    { &frog_jump_sprites[1], 128, 3, 13, 12 },
    { &frog_jump_sprites[2],  93, 2, 12, 13 },
    { &frog_jump_sprites[3],  57, 3, 13, 12 },
    /* muerte: splash violeta x3, ondas x2, calavera */
    { &death_sprites[0],    3,  81, 12, 14 },
    { &death_sprites[1],   20,  81, 14, 13 },
    { &death_sprites[2],   37,  80, 16, 16 },
    { &death_sprites[3],   59,  84,  8,  8 },
    { &death_sprites[4],   77,  84,  8,  8 },
    { &death_sprites[5],  110,  80, 15, 16 },
    /* vehiculos (tipos 0..4 del backend; el camion mide ~2 casilleros) */
    { &vehicle_sprites[0],  2, 119, 15, 10 },
    { &vehicle_sprites[1], 19, 117, 16, 14 },
    { &vehicle_sprites[2], 37, 117, 16, 14 },
    { &vehicle_sprites[3], 56, 118, 14, 12 },
    { &vehicle_sprites[4], 76, 119, 27, 10 },
    /* tronco: puntas y tramo repetible */
    { &log_left,            4, 137, 13, 10 },
    { &log_mid,            19, 137, 16, 10 },
    { &log_right,          37, 137, 13, 10 },
    /* tortuga a flote / hundiendose */
    { &turtle_sprite,       2, 156, 13,  9 },
    { &turtle_dive,        56, 154, 16, 13 },
    /* rana guardada en el hueco-meta */
    { &home_frog,          45, 196, 16, 16 },
    /* fondo: vereda y arbustos de la fila de llegada */
    { &sidewalk_tile,     135, 196, 16, 16 },
    { &bush_arch,           1, 188, 32, 23 },
    { &bush_fill,          35, 188,  8, 23 },
};

#define NUM_REGIONS ((int)(sizeof(regions) / sizeof(regions[0])))

ALLEGRO_BITMAP *get_spritesheet(void){

    return spritesheet;

}

int load_sprites(const char *filename){
    
    const char *file = filename ? filename : DEFAULT_SPRITESHEET_FILE;
    int i;

    spritesheet = al_load_bitmap(file);
    if (!spritesheet) {
        fprintf(stderr, "a_sprites: Failed to load spritesheet '%s'\n", file);
        return -1;
    }

    /* el fondo de la hoja pasa a transparente */
    al_convert_mask_to_alpha(spritesheet, al_map_rgb(64, 64, 64));
    al_convert_mask_to_alpha(spritesheet, al_map_rgb(0, 0, 0));

    for (i = 0; i < NUM_REGIONS; i++) {

        *regions[i].dst = al_create_sub_bitmap(spritesheet, regions[i].x, regions[i].y, regions[i].w, regions[i].h);

        if (*regions[i].dst == NULL) {
            fprintf(stderr, "a_sprites: Failed to create sub-bitmap %d\n", i);
            destroy_sprites();
            return -1;
        }
    }

    return 0;
}

void destroy_sprites(void)
{
    int i;

    for (i = 0; i < NUM_REGIONS; i++) {
        if (*regions[i].dst) {
            al_destroy_bitmap(*regions[i].dst);
            *regions[i].dst = NULL;
        }
    }

    if (spritesheet) {
        al_destroy_bitmap(spritesheet);
        spritesheet = NULL;
    }
}
