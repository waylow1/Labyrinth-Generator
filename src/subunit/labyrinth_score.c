#include <stdio.h>
#include <stdlib.h>
#include "labyrinth_score.h"    
#include <stdlib.h>

int create_score_file_if_not_exists(char * labyrinth_name){
    if (!labyrinth_name) return -1;
    char filename[256];
    snprintf(filename, sizeof(filename), "score/%s.score", labyrinth_name);

    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fclose(fp);
        return 0; 
    }

    fp = fopen(filename, "wb");
    if (!fp) {
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
    printf("Adding new score: %s with %d coins\n", new_player.name, new_player.coins);
    if (ladder->count < 10) {
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
    for(int i=0;i<ladder->count-1;i++){
        for(int j=0;j<ladder->count-i-1;j++){
            if(ladder->scores[j].coins< ladder->scores[j+1].coins){
                Score temp = ladder->scores[j];
                ladder->scores[j] = ladder->scores[j+1];
                ladder->scores[j+1] = temp;
            }
        }
    }
    return 0;
}

void load_labyrinth_scores(Ladder * ladder, const char * labyrinth_name){
    if (!ladder || !labyrinth_name) return;

    char filename[256];
    snprintf(filename, sizeof(filename), "score/%s.score", labyrinth_name);

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return;
    }

    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return; }
    long file_size = ftell(fp);
    if (file_size <= 0) { fclose(fp); return; }

    rewind(fp);

    size_t entry_size = sizeof(Score);
    if (entry_size == 0) { fclose(fp); return; }

    size_t count = (size_t)file_size / entry_size;
    if (count == 0) { fclose(fp); return; }


    if (((size_t)file_size % entry_size) != 0) {
        fclose(fp);
        return;
    }

    const size_t MAX_SCORES = 10;
    if (count > MAX_SCORES) count = MAX_SCORES;

    if (!ladder->scores) { fclose(fp); return; }

    Score * scores = malloc(count * entry_size);
    if (!scores) { fclose(fp); return; }

    size_t read = fread(scores, entry_size, count, fp);
    if (read != count) {
        free(scores);
        fclose(fp);
        return;
    }

    ladder->count = (int)count;

    free(scores);
    fclose(fp);
}

int display_ladder(Ladder ladder){

    if (!ladder.scores || ladder.count == 0) {
        printf("No scores available.\n");
        return -1;
    }

    printf("\n--- High Scores ---\n");
    for (size_t i = 0; i < ladder.count; i++) {
        printf("%zu. %s - %d coins\n", i + 1, ladder.scores[i].name, ladder.scores[i].coins);
    }
    printf("-------------------\n\n");
    return 0;
}

int dump_scores(Ladder ladder, char *labyrinth_name){
    
    if ((!ladder.scores && ladder.count > 0) || !labyrinth_name) return -1;
    char filename[256];
    snprintf(filename, sizeof(filename), "score/%s.score", labyrinth_name);

    FILE *fp = fopen(filename, "wb");
    if (!fp) return -1;

    if (ladder.count > 0) {
        size_t written = fwrite(ladder.scores, sizeof(Score), ladder.count, fp);
        fclose(fp);
        return (written == ladder.count) ? 0 : -1;
    }

    fclose(fp);
    return 0;
}