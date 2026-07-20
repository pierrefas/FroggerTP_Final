/*
 * a_pause.h
 *
 * Overlay de pausa para el front-end de Allegro. Solo dibuja: el manejo
 * de teclas (seguir / reiniciar / volver al menu) vive en el loop
 * principal de a_PC_display.c, que es el unico dueño de los eventos.
 */

#ifndef A_PAUSE_H
#define A_PAUSE_H

#include <allegro5/allegro_font.h>

/* Dibuja el velo translucido y las opciones de pausa sobre el target actual. */
void draw_pause_overlay(ALLEGRO_FONT * font);

#endif /* A_PAUSE_H */
