#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "a_sprites.h"
#include "a_PC_display.h"

extern bush_0;

void a_disp_map (void){

    int i = 0;

    while (i < GAME_WIDTH)
    {
        if ((i % 2) == 0)
        {
            al_draw_bitmap(bush_0, i * 8, 0, 0);
            i+=3;
        }
        else 
        {
            al_draw_bitmap(bush_1, i * 8, 0, 0);
            i++;
        }
    }
}