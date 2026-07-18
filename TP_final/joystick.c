////////////////////////////////////////////////////////////////////////////////
//
// Autor: Matías Larrahona
// Código que unifica la lógica del movimiento con el joystick
//
/////////////////////////////////////////////////////////////////////////////////

#include "joystick.h"
#include "entidades.h"
#include "frogupdates.h"
#include "joydrv.h"
#define DEADZONE 100 // zona muerta del joystick

int main (void){

    {
        
        joy_init();
        joyinfo_t data = {0,0,J_NOPRESS};
    
    do
        {
        data = joy_read();
        if (data.x > DEADZONE){
            frogStepRight()
        }
        if (data.x < - DEADZONE){}
        if (data.y > DEADZONE){}
        if (data.y < -DEADZONE){}
        }
        while(data.sw == J_NOPRESS);
}
