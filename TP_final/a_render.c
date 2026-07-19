#include "a_render.h"
#include "a_sprites.h"
#include <allegro5/allegro.h>

void draw_game_state(game_state *g)
{
    if (!g) return;

    /* Draw supports */
    for (int i = 0; i < g->support_count && i < MAX_ENTITIES; ++i) {
        support_entity *s = &g->psoport[i];
        if (!s) continue;
        if (s->type == 0) continue; /* unused sentinel */
        int x = s->startcoord; /* if tile index, multiply by FRAME_W elsewhere */
        int y = s->height;
        int type_idx = (s->type >= 0 && s->type < NUM_ENEMY_TYPES) ? s->type : 0;
        ALLEGRO_BITMAP *bmp = enemy_sprites[type_idx][0];
        if (bmp) al_draw_bitmap(bmp, x, y, 0);
    }

    /* Draw enemies */
    for (int i = 0; i < g->enemy_count && i < MAX_ENTITIES; ++i) {
        enemy_entity *e = &g->penemies[i];
        if (!e) continue;
        if (e->type == 0) continue;
        int x = e->startcoord;
        int y = e->height;
        int t = (e->type >= 0 && e->type < NUM_ENEMY_TYPES) ? e->type : 0;
        int frame = 0;
        ALLEGRO_BITMAP *bmp = enemy_sprites[t][frame];
        if (bmp) al_draw_bitmap(bmp, x, y, 0);
    }

    /* Draw frog */
    if (g->prana) {
        int frog_x = ADJCOORDFROG(g->prana->startcoord);
        int frog_y = g->prana->height;
        int frog_frame = FROG_IDLE;
        ALLEGRO_BITMAP *fbmp = frog_sprites[frog_frame];
        if (fbmp) al_draw_bitmap(fbmp, frog_x, frog_y, 0);
    }
}
