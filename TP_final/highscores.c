#include "highscores.h"

int readHighScores(ScoreEntry * list, int max){

    if(list == NULL || max <= 0){
        return 0;
    }

    int count = 0;

    FILE * file = fopen(HS_FILE, "r");

    if(file == NULL){
        return 0; //Sin archivo todavia: lista vacia (primer uso)
    }

    while(count < max && fscanf(file, "%3s %d", list[count].initials, &list[count].score) == 2){
        count++;
    }

    fclose(file);

    return count;

}

int updateHighScores(const char * new_initials, int new_score){

    ScoreEntry list[HS_MAX_SCORES + 1];
    int count = readHighScores(list, HS_MAX_SCORES);
    int i;

    /* Busco el puesto del puntaje nuevo (a igualdad, queda debajo) */
    int pos = 0;

    while(pos < count && list[pos].score >= new_score){
        pos++;
    }

    /* Desplazo hacia abajo e inserto */
    for(i = count; i > pos; i--){
        list[i] = list[i - 1];
    }

    strncpy(list[pos].initials, (new_initials != NULL) ? new_initials : "---", 3);
    list[pos].initials[3] = '\0';
    list[pos].score = new_score;

    count++;

    if(count > HS_MAX_SCORES){
        count = HS_MAX_SCORES; //Solo persisten los mejores 10
    }

    FILE * file = fopen(HS_FILE, "w");

    if(file == NULL){
        return HS_FILE_ERROR;
    }

    for(i = 0; i < count; i++){
        fprintf(file, "%s %d\n", list[i].initials, list[i].score);
    }

    fclose(file);

    return (pos < HS_MAX_SCORES) ? pos : -1;

}
