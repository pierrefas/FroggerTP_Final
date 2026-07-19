/*
 * a_pause.h
 *
 * Minimal pause menu for the Allegro frontend.
 *
 * The frontend should call pause_menu() when it wants to suspend the game loop.
 * The function will block until the player chooses to resume or quit.
 */

#ifndef A_PAUSE_H
#define A_PAUSE_H

/* Blocks and runs a small modal pause menu.
 * - Resume: Enter, Space or Escape
 * - Quit: Q or closing the display window (calls exit(0))
 *
 * This function expects Allegro to be initialized and a display to be current.
 * It performs its own event loop and cleans up before returning.
 */
void pause_menu(void);

#endif /* A_PAUSE_H */