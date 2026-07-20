#ifndef EUPDATE_H
#define EUPDATE_H

#include "gamestate.h"


#define SUPPORT_IS_TURTLE(type) ((type) >= 8)

#define DIVE_CYCLE_TICKS 210
#define DIVE_FLOAT_TICKS 120 
#define DIVE_WARN_TICKS  30 

typedef enum {
    SUPPORT_FLOATING,
    SUPPORT_SINKING,
    SUPPORT_DIVED,
    SUPPORT_LOG 
} dive_phase;

int stepEntites(game_state*);
int resetEntites(game_state*);
int updateSupportDive(game_state*);
dive_phase supportDivePhase(const support_entity*);

#endif
