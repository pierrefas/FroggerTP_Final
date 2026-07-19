/*
 * main.c
 *
 *  Created on: Jul 9, 2026
 *      Author: peterfas
 */
#include "a_PC_display.h"

#include <stdio.h> 

#ifndef HEADLESS
  // si el hdmi esta conectado entonces se incluyen las libs
  #include <allegro5/allegro.h>
  #include <allegro5/allegro_font.h>
#elif defined(IS_PI)
  // sin hdmi pero en la Raspberry Pi: gameloop.o (con disdrv.o/joydrv.o)
  // solo existe en el build cuando IS_PI=1, asi que solo la llamamos ahi.
  #include "gameloop.h"
#endif

int main (void){

	#ifndef HEADLESS
	init_alegro(); // inicializo todo lo de alegro en esta funcion
  printf("\n");
  display();
	#elif defined(IS_PI)
	run_headless_game();
	#endif

	return 0;
}
