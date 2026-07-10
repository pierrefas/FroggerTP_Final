/*
 * display.h
 *
 *  Created on: Jul 9, 2026
 *      Author: peterfas
 */


#ifndef PC_DISPLAY_H
#define PC_DISPLAY_H

// Game resolution constants accessible by any file including this header
#define GAME_HEIGHT 256
#define GAME_WIDTH 224

/**
 * @brief Initializes Allegro, creates the auto-scaling fullscreen display,
 * and runs the main game loop.
 * * @return int Returns 0 on successful exit, or 1 if initialization fails.
 */
int display(void);

#endif /* PC_DISPLAY_H */
