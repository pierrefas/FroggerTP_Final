#include "gamestate.h"

/* a_frog_move provides simple helpers the frontend can call when input occurs.
 * These are intentionally minimal — actual movement rules and collision checks
 * should remain in the backend (frogupdates.c / entityupdates.c). */

void frog_move_up(game_state *g)
{
    if (!g || !g->prana) return;
    g->prana->startcoord -= 1; /* move one tile up (interpretation depends on your coords) */
}

void frog_move_down(game_state *g)
{
    if (!g || !g->prana) return;
    g->prana->startcoord += 1;
}

void frog_move_left(game_state *g)
{
    if (!g || !g->prana) return;
    g->prana->startcoord -= 1;
}

void frog_move_right(game_state *g)
{
    if (!g || !g->prana) return;
    g->prana->startcoord += 1;
}
