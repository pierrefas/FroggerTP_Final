#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "a_map.h"
#include "a_render.h" /* ROW_TO_Y + geometria de checking.h */

void a_disp_map(void)
{
    ALLEGRO_COLOR water = al_map_rgb(10, 10, 90);
    ALLEGRO_COLOR grass = al_map_rgb(20, 110, 40);
    ALLEGRO_COLOR strip = al_map_rgb(120, 40, 140); /* franjas seguras violetas */
    ALLEGRO_COLOR road = al_map_rgb(35, 35, 35);
    ALLEGRO_COLOR lane = al_map_rgb(200, 200, 200);

    /* agua: de la fila de llegada al final del lago */
    al_draw_filled_rectangle(0, ROW_TO_Y(GOALROW), GAME_WIDTH,
                             ROW_TO_Y(STARTLAKE) + ADJCOORDFROG(1), water);

    /* fila de llegada: pasto con los 5 huecos-meta de agua */
    int gy = ROW_TO_Y(GOALROW);
    int prev = 0;
    int i;
    for (i = 0; i < NUM_GOAL_SLOTS; i++) {
        al_draw_filled_rectangle(prev, gy, GOAL_SLOT_X(i), gy + ADJCOORDFROG(1), grass);
        prev = GOAL_SLOT_X(i) + ADJCOORDFROG(1);
    }
    al_draw_filled_rectangle(prev, gy, GAME_WIDTH, gy + ADJCOORDFROG(1), grass);

    /* franja segura del medio y fila de salida */
    al_draw_filled_rectangle(0, ROW_TO_Y(SAFEROW), GAME_WIDTH,
                             ROW_TO_Y(SAFEROW) + ADJCOORDFROG(1), strip);
    al_draw_filled_rectangle(0, ROW_TO_Y(0), GAME_WIDTH,
                             ROW_TO_Y(0) + ADJCOORDFROG(1), strip);

    /* calle (filas 1..5) con lineas de carril punteadas */
    al_draw_filled_rectangle(0, ROW_TO_Y(5), GAME_WIDTH, ROW_TO_Y(1) + ADJCOORDFROG(1), road);
    int h, x;
    for (h = 1; h < 5; h++) {
        int y = ROW_TO_Y(h); /* borde entre la fila h y la h+1 */
        for (x = 0; x < GAME_WIDTH; x += 24) {
            al_draw_filled_rectangle(x, y - 1, x + 12, y + 1, lane);
        }
    }
}
