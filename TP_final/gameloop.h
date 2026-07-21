/*
 * gameloop.h
 * integración de joystick.c drawleds.c, frogupdates.c, entityupdates.c
 * y levelupdtates.c para correr el juego en la raspberry hasta que el 
 * jugador se queda sin vidas
 */

#ifndef GAMELOOP_H
#define GAMELOOP_H

/**
 * @return 0 si corrio y termino normalmente, -1 si no se pudo crear
 * el estado inicial del juego (createGame/firstLevel fallaron).
 */
int run_headless_game(void);

#endif // GAMELOOP_H
