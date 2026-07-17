#include "highscores.h"

int compare_scores(const void *a, const void *b){
    return ((ScoreEntry *)b)->score - ((ScoreEntry *)a)->score;
}

int updateHighScores(const char *new_initials, int new_score){
    
    ScoreEntry list[11];

    int count = 0;

    // Leemos y guardamos las puntuaciones del archivo

    FILE *file = fopen("highscores.txt", "r");
    
    if (file != NULL) {

        while (count < 11 && fscanf(file, "%3s %d", list[count].initials, &list[count].score) == 2) {

            count++;

        }

        fclose(file);

    }
    else{

        return FILENOTFOUND;

    }
    
    // Añado la nueva puntuacion
    strncpy(list[count].initials, new_initials, 3);
    list[count].initials[3] = '\0'; // Ensure null-termination
    list[count].score = new_score;
    count++;

    // Ordeno
    qsort(list, count, sizeof(ScoreEntry), compare_scores);

    // Reescribo el archivo

    file = fopen("highscores.txt", "w");

    if (file == NULL) {

        return FILENOTFOUND;
    }

    // Si tenemos menos de 10 puntuaciones escribo esa cantidad
    int limit = (count < 10) ? count : 10;
    
    for (int i = 0; i < limit; i++) {

        fprintf(file, "%s %d\n", list[i].initials, list[i].score);

    }

    fclose(file);
}
