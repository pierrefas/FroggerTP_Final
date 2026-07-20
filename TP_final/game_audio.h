/*
 * game_audio.h
 *
 * Interfaz compartida de efectos de sonido: a_audio.c (Allegro, build de
 * PC) y pi_audio.c (Simple-SDL2-Audio, build headless de la Raspberry
 * Pi) implementan las mismas tres funciones; el build activo elige cual
 * de los dos archivos se compila (ver Debug/subdir.mk), asi que nunca
 * coexisten en un mismo link.
 */

#ifndef GAME_AUDIO_H
#define GAME_AUDIO_H

typedef enum {
    SND_JUMP,
    SND_DEATH,
    SND_GAMEOVER,
    SND_LETRA,
    SND_NEXTLEVEL,
    SND_SALIDA,
    SND_START,
    NUM_GAME_SOUNDS
} game_sound;

/* Carga los 7 efectos. Devuelve 0 si el subsistema de audio quedo listo
 * (aunque algun archivo puntual no haya cargado: audio_play() ignora en
 * silencio esos casos), o distinto de 0 si no hay audio en absoluto para
 * esta sesion (el juego sigue jugable, sin sonido). */
int audio_init(void);

/* No hace nada si audio_init() fallo o si el sonido pedido no cargo. */
void audio_play(game_sound snd);

void audio_destroy(void);

#endif
