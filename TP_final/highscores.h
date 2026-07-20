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

/* 1 si score entraria al top 10 (consulta pura: no escribe nada).
 * Los front-ends la usan para pedir iniciales solo cuando vale la pena. */
int hsQualifies(int score);

#endif
