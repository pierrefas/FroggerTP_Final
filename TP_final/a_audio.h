#ifndef GAME_AUDIO_H
#define GAME_AUDIO_H

/* Enumeración de sonidos del juego */
typedef enum {
    SOUND_FROG_JUMP = 0,
    SOUND_DEATH,
    SOUND_GAMEOVER,
    SOUND_LETTER,
    SOUND_NEXTLEVEL,
    SOUND_EXIT,
    SOUND_START,

    NUM_GAME_SOUNDS
} game_sound;

/* Inicializa el sistema de audio.
 * Devuelve 0 si OK, -1 si falla.
 */
int audio_init(void);

/* Reproduce un sonido */
void audio_play(game_sound snd);

/* Libera recursos de audio */
void audio_destroy(void);

#endif /* GAME_AUDIO_H */