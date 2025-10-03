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
                printf("  #  ");
            }
            else{
                printf("     ");
            }
        }
        printf("\n");
    }
}

void free_labyrinth(LabyrinthCell ** labyrinth, int length){
    for (int i=0;i<length;i++){
        free(labyrinth[i]);
    }
        free(labyrinth);
}