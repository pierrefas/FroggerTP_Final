////////////////////////////////////////////////////////////////////////////////
//
// Autor: Matías Larrahona
// Código que unifica la lógica del movimiento con el joystick
//
/////////////////////////////////////////////////////////////////////////////////

#include "joystick.h"
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
        if (abs(data.x)<DEADZONE && abs(data.y) < DEADZONE)
            {
                isActive = 0;
            }
        if(!isActive) 
            { 
            if (data.x > DEADZONE)
                {
                    isActive = 1;
                    printf("El jugador se movió a la derecha\n");
                    usleep(200000);
                }
            if (data.x < - DEADZONE)
                {
                  isActive = 1;
                    printf("El jugador se movió a la izquierda\n");
                    usleep(200000);
                }
            if (data.y > DEADZONE)
                {
                    isActive = 1;
                    printf("El jugador se movió arriba\n");
                    usleep(200000);
                }
        if (data.y < -DEADZONE)
                {
                    isActive = 1;
                    printf("El jugador se movió abajo\n");
                    usleep(200000);
                }
            }
        }
        while(data.sw == J_NOPRESS);
}
