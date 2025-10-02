#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define LAB_LENGTH 11
#define LAB_WIDTH 25

void free_matrix(int ** matrix, int n){
    for (int i=0;i<n;i++){
        free(matrix[i]);
    }
    free(matrix);
}

int ** allocate_labyrinth(){
    int ** matrix = malloc(sizeof(int*)*LAB_LENGTH);
    int value=0;
    for(int i=0;i<LAB_LENGTH;i++){
        matrix[i]=malloc(sizeof(int)*LAB_WIDTH);
        for(int j=0;j<LAB_WIDTH;j++){
            matrix[i][j]=value++;
        }
    }
    return matrix;
}

int ** allocate_matrix_walls(int lines, int columns){
    int ** matrix = malloc(sizeof(int*)*lines);
    for(int i=0;i<lines;i++){
        matrix[i]=malloc(sizeof(int)*columns);
        for(int j=0;j<columns;j++){
            matrix[i][j]=0;
        }
    }
    return matrix;
}


void generate_lab(int ** labyrinth, int ** vertical_walls, int  ** horizontal_walls, int length, int width){
    int count=0;
    while(count < (length*width)+1){
        int random_case = rand()%(length*width);
        int random_wall = (random_case % width == 0) ? rand()%4 : rand()%2;

        


        count++;
    }

}

int main(){

    int ** labyrinth = allocate_labyrinth();

    int ** vertical_walls = allocate_matrix_walls(LAB_LENGTH+1, LAB_WIDTH);
    int ** horizontal_walls = allocate_matrix_walls(LAB_LENGTH, LAB_WIDTH+1);

    display_matrix(labyrinth, LAB_LENGTH, LAB_WIDTH);
    printf("\n");

    display_matrix(vertical_walls, LAB_LENGTH+1, LAB_WIDTH);

    printf("\n");

    display_matrix(horizontal_walls, LAB_LENGTH, LAB_WIDTH+1);
}