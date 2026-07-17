/*
 * display.h
 *
 *  Created on: Jul 9, 2026
 *      Author: peterfas
 */


#ifndef a_PC_DISPLAY_H
#define a_PC_DISPLAY_H

// Game resolution constants accessible by any file including this header
#define GAME_HEIGHT 256
#define GAME_WIDTH 224

#define CENTER_X  (GAME_WIDTH / 2)
#define CENTER_Y  (GAME_HEIGHT / 2)

/**
 * @brief Initializes Allegro, creates the auto-scaling fullscreen display,
 * and runs the main game loop.
 * * @return int Returns 0 on successful exit, or 1 if initialization fails.
 */
int display(void);

void init_alegro(void);

#endif /* a_PC_DISPLAY_H */
