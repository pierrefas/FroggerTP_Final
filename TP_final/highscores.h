#ifndef HIGH_H
#define HIGH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENOTFOUND 55

typedef struct {
    char initials[4]; // 3 chars + null terminator
    int score;
} ScoreEntry;

int compare_scores(const void *a, const void *b);
int updateHighScores(const char *new_initials, int new_score);

#endif