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

/* Lee hasta max puntajes del archivo (ya ordenados de mayor a menor).
 * Devuelve la cantidad leida (0 si el archivo todavia no existe). */
int readHighScores(ScoreEntry * list, int max);

/* Inserta un puntaje nuevo en el top 10 y reescribe el archivo.
 * Devuelve el puesto obtenido (0 = primero), -1 si no entro al top 10,
 * o HS_FILE_ERROR si no se pudo escribir el archivo. */
int updateHighScores(const char * new_initials, int new_score);

/* 1 si score entraria al top 10 (consulta pura: no escribe nada).
 * Los front-ends la usan para pedir iniciales solo cuando vale la pena. */
int hsQualifies(int score);

#endif
