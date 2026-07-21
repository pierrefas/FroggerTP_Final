/*
 * a_render.h
 *
 * Dibujo de todo lo que se mueve en el front-end de PC: la rana, los
 * autos/camiones, los troncos/tortugas y la animacion de muerte, mas el
 * HUD (puntaje, nivel, vidas y barra de tiempo). Usa los sprites del
 * arcade cuando el spritesheet cargo y cae a primitivas (rectangulos,
 * circulos) si no.
 */

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

/* Dibuja entidades, huecos-meta reclamados y la rana en el target actual.
 * hide_player: no dibujar la rana del jugador (mientras corre la
 * animacion de muerte en su lugar). */
void draw_game_state(game_state * g, int hide_player);

/* Aviso de que la rana acaba de moverse: los proximos frames se dibujan
 * con el sprite de salto (patas estiradas). */
void frog_anim_jump(void);

/* Un cuadro de la animacion de muerte en el casillero (x, fila row).
 * step va de 0 (splash) a NUM_DEATH_FRAMES - 1 (calavera). */
void draw_death_at(int x, int row, int step);

/* Dibuja puntaje/nivel arriba y vidas/barra de tiempo abajo. */
void draw_hud(game_state * g, ALLEGRO_FONT * font, int time_left, int time_total);

#endif /* A_RENDER_H */
