#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "a_map.h"
#include "a_render.h" /* ROW_TO_Y + geometria de checking.h */
#include "a_sprites.h"

/* La fila de llegada del arcade: un arco de arbusto (con la boca del
 * hueco-meta) centrado en cada slot, y arbusto angosto rellenando los
 * huecos entre arcos. El arco es mas alto que un casillero (23 px), asi
 * que se apoya en el borde inferior de la fila y sobresale hacia arriba. */
static void draw_goal_row_bushes(void)
{
    int arch_w = al_get_bitmap_width(bush_arch);   /* 32 */
    int arch_h = al_get_bitmap_height(bush_arch);  /* 23 */
    int fill_w = al_get_bitmap_width(bush_fill);   /* 8 */
    int y = ROW_TO_Y(GOALROW) + ADJCOORDFROG(1) - arch_h;
    int x, i;

    /* relleno entre arcos (salteando el ancho de cada arco) */
    for (x = 0; x < GAME_WIDTH; x += fill_w) {

        int inside_arch = 0;

        for (i = 0; i < NUM_GOAL_SLOTS; i++) {
            int ax = GOAL_SLOT_X(i) - (arch_w - ADJCOORDFROG(1)) / 2;
            if (x + fill_w > ax && x < ax + arch_w) {
                inside_arch = 1;
                break;
            }
        }

        if (!inside_arch) {
            al_draw_bitmap(bush_fill, x, y, 0);
        }
    }

    for (i = 0; i < NUM_GOAL_SLOTS; i++) {
        al_draw_bitmap(bush_arch, GOAL_SLOT_X(i) - (arch_w - ADJCOORDFROG(1)) / 2, y, 0);
    }
}

void a_disp_map(void)
{
    ALLEGRO_COLOR water = al_map_rgb(10, 10, 90);
    ALLEGRO_COLOR grass = al_map_rgb(20, 110, 40);
    ALLEGRO_COLOR strip = al_map_rgb(120, 40, 140); /* franjas seguras violetas */
    ALLEGRO_COLOR road = al_map_rgb(35, 35, 35);
    ALLEGRO_COLOR lane = al_map_rgb(200, 200, 200);
    int x;

    /* agua: de la fila de llegada al final del lago (queda tambien de
     * fondo en las bocas de los huecos-meta, detras de los arcos) */
    al_draw_filled_rectangle(0, ROW_TO_Y(GOALROW), GAME_WIDTH,
                             ROW_TO_Y(STARTLAKE) + ADJCOORDFROG(1), water);

    /* fila de llegada: arbustos del spritesheet o pasto de respaldo */
    if (bush_arch && bush_fill) {
        draw_goal_row_bushes();
    } else {
        int gy = ROW_TO_Y(GOALROW);
        int prev = 0;
        int i;
        for (i = 0; i < NUM_GOAL_SLOTS; i++) {
            al_draw_filled_rectangle(prev, gy, GOAL_SLOT_X(i), gy + ADJCOORDFROG(1), grass);
            prev = GOAL_SLOT_X(i) + ADJCOORDFROG(1);
        }
        al_draw_filled_rectangle(prev, gy, GAME_WIDTH, gy + ADJCOORDFROG(1), grass);
    }

    /* franja segura del medio y fila de salida: vereda del arcade */
    if (sidewalk_tile) {
        for (x = 0; x < GAME_WIDTH; x += ADJCOORDFROG(1)) {
            al_draw_bitmap(sidewalk_tile, x, ROW_TO_Y(SAFEROW), 0);
            al_draw_bitmap(sidewalk_tile, x, ROW_TO_Y(0), 0);
        }
    } else {
        al_draw_filled_rectangle(0, ROW_TO_Y(SAFEROW), GAME_WIDTH,
                                 ROW_TO_Y(SAFEROW) + ADJCOORDFROG(1), strip);
        al_draw_filled_rectangle(0, ROW_TO_Y(0), GAME_WIDTH,
                                 ROW_TO_Y(0) + ADJCOORDFROG(1), strip);
    }

    /* calle (filas 1..5) con lineas de carril punteadas */
    al_draw_filled_rectangle(0, ROW_TO_Y(5), GAME_WIDTH, ROW_TO_Y(1) + ADJCOORDFROG(1), road);
    int h;
    for (h = 1; h < 5; h++) {
        int y = ROW_TO_Y(h); /* borde entre la fila h y la h+1 */
        for (x = 0; x < GAME_WIDTH; x += 24) {
            al_draw_filled_rectangle(x, y - 1, x + 12, y + 1, lane);
        }
    }
}
