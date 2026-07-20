/*
 * a_audio.c
 *
 * Efectos de sonido del front-end de PC (Allegro 5). Carga los WAV una
 * sola vez al arrancar y los reproduce con al_play_sample; si el
 * dispositivo de audio o algun archivo no esta disponible, el juego
 * sigue jugable en silencio (mismo criterio que load_sprites()).
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "game_audio.h"

#define NUM_RESERVED_SAMPLES 8

static const char * SOUND_FILES[NUM_GAME_SOUNDS] = {
    "audio/frog_jump.wav",
    "audio/sonido_death.wav",
    "audio/sonido_gameover.wav",
    "audio/sonido_letra.wav",
    "audio/sonido_nextlevel.wav",
    "audio/sonido_salida.wav",
    "audio/sonido_start.wav",
};

static ALLEGRO_SAMPLE * samples[NUM_GAME_SOUNDS] = { NULL };
static int audio_ready = 0;

int audio_init(void)
{
    int i;

    if (!al_install_audio() || !al_init_acodec_addon() ||
        !al_reserve_samples(NUM_RESERVED_SAMPLES)) {
        fprintf(stderr, "a_audio: no se pudo iniciar el audio\n");
        return -1;
    }

    audio_ready = 1;

    for (i = 0; i < NUM_GAME_SOUNDS; i++) {
        samples[i] = al_load_sample(SOUND_FILES[i]);
        if (!samples[i]) {
            fprintf(stderr, "a_audio: no se pudo cargar %s\n", SOUND_FILES[i]);
        }
    }

    return 0;
}

void audio_play(game_sound snd)
{
    if (!audio_ready || snd < 0 || snd >= NUM_GAME_SOUNDS || !samples[snd]) {
        return;
    }

    al_play_sample(samples[snd], 1.0, ALLEGRO_AUDIO_PAN_NONE, 1.0,
                   ALLEGRO_PLAYMODE_ONCE, NULL);
}

void audio_destroy(void)
{
    int i;

    for (i = 0; i < NUM_GAME_SOUNDS; i++) {
        if (samples[i]) {
            al_destroy_sample(samples[i]);
            samples[i] = NULL;
        }
    }

    audio_ready = 0;
}
