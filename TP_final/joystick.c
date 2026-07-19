#include "joystick.h"
#include "joydrv.h"
#include <stdlib.h>
#include <stdio.h>

int joystic_update(void) { 
    static int isActive = 0; 
    
    joyinfo_t data = joy_read();
    isUp = 0;
    isDwn = 0;
    isRgt = 0;
    isLft = 0;
    if (abs(data.x) < DEADZONE && abs(data.y) < DEADZONE) {
        isActive = 0;
    }

    if (!isActive) { 
        if (data.x > DEADZONE) {
            isRgt = 1;
            isActive = 1; 
        }
        else if (data.x < -DEADZONE) {
            isLft = 1;
            isActive = 1;
        }
        else if (data.y > DEADZONE) {
            isUp = 1;
            isActive = 1;
        }
        else if (data.y < -DEADZONE) {
            isDwn = 1;
            isActive = 1;
        }
    }
    return (data.sw != J_NOPRESS); 
}