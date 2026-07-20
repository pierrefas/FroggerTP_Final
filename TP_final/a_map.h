/*
 * a_map.h
 *
 * Dibujo del fondo del mapa (agua, huecos-meta, franjas seguras y calle)
 * para el front-end de Allegro. Solo primitivas: no depende de que el
 * spritesheet haya cargado.
 */

#ifndef A_MAP_H
#define A_MAP_H

/* Dibuja el mapa en el target actual (no cambia el target). */
void a_disp_map(void);

#endif /* A_MAP_H */
