#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

LabyrinthCell ** allocate_labyrinth(int length, int width){
    LabyrinthCell ** labyrinth = malloc(sizeof(LabyrinthCell*)*length);
    int value = 0;
    for(int i = 0; i < length; i++){
        labyrinth[i] = malloc(sizeof(LabyrinthCell)*width);
        for(int j = 0; j < width; j++){
            labyrinth[i][j].x = i;
            labyrinth[i][j].y = j;
            labyrinth[i][j].value = value++;
        }
    }
    return labyrinth;
}

int ** allocate_matrix_walls(int lines, int columns){
    int ** matrix = malloc(sizeof(int*)*lines);
    for(int i = 0; i < lines; i++){
        matrix[i] = malloc(sizeof(int)*columns);
        for(int j = 0; j < columns; j++){
            matrix[i][j] = 1;
        }
    }
    return matrix;
}

void free_matrix(int ** matrix, int length){
    for (int i=0;i<length;i++){
        free(matrix[i]);
    }
    free(matrix);
}

void free_labyrinth_cells(LabyrinthCell ** labyrinth, int length){
    for (int i=0;i<length;i++){
        free(labyrinth[i]);
    }
        free(labyrinth);
}

void free_labyrinth(Labyrinth labyrinth, int lines, int columns){
    if (labyrinth.grid) {
        for (int i=0;i<lines;i++){
            free(labyrinth.grid[i]);
        }
        free(labyrinth.grid);
    }
    if (labyrinth.extras) {
        if (labyrinth.extras->extra.monsters) free(labyrinth.extras->extra.monsters);
        free(labyrinth.extras);
    }
}

void dump_labyrinth_ext(int seed, int lines, int columns, Difficulty diff, char * filename){
    if (!filename) return;
    size_t len = 0;
    while (filename[len]) len++;

    const char prefix[] = "config/";
    size_t prefix_len = sizeof(prefix) - 1;
    char *path = malloc(prefix_len + len + 5);
    if (!path) return;

    size_t k = 0;
    for (size_t i = 0; i < prefix_len; ++i) path[k++] = prefix[i];
    for (size_t i = 0; i < len; ++i) path[k++] = filename[i];
    path[k++] = '.';
    path[k++] = 'c';
    path[k++] = 'f';
    path[k++] = 'g';
    path[k] = '\0';

    FILE *fp = fopen(path, "w");
    if (!fp) {
        free(path);
        return;
    }

    fprintf(fp, "%d,%d,%d,%d\n", seed, lines, columns, (int)diff);

    fclose(fp);
    free(path);
}

void dump_labyrinth(int seed, int lines, int columns, char * filename){
    dump_labyrinth_ext(seed, lines, columns, DIFF_EASY, filename);
}

void display_all_available_files(char ** labyrinth_name){
    printf("\n");
    system("ls config/");
    printf("\n");
    printf("Please enter the name of the labyrinth file (without extension): ");
    *labyrinth_name = malloc(100 * sizeof(char));
    scanf("%99s", *labyrinth_name);
}


void load_labyrinth_ext(const char *filename, int *seed, int *lines, int *columns, Difficulty *diff) {
    if (!filename || !seed || !lines || !columns) {
        fprintf(stderr, "❌ Invalid arguments to load_labyrinth().\n");
        return;
    }

    const char prefix[] = "config/";
    size_t len = strlen(filename);
    size_t path_len = strlen(prefix) + len + 5;
    char *path = malloc(path_len);
    if (!path) {
        fprintf(stderr, "❌ Memory allocation failed for path.\n");
        return;
    }

    snprintf(path, path_len, "%s%s.cfg", prefix, filename);

    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "⚠️  File not found: %s\n", path);
        free(path);
        *seed = *lines = *columns = 0; 
        return;
    }

    printf("Loading labyrinth from file: %s\n", path);

    int sd=0, ln=0, col=0, df=-1;
    int read = fscanf(fp, "%d,%d,%d,%d", &sd, &ln, &col, &df);
    if (read < 3) {
        fprintf(stderr, "⚠️  Invalid labyrinth file format: %s\n", path);
        *seed = *lines = *columns = 0;
        if (diff) *diff = DIFF_EASY;
    } else {
        *seed = sd; *lines = ln; *columns = col;
        if (read == 4 && diff) {
            *diff = (df == 1 ? DIFF_HARD : DIFF_EASY);
        } else if (diff) {
            *diff = DIFF_EASY;
        }
        printf("✅ Loaded labyrinth parameters: seed=%d, lines=%d, columns=%d\n", *seed, *lines, *columns);
        if (read == 4) {
            printf("✅ Loaded difficulty: %s\n", (df==1?"HARD":"EASY"));
        }
    }

    fclose(fp);
    free(path);
}

void load_labyrinth(const char *filename, int *seed, int *lines, int *columns) {
    Difficulty tmp;
    load_labyrinth_ext(filename, seed, lines, columns, &tmp);
}