#include <stdio.h>
#include <stdlib.h>
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
    for (int i=0;i<lines;i++){
        free(labyrinth.grid[i]);
    }
    free(labyrinth.grid);
    labyrinth.grid = NULL;
}

void dump_labyrinth(int seed, int lines, int columns, char * filename){
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

    fprintf(fp, "%d,%d,%d\n", seed, lines, columns);

    fclose(fp);
    free(path);
}

void display_all_available_files(char ** labyrinth_name){
    printf("\n");
    system("ls config/");
    printf("\n");
    printf("Please enter the name of the labyrinth file (without extension): ");
    *labyrinth_name = malloc(100 * sizeof(char));
    scanf("%99s", *labyrinth_name);
}


void load_labyrinth(const char * filename, int * seed, int * lines, int * columns){
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

    printf("Loading labyrinth from file: %s\n", path);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        free(path);
        return;
    }

    fscanf(fp, "%d,%d,%d\n", seed, lines, columns);

    fclose(fp);
    free(path);
}