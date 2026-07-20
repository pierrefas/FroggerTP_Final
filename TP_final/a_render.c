#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "a_render.h"
#include "levelset.h" /* extern level para el HUD */

/* Un color distinto por tipo de entidad (0..4 enemigos, 5..9 soportes). */
static ALLEGRO_COLOR entity_color(int type)
{
    switch (type) {
    case 0: return al_map_rgb(235, 220, 60);   /* auto amarillo */
    case 1: return al_map_rgb(240, 240, 240);  /* auto blanco */
    case 2: return al_map_rgb(210, 70, 210);   /* auto violeta */
    case 3: return al_map_rgb(80, 200, 230);   /* auto celeste */
    case 4: return al_map_rgb(220, 60, 60);    /* camion rojo */
    case 5: return al_map_rgb(150, 100, 50);   /* troncos marrones */
    case 6: return al_map_rgb(170, 115, 60);
    case 7: return al_map_rgb(135, 90, 45);
    case 8: return al_map_rgb(60, 160, 90);    /* tortugas verdes */
    case 9: return al_map_rgb(40, 130, 75);
    default: return al_map_rgb(128, 128, 128);
    }
}

/* Rana de 16x16 en (x, y) mirando segun orientation (0 arriba, 1 derecha,
 * 2 abajo, 3 izquierda): cuerpo redondeado + dos ojos del lado del frente. */
static void draw_frog_at(int x, int y, int orientation)
{
    ALLEGRO_COLOR body = al_map_rgb(70, 220, 70);
    ALLEGRO_COLOR eyes = al_map_rgb(20, 60, 20);

    al_draw_filled_rounded_rectangle(x + 2, y + 2, x + 14, y + 14, 5, 5, body);

    switch (orientation) {
    case 1: /* derecha */
        al_draw_filled_circle(x + 12, y + 5, 1.5, eyes);
        al_draw_filled_circle(x + 12, y + 11, 1.5, eyes);
        break;
    case 2: /* abajo */
        al_draw_filled_circle(x + 5, y + 12, 1.5, eyes);
        al_draw_filled_circle(x + 11, y + 12, 1.5, eyes);
        break;
    case 3: /* izquierda */
        al_draw_filled_circle(x + 4, y + 5, 1.5, eyes);
        al_draw_filled_circle(x + 4, y + 11, 1.5, eyes);
        break;
    default: /* arriba */
        al_draw_filled_circle(x + 5, y + 4, 1.5, eyes);
        al_draw_filled_circle(x + 11, y + 4, 1.5, eyes);
        break;
    }
}

void draw_game_state(game_state * g)
{
    if (!g) return;

    int i;

    /* soportes (lago) */
    for (i = 0; g->psoport[i].type != -1; i++) {
        support_entity * s = &g->psoport[i];
        int y = ROW_TO_Y(s->height);
        al_draw_filled_rounded_rectangle(s->startcoord, y + 2, s->endcoord, y + 14,
                                         4, 4, entity_color(s->type));
    }

    /* enemigos (calle) */
    for (i = 0; g->penemies[i].type != -1; i++) {
        enemy_entity * e = &g->penemies[i];
        int y = ROW_TO_Y(e->height);
        al_draw_filled_rounded_rectangle(e->startcoord, y + 2, e->endcoord, y + 14,
                                         3, 3, entity_color(e->type));
        /* parabrisas para que se lea como vehiculo */
        int mid = (e->startcoord + e->endcoord) / 2;
        al_draw_filled_rectangle(mid - 2, y + 4, mid + 2, y + 12, al_map_rgb(30, 30, 30));
    }

    /* ranas ya guardadas en los huecos-meta */
    for (i = 0; i < NUM_GOAL_SLOTS; i++) {
        if (g->safespaces[i]) {
            draw_frog_at(GOAL_SLOT_X(i), ROW_TO_Y(GOALROW), 2);
        }
    }

    /* la rana del jugador */
    if (g->prana) {
        draw_frog_at(g->prana->startcoord, ROW_TO_Y(g->prana->height), g->prana->orientation);
    }
}

void draw_hud(game_state * g, ALLEGRO_FONT * font, int time_left, int time_total)
{
    if (!g || !font) return;

    al_draw_textf(font, al_map_rgb(255, 255, 255), 4, 4, 0, "SCORE %d", g->score);
    al_draw_textf(font, al_map_rgb(255, 255, 255), GAME_WIDTH - 4, 4,
                  ALLEGRO_ALIGN_RIGHT, "NIVEL %d", level);

    /* vidas: ranitas chicas abajo a la izquierda */
    int i;
    for (i = 0; g->prana && i < g->prana->lives; i++) {
        al_draw_filled_rounded_rectangle(4 + i * 14, GAME_HEIGHT - 13,
                                         14 + i * 14, GAME_HEIGHT - 3,
                                         3, 3, al_map_rgb(70, 220, 70));
    }

    /* barra de tiempo abajo a la derecha (se achica y termina en rojo) */
    int bar_max = 100;
    int w = (time_total > 0) ? (bar_max * time_left) / time_total : 0;
    if (w < 0) w = 0;
    ALLEGRO_COLOR bar = (4 * time_left > time_total) ? al_map_rgb(80, 220, 80)
                                                     : al_map_rgb(220, 60, 60);
    al_draw_rectangle(GAME_WIDTH - 5 - bar_max, GAME_HEIGHT - 13,
                      GAME_WIDTH - 3, GAME_HEIGHT - 3, al_map_rgb(120, 120, 120), 1);
    al_draw_filled_rectangle(GAME_WIDTH - 4 - w, GAME_HEIGHT - 12,
                             GAME_WIDTH - 4, GAME_HEIGHT - 4, bar);
}
