/*
 * a_sprites.h
 *
 * Carga del spritesheet (rip del Frogger arcade de Konami) y recorte en
 * sub-bitmaps listos para dibujar. Las coordenadas de cada sprite dentro
 * de la hoja viven en a_sprites.c. Todos los punteros pueden quedar NULL
 * si la hoja no cargo: a_render.c dibuja con primitivas en ese caso.
 */

#ifndef A_SPRITES_H
#define A_SPRITES_H

#include <allegro5/allegro.h>

/* Tipos de enemigo del backend (0..4); el 4 es el camion de 2 casilleros. */
#define NUM_VEHICLE_TYPES 5

/* Rana del jugador, indexada por prana->orientation:
 * 0 arriba, 1 derecha, 2 abajo, 3 izquierda. */
extern ALLEGRO_BITMAP *frog_sprites[4];

extern ALLEGRO_BITMAP *vehicle_sprites[NUM_VEHICLE_TYPES];

/* Troncos de largo variable: punta izquierda + tramo del medio (se
 * repite) + punta derecha. */
extern ALLEGRO_BITMAP *log_left, *log_mid, *log_right;

/* Tortuga a flote y hundiendose (para el parpadeo de aviso). */
extern ALLEGRO_BITMAP *turtle_sprite, *turtle_dive;

/* Rana ya guardada en un hueco-meta. */
extern ALLEGRO_BITMAP *home_frog;

/* Carga el spritesheet y crea los sub-bitmaps.
   - filename: ruta del PNG; NULL usa "sprites.png" (directorio actual).
   - Devuelve 0 si cargo, -1 si no (el juego sigue, con primitivas).
   Requiere al_init() y al_init_image_addon() ya llamados. */
int load_sprites(const char *filename);

void destroy_sprites(void);

/* Hoja completa (NULL si no cargo). La usa a_alphanum.c para el texto. */
ALLEGRO_BITMAP *get_spritesheet(void);

#endif /* A_SPRITES_H */
