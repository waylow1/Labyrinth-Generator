#include <stdio.h>
#include <stdlib.h>

typedef struct cell{
    int x, y, value;
} LabyrinthCell;

void display_matrix(int ** matrix, int lines, int columns){

    for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}   

void free_matrix(int ** matrix, int length){
    for (int i=0;i<length;i++){
        free(matrix[i]);
    }
    free(matrix);
}

void display_labyrinth_numerically(LabyrinthCell ** labyrinth, int lines, int columns){
     for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            printf("%5d", labyrinth[i][j].value);
        }
        printf("\n");
    }
}

void display_labyrinth(LabyrinthCell ** labyrinth, int lines, int columns){
     for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            if (labyrinth[i][j].value == 1){
                printf("#");
            }
            else{
                printf(".");
            }
        }
        printf("\n");
    }
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

void dump_labyrinth(LabyrinthCell ** labyrinth, int lines, int columns){
    char * filename = random_labyrinth_name();
    FILE * file = fopen(filename, "w");
    if (file == NULL){
        perror("Error opening file");
        return;
    }
    for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            fprintf(file, "%d ", labyrinth[i][j].value);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void free_labyrinth(LabyrinthCell ** labyrinth, int length){
    for (int i=0;i<length;i++){
        free(labyrinth[i]);
    }
        free(labyrinth);
}

