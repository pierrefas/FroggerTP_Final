#include "movement.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

extern frog;
void funcion (void){
if(event.keyboard.keycode == ALLEGRO_KEY_W)  //se mueve para arriba
{
    frogStepUp(frog);
}
if (event.keyboard.keycode == ALLEGRO_KEY_S )
{
    frogStepDown(frog);
}
if (event.keyboard.keycode == ALLEGRO_KEY_D)
{
    frogStepRight(frog);
}
if ((event.keyboard.keycode == ALLEGRO_KEY_A))
{
    frogStepLeft(frog);
}
}
//hay que hacer un IF(entra movimiento direccional (4 casos) por allegro teclado o por joystick){ 
// llame a la funcion de movimiento adecuada, levantando su flag asociado
// haciendo que la funcion asociada ocurra, en caso allegro cambie el sprite y en disp que cambie
// la LED prendida}