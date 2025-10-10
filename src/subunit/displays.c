#include <stdio.h>
#include <stdlib.h>
#include "displays.h"

void display_labyrinth(Labyrinth labyrinth, int lines, int columns){
    lines = lines*2 + 1;
    columns = columns*2 + 1;
    for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            if(labyrinth.grid[i][j] == '#'){
                printf("\u2588");
            }
        else {
                printf("%c", labyrinth.grid[i][j]);
            }
        }
        printf("\n");
    }
}

void display_labyrinth_numerically(LabyrinthCell ** labyrinth, int lines, int columns){
     for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            printf("%5d", labyrinth[i][j].value);
        }
        printf("\n");
    }
}

void display_matrix(int ** matrix, int lines, int columns){

    for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}   