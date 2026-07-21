/*
 * gameloop.h
 *
 * Front-end headless de Raspberry Pi: el equivalente de a_PC_display.c
 * pero para el panel de LEDs + joystick en vez de una ventana Allegro.
 * Corre el mismo backend (gamestate/checking/frogupdates/levelset/
 * highscores) y traduce joystick -> movimientos y estado -> LEDs (via
 * drawleds.c/disdrv.h), alternando entre menu, juego, pausa, cartel de
 * nivel, carga de iniciales y game over. Solo se compila en el build de
 * Pi (IS_PI=1); ver main.c.
 */

#ifndef GAMELOOP_H
#define GAMELOOP_H

/**
 * @return 0 si corrio y termino normalmente, -1 si no se pudo crear
 * el estado inicial del juego (createGame/firstLevel fallaron).
 */
int run_headless_game(void);

#endif // GAMELOOP_H
