#include <stdio.h>

void display_matrix(int ** matrix, int lines, int columns){

    for(int i=0;i<lines;i++){
        for(int j=0;j<columns;j++){
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
}   