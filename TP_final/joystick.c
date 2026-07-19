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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (void)

    {   
        int isActive; 
        joy_init();
        joyinfo_t data = {0,0,J_NOPRESS};
    
    do
        {
        data = joy_read();
        if (abs(data.x)<DEADZONE && abs(data.x) < DEADZONE)
            {
                isActive = 0;
            }
        if(!isActive) 
            { 
            if (data.x > DEADZONE)
                {
                    isActive = 1;
                    printf("El jugador se movió a la derecha");
                }
            if (data.x < - DEADZONE)
                {
                  isActive = 1;
                    printf("El jugador se movió a la izquierda");
                }
            if (data.y > DEADZONE)
                {
                    isActive = 1;
                    printf("El jugador se movió arriba");
                }
        if (data.y < -DEADZONE)
                {
                    isActive = 1;
                    printf("El jugador se movió abajo");
                }
            }
        }
        while(data.sw == J_NOPRESS);
}
