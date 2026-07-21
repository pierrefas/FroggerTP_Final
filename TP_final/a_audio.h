/*
 * a_audio.h
 *
 * Version anterior de la interfaz de audio (enum game_sound con nombres
 * SOUND_*). Quedo sin uso: ningun .c del proyecto la incluye, ya que
 * a_audio.c termino implementando la interfaz de game_audio.h (con
 * nombres SND_*) en su lugar. Ademas comparte el guard GAME_AUDIO_H con
 * game_audio.h, asi que no se puede incluir junto a ese archivo sin
 * chocar. Se documenta tal cual esta, sin modificar su contenido.
 */

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