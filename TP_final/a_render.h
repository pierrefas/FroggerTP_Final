#ifndef A_RENDER_H
#define A_RENDER_H

#include <allegro5/allegro_font.h>

#include "gamestate.h"
#include "checking.h"
#include "a_PC_display.h"

/* Fila del backend -> pixel y (borde superior del casillero) en pantalla.
 * La fila 0 (salida) queda a dos casilleros del borde inferior: la ultima
 * franja de 16 px es HUD (vidas + barra de tiempo). */
#define ROW_TO_Y(h) (GAME_HEIGHT - ADJCOORDFROG(2) - ADJCOORDFROG(h))

/* Dibuja entidades, huecos-meta reclamados y la rana en el target actual. */
void draw_game_state(game_state * g);

/* Dibuja puntaje/nivel arriba y vidas/barra de tiempo abajo. */
void draw_hud(game_state * g, ALLEGRO_FONT * font, int time_left, int time_total);

#endif /* A_RENDER_H */
