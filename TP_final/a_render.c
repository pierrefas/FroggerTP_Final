// TP_final/render.c
#include <allegro5/allegro.h>
#include "a_sprites.h"
#include "gamestate.h"
#include "a_render.h"

void draw_game_state(game_state *g)
{
    if (!g) return;

    /* Draw supports (e.g. logs/turtles). Decide whether startcoord is tile or pixel.
       If they are tile indices, multiply by FRAME_W (or use ADJCOORDFROG macro for frog). */
    for (int i = 0; i < g->support_count; ++i) {
        support_entity *s = &g->psoport[i];
        if (!s) continue;
        int x = s->startcoord; /* if tile index: x = s->startcoord * FRAME_W; */
        int y = s->height;
        int type_idx = (s->type >= 0 && s->type < NUM_ENEMY_TYPES) ? s->type : 0;
        ALLEGRO_BITMAP *bmp = enemy_sprites[type_idx][0]; /* reuse enemy sprites or create support-specific ones */
        if (bmp) al_draw_bitmap(bmp, x, y, 0);
    }

    /* Draw enemies */
    for (int i = 0; i < g->enemy_count; ++i) {
        enemy_entity *e = &g->penemies[i];
        if (!e) continue;
        int x = e->startcoord;
        int y = e->height;
        int t = (e->type >= 0 && e->type < NUM_ENEMY_TYPES) ? e->type : 0;
        int frame = 0; /* if you implement per-entity animation, pick frame here */
        ALLEGRO_BITMAP *bmp = enemy_sprites[t][frame];
        if (bmp) al_draw_bitmap(bmp, x, y, 0);
    }

    /* Draw frog */
    if (g->prana) {
        int frog_x = ADJCOORDFROG(g->prana->startcoord); /* use macro if frog stores tile index */
        int frog_y = g->prana->height;
        int frog_frame = FROG_IDLE; /* or pick based on prana->orientation */
        ALLEGRO_BITMAP *fbmp = frog_sprites[frog_frame];
        if (fbmp) al_draw_bitmap(fbmp, frog_x, frog_y, 0);
    }
}