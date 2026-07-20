#ifndef A_PAUSE_H
#define A_PAUSE_H

#include "gamestate.h"

/* pause_menu return values */
enum {
    PAUSE_RESUME = 0,
    PAUSE_RESET  = 1,
    PAUSE_QUIT   = 2
};

/* Modal pause menu (keyboard-only).
 * - R  -> return PAUSE_RESET
 * - Esc/Enter/Space -> return PAUSE_RESUME
 * - Q or window close -> return PAUSE_QUIT
 *
 * The menu draws highscores (two columns, 5 entries each) under the text.
 */
int pause_menu(game_state *gs);

#endif /* A_PAUSE_H */