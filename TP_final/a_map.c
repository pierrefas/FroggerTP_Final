#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "a_sprites.h"
#include "a_PC_display.h"

extern ALLEGRO_BITMAP* bush_0;
extern ALLEGRO_BITMAP* bush_1;
extern ALLEGRO_BITMAP* tile_0;

void a_disp_map (void){

    int i = 0;

    while (i < 28)
    {
        if ((i == 24))
        {
            al_draw_bitmap(bush_0, i * 8, 0, 0);
            i+=4;
        }
        else 
        {
            al_draw_bitmap(bush_0, i * 8, 0, 0);
            i+=4;
            al_draw_bitmap(bush_1, i * 8, 0, 0);
            i++;
            al_draw_bitmap(bush_1, i * 8, 0, 0);
            i++;
        }
    }

    for (i = 0; i < 28; i++)
    {
        al_draw_bitmap(tile_0, i * 16, 128, 0);
        al_draw_bitmap(tile_0, i * 16, 240, 0);
    }
}