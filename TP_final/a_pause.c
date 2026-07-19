#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "a_PC_display.h"
#include "a_alphanum.h"

void pause_menu (void){
    
    al_clear_to_color(al_map_rgb(0, 0, 0));

    char * menu = "hola";

    index_disp(menu, sizeof(menu), CENTER_X, CENTER_Y, 0);

}
