//aca voy a poner los "sprites" de las letras del frogger

#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "a_sprites.h"
#include "a_PC_display.h"

#define FRAME_WH_8_BIT 8

#define POSITION_16_BIT 232 // todos los sprites estan defazados en 1 pixel en x, asi que lo unico que importa es el y

#define POSITION_8_BIT 250

#define COLOR_OFFSET 28 //puedo cambiar el color de las letras sabiendo que todas varian en 28 px del siguiente color. Capaz lo use, capaz no.

extern ALLEGRO_BITMAP* sprites;

//pienso hacer dos funciones (una para las letras de 16*16 y otra para las de 8*8) que reciban un array y que
// vaya leyendo los ints de ese array, por ejemplo si el valor es 0 en el de 16*16 devuelve o imprime en pantalla el bitmap
//  de la F. Lo hago vla porque no se cuantas veces lo voy a usar y para que.

int index_disp (char * arr, int size, int x, int y, int color){

    if ( arr == NULL)
    {
        return 1;
    }

    if ( size <= 0)
    {
        return 0;
    }

    if ( ( x < 0 ) || ( y < 0 ) )
    {
        return 2;
    }
    if ( ( x > GAME_WIDTH ) || ( y > GAME_HEIGHT ) )
    {
        return 3;
    }

    if (color > 3 || color < 0)
    {
        color = 0;
    }

    int a = 0;

    int row = 0;

    ALLEGRO_BITMAP* sprite_alphanum = NULL;

    int i;

    int index;

    int space;

    for (i = 0; i < size; i += 1)   //estoy re gaga, me acabo de dar cuenta que escribi i+=1 en vez de i++, ahora lo dejo porque me da risa
    {
        space = 0;

        if((arr[i] >= 'a') && (arr[i] <= 'z'))
        {
            index = arr[i] - 'a' + 10;
        }
        else if((arr[i] >= 'A') && (arr[i] <= 'Z'))
        {
            index = arr[i] - 'A' + 10;
        }
        else if((arr[i] >= '0') && (arr[i] <= '9'))
        {
            index = arr[i] - '0';
        }
        else if( arr[i] == ' ')
        {
            space = 1;
        }
        else if( arr[i] == '\n')
        {
            y+=8;
        }
        else
        {
            index = 38; // si no encuentro valor para i, entonces devuelvo el cuadradito raro ese que hay en el sprite N39
        }
        
        if (index > 16 && index <= 32)
        {
            index -= 16;
            row = 1;
            
        }
        else if (index > 32)
        {
            index -= 32;
            row = 2;
        }

        if(!space){

            sprite_alphanum = al_create_sub_bitmap( sprites, 1 + index*8, POSITION_8_BIT + color * COLOR_OFFSET + row * 8, FRAME_WH_8_BIT, FRAME_WH_8_BIT);

            al_draw_bitmap(sprite_alphanum, x + a, y, 0);

        }

        a+= FRAME_WH_8_BIT;
        if ((x + a > GAME_WIDTH) && (arr[i] != '\n'))
        {
            x = 0;
            a = 0;
            y += 8;
        }

        if ((y > GAME_HEIGHT))
        {
            return 0;
        }

    }

    al_destroy_bitmap(sprite_alphanum);

    return 0;

}