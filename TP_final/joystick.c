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

int joystick (void)

    {   
        int isActive; 
        joy_init();
        joyinfo_t data = {0,0,J_NOPRESS};
    
    do
        {
        data = joy_read();
        if (abs(data.x)<DEADZONE && abs(data.y) < DEADZONE)
            {
                isUp = 0;
                isDwn = 0;
                isRgt = 0;
                isLft = 0;
                isActive = 0;
            }
        if(!isActive) 
            { 
            if (data.x > DEADZONE)
                {
                    isRgt = 1;
                    isActive = 1;
                    usleep(200000);
                }
            if (data.x < - DEADZONE)
                {
                  isLft = 1;
                  isActive = 1;
                    usleep(200000);
                }
            if (data.y > DEADZONE)
                {
                    isUp = 1;
                    isActive = 1;
                    usleep(200000);
                }
        if (data.y < -DEADZONE)
                {
                    isDwn = 0;
                    isActive = 1;
                    usleep(200000);
                }
            }
        }
        while(data.sw == J_NOPRESS);

        return 1;
}
