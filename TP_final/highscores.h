/*
 * highscores.h
 *
 * Tabla de mejores puntajes persistida en highscores.txt (texto plano,
 * "INICIALES PUNTAJE" por linea). readHighScores la carga ordenada de
 * mayor a menor; updateHighScores inserta un puntaje nuevo en su posicion
 * y reescribe el archivo quedandose solo con los mejores HS_MAX_SCORES;
 * hsQualifies dice si un puntaje entraria al top sin tener que
 * insertarlo todavia (para decidir si mostrar la pantalla de iniciales).
 */

#ifndef HIGH_H
#define HIGH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HS_MAX_SCORES 10
#define HS_FILE "highscores.txt"
#define HS_FILE_ERROR -2

typedef struct {
    char initials[4]; // 3 chars + terminador nulo
    int score;
} ScoreEntry;


int readHighScores(ScoreEntry * list, int max);
int updateHighScores(const char * new_initials, int new_score);
int hsQualifies(int score);

#endif
