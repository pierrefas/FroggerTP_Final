/*
 * gameloop.h
 *
 * Orquestador del juego para el hardware fisico de la Raspberry Pi
 * (display de LEDs de 16x16 + joystick analogico). Conecta el
 * joystick con el movimiento de la rana y con el dibujado en el
 * display, algo que hasta ahora ningun archivo hacia: joystick.c,
 * drawleds.c, frogupdates.c, entityupdates.c y levelset.c ya existian
 * por separado, pero nada los llamaba juntos en un mismo ciclo.
 */

#ifndef GAMELOOP_H
#define GAMELOOP_H

/**
 * @brief Corre el juego completo sobre el hardware fisico (disp_* +
 * joy_*) hasta que el jugador se queda sin vidas. Bloqueante.
 * @return 0 si corrio y termino normalmente, -1 si no se pudo crear
 * el estado inicial del juego (createGame/firstLevel fallaron).
 */
int run_headless_game(void);

#endif // GAMELOOP_H
