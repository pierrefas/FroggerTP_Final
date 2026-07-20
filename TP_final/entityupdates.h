#ifndef EUPDATE_H
#define EUPDATE_H

#include "gamestate.h"

<<<<<<< HEAD
/*******************************************************************************
 * CICLO DE BUCEO DE LAS TORTUGAS
 *
 * Los soportes de tipo tortuga (ver SUPPORT_IS_TURTLE) se hunden
 * periodicamente: a flote -> hundiendose (aun soporta, los front-ends
 * la parpadean como aviso) -> sumergida (NO soporta: si la rana estaba
 * arriba, se ahoga) -> a flote de nuevo. Los ticks son los del backend,
 * asi que el ciclo dura lo mismo que la barra de tiempo relativa en
 * ambas plataformas (~7 seg en PC a 30 fps, ~10 en la Pi a 20 t/s).
 ******************************************************************************/
#define SUPPORT_IS_TURTLE(type) ((type) >= 8)

#define DIVE_CYCLE_TICKS 210
#define DIVE_FLOAT_TICKS 120 /* a flote y firme */
#define DIVE_WARN_TICKS  30  /* hundiendose; el resto del ciclo esta sumergida */
=======

#define SUPPORT_IS_TURTLE(type) ((type) >= 8)

#define DIVE_CYCLE_TICKS 210
#define DIVE_FLOAT_TICKS 120 
#define DIVE_WARN_TICKS  30 
>>>>>>> 046f257db908d7a4cdae0a785937beace1eab9f8

typedef enum {
    SUPPORT_FLOATING,
    SUPPORT_SINKING,
    SUPPORT_DIVED,
<<<<<<< HEAD
    SUPPORT_LOG /* tronco: nunca se hunde */
=======
    SUPPORT_LOG 
>>>>>>> 046f257db908d7a4cdae0a785937beace1eab9f8
} dive_phase;

int stepEntites(game_state*);
int resetEntites(game_state*);
int updateSupportDive(game_state*);
dive_phase supportDivePhase(const support_entity*);

<<<<<<< HEAD
/* Avanza un tick el ciclo de buceo de cada tortuga y actualiza su flag
 * supporting. Llamar una vez por tick desde updateLevel(). */
int updateSupportDive(game_state*);

/* Fase actual del soporte (consulta pura; los front-ends la usan para
 * dibujar el parpadeo de aviso). */
dive_phase supportDivePhase(const support_entity*);

=======
>>>>>>> 046f257db908d7a4cdae0a785937beace1eab9f8
#endif
