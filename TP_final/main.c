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
  // sino nada, despues veo si agrego algo mas aca o si mati necesita algo
#endif

int main (void){
	#ifndef HEADLESS
	init_alegro(); // inicializo todo lo de alegro en esta funcion

  display();
	#endif
	
	return 0;
}
