#ifndef CHECKING_H
#define CHECKING_H

#define STARTLAKE 7
#define ENDLAKE 11
#define ISINSAFEZONE(rana) (((rana)->height > ENDLAKE) && !((((rana)->startcoord>=12)&&((rana)->endcoord<=28))||(((rana)->startcoord>=52)&&((rana)->endcoord<=68)))||(((rana)->startcoord>=92)&&(rana->endcoord<=108))||(((rana)->startcoord>=132)&&((rana)->endcoord<=148))||(((rana)->startcoord>=172)&&((rana)->endcoord<=188)))

#include "gamestate.h"

int isDeadFromEnemy(game_state*);
int isDeadLake(game_state*);
int isAtEnd(game_state*);

#endif