#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labyrinth_score.h"    

#define MAX_SCORES 10

int create_score_file_if_not_exists(char * labyrinth_name){
    if (!labyrinth_name) return -1;

    char filename[256];
    snprintf(filename, sizeof(filename), "score/%s.score", labyrinth_name);

    FILE *fp = fopen(filename, "r");
    if (fp) {
        fclose(fp);
        return 0; 
    }

    fp = fopen(filename, "w");
    if (!fp) {
        perror("Error creating score file");
        return -1; 
    }

    fclose(fp);
    return 0; 
}

void end_of_game_dialog(Score * score){
    printf("Game Over!\n");
    printf("You finished the labyrinth with %d coins.\n", score->coins);
    printf("Please enter your name for the high score list: ");
    scanf("%99s", score->name);
}

int add_new_score(Ladder * ladder, Score new_player){
    if (!ladder || !ladder->scores) return -1;

    printf("Adding new score: %s with %d coins\n", new_player.name, new_player.coins);

    if (ladder->count < MAX_SCORES) {
        ladder->scores[ladder->count] = new_player;
        ladder->count++;
    } else if (new_player.coins > ladder->scores[ladder->count - 1].coins) {
        ladder->scores[ladder->count - 1] = new_player;
    } else {
        return 0; 
    }

    printf("Score added successfully.\n");
    return 0;
}

int sort_scores(Ladder * ladder){
    if (!ladder || !ladder->scores) return -1;

    for(int i = 0; i < ladder->count - 1; i++){
        for(int j = 0; j < ladder->count - i - 1; j++){
            if(ladder->scores[j].coins < ladder->scores[j + 1].coins){
                Score temp = ladder->scores[j];
                ladder->scores[j] = ladder->scores[j + 1];
                ladder->scores[j + 1] = temp;
            }
        }
    }
    return 0;
}

void load_labyrinth_scores(Ladder * ladder, const char * labyrinth_name){
    if (!ladder || !labyrinth_name) return;

    ladder->count = 0;

    char filename[256];
    snprintf(filename, sizeof(filename), "score/%s.score", labyrinth_name);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No score file found for %s.\n", labyrinth_name);
        return;
    }

    while (ladder->count < MAX_SCORES && 
           fscanf(fp, "%99s %d", ladder->scores[ladder->count].name,
            &ladder->scores[ladder->count].coins) == 2) {
        ladder->count++;
    }

    fclose(fp);
}

int display_ladder(Ladder ladder){
    if (!ladder.scores || ladder.count == 0) {
        printf("No scores available.\n");
        return -1;
    }

    printf("\n--- High Scores ---\n");
    for (int i = 0; i < ladder.count; i++) {
        printf("%d. %s - %d coins\n", i + 1, ladder.scores[i].name, ladder.scores[i].coins);
    }
    printf("-------------------\n\n");
    return 0;
}

int dump_scores(Ladder ladder, char *labyrinth_name){
    if ((!ladder.scores && ladder.count > 0) || !labyrinth_name) return -1;

    char filename[256];
    snprintf(filename, sizeof(filename), "score/%s.score", labyrinth_name);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error saving scores");
        return -1;
    }

    for (int i = 0; i < ladder.count; i++) {
        fprintf(fp, "%s %d\n", ladder.scores[i].name, ladder.scores[i].coins);
    }

    fclose(fp);
    return 0;
}
