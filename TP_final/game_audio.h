/*
 * game_audio.h
 *
 * Interfaz comun de audio que declara los 7 efectos de
 * sonido (game_sound) y las tres funciones que cualquier backend debe
 * implementar (audio_init/audio_play/audio_destroy). a_audio.c la
 * implementa con Allegro para el build de PC; se suponía que también se
 *  implementaria con Simple-SDL2-Audio para el build headless de la Raspberry Pi, pero no lo hicimos 
 * porque no conseguimos un jack para probar la salida de audio de la Raspberry Pi. El
 * build activo elige cual de los dos se compila (ver Debug/subdir.mk),
 * asi se evitaban errores de linkeo.
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
