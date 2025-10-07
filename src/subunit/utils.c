#include <stdio.h>
#include <stdlib.h>

typedef struct cell{
    int x, y, value;
} LabyrinthCell;

typedef struct walls{
    int ** walls;
} LabyrinthWalls;

typedef struct labyrinth{
    char ** grid;
    int starting_x, starting_y;
    int ending_x, ending_y;
} Labyrinth;

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
}

char * random_labyrinth_name() {
    int random_number = rand() % 10000;
    char * filename = malloc(26 * sizeof(char)); 
    if (filename == NULL) {
        perror("Unable to allocate memory for filename");
        exit(1);
    }
    snprintf(filename, 26, "config/labyrinth%04d.cfg", random_number);
    return filename;
}

void dump_labyrinth(Labyrinth labyrinth, int lines, int columns){
    char * filename = random_labyrinth_name();
    FILE * file = fopen(filename, "w");
    if (file == NULL){
        perror("Error opening file");
        return;
    }
    for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            fprintf(file, "%c", labyrinth.grid[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}