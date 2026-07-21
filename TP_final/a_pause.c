/*
 * a_pause.c
 *
 * Overlay de pausa: un velo oscuro translucido con las opciones. No tiene
 * loop de eventos propio ni corta el programa; eso lo decide el loop
 * principal segun la tecla que reciba.
 */

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "a_pause.h"
#include "a_PC_display.h"

void draw_pause_overlay(ALLEGRO_FONT * font){
    
    al_draw_filled_rectangle(0, 0, GAME_WIDTH, GAME_HEIGHT, al_map_rgba(0, 0, 0, 170));

    if (!font) return;

    ALLEGRO_COLOR title = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR item = al_map_rgb(200, 200, 200);

    al_draw_text(font, title, CENTER_X, CENTER_Y - 32, ALLEGRO_ALIGN_CENTER, "PAUSA");
    al_draw_text(font, item, CENTER_X, CENTER_Y - 8, ALLEGRO_ALIGN_CENTER, "ENTER/ESC  SEGUIR");
    al_draw_text(font, item, CENTER_X, CENTER_Y + 6, ALLEGRO_ALIGN_CENTER, "R  REINICIAR");
    al_draw_text(font, item, CENTER_X, CENTER_Y + 20, ALLEGRO_ALIGN_CENTER, "M  SALIR AL MENU");
}
