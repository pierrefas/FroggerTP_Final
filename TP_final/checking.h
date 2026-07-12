#ifndef CHECKING_H
#define CHECKING_H

#define STARTLAKE 7
#define ENDLAKE 11
#define ISINSAFEZONE(rana) (((rana)->height > ENDLAKE) && !((((rana)->startcoord>=12)&&((rana)->endcoord<=28))||(((rana)->startcoord>=52)&&((rana)->endcoord<=68)))||(((rana)->startcoord>=92)&&(rana->endcoord<=108))||(((rana)->startcoord>=132)&&((rana)->endcoord<=148))||(((rana)->startcoord>=172)&&((rana)->endcoord<=188)))

#include "entidades.h"

int isDeadFromEnemy(frog_player * rana, enemy_entity * enemigos);
int isDeadLake(frog_player * rana, support_entity * soporte);

#endif