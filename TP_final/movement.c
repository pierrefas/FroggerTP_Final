#include "movement.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
void movement ()
    extern frog;

<<<<<<< HEAD
    if (event.keyboard.keycode == ALLEGRO_KEY_W || /*joystick*/)  //se mueve para arriba
    {
    frogStepUp(frog);
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_s || /*joystick*/)
    {
    frogStepDown(frog);
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_D || /*joystick*/)
    {
    frogStepRight(frog);
    }
    if ((event.keyboard.keycode == ALLEGRO_KEY_A)|| /*joystick*/)
    {
    frogStepLeft(frog);
    }
=======
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
>>>>>>> 3756c484445296b37edfe653a7e4e1a3210cf0a2
//hay que hacer un IF(entra movimiento direccional (4 casos) por allegro teclado o por joystick){ 
// llame a la funcion de movimiento adecuada, levantando su flag asociado
// haciendo que la funcion asociada ocurra, en caso allegro cambie el sprite y en disp que cambie
// la LED prendida}