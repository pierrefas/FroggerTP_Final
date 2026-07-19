
/*
 * a_map.h
 *
 * Simple map / tile drawing helpers for the Frogger frontend.
 *
 * The implementation draws a background strip, a row of decorative bushes
 * and two rows of tiles. It prefers exported sub-bitmaps from a_sprites;
 * when those are NULL it falls back to drawing regions from the spritesheet.
 *
 * Tune the TILE_* / SRC_* macros before including this header if your
 * spritesheet layout differs.
 */

#ifndef A_MAP_H
#define A_MAP_H

#include <allegro5/allegro.h>
#include "a_sprites.h"

/* Geometry defaults - override these before including if needed */
#ifndef TILE_W
#define TILE_W 16
#endif

#ifndef TILE_H
#define TILE_H 16
#endif

/* Fallback source coordinates (on the spritesheet) for drawing bushes/tiles.
   Override before including if your sheet layout differs. Coordinates are
   in pixels (top-left corner). */
#ifndef SRC_BUSH_0_X
#define SRC_BUSH_0_X 0
#endif
#ifndef SRC_BUSH_0_Y
#define SRC_BUSH_0_Y 0
#endif

#ifndef SRC_BUSH_1_X
#define SRC_BUSH_1_X 8
#endif
#ifndef SRC_BUSH_1_Y
#define SRC_BUSH_1_Y 0
#endif

#ifndef SRC_TILE_0_X
#define SRC_TILE_0_X 0
#endif
#ifndef SRC_TILE_0_Y
#define SRC_TILE_0_Y 32
#endif

/* Public API
 *
 * a_disp_map()
 *   Draws the map elements into the current Allegro target (does not change
 *   the target bitmap). The implementation expects Allegro to be initialized
 *   and the sprites to be loaded (load_sprites() called), so get_spritesheet()
 *   / tile bitmaps exported by a_sprites are available.
 */
void a_disp_map(void);

#endif /* A_MAP_H */