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
#else
  // sin hdmi, corremos el juego sobre el display de LEDs + joystick
  #include "gameloop.h"
#endif

int main (void){

	#ifndef HEADLESS
	init_alegro(); // inicializo todo lo de alegro en esta funcion
  printf("\n");
  display();
	#else
	run_headless_game();
	#endif

	return 0;
}
