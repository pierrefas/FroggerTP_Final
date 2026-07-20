/*
 * main.c
 *
 *  Created on: Jul 9, 2026
 *      Author: peterfas
 */

#include <stdio.h>

#ifndef HEADLESS
  /* build de PC (o Pi con HDMI): interfaz grafica con Allegro */
  #include "a_PC_display.h"
#elif defined(IS_PI)
  /* build de Raspberry Pi sin HDMI: display de LEDs + joystick.
   * gameloop.o solo existe en el build cuando IS_PI=1. */
  #include "gameloop.h"
#endif

int main(void)
{
#ifndef HEADLESS

    if (!init_alegro()) {
        fprintf(stderr, "No se pudo inicializar Allegro\n");
        return 1;
    }

    return display() ? 0 : 1;

#elif defined(IS_PI)

    return (run_headless_game() == 0) ? 0 : 1;

#else

    fprintf(stderr, "Build HEADLESS en PC: no hay interfaz disponible.\n"
                    "Recompilar con FORCE_ALLEGRO=yes para la version grafica.\n");
    return 1;

#endif
}
