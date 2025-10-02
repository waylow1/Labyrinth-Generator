#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#define LAB_LENGTH 11
#define LAB_WIDTH 25


LabyrinthCell ** allocate_labyrinth(){
    LabyrinthCell ** labyrinth = malloc(sizeof(LabyrinthCell*)*LAB_LENGTH);
    int value=0;
    for(int i=0;i<LAB_LENGTH;i++){
        labyrinth[i]=malloc(sizeof(LabyrinthCell)*LAB_WIDTH);
        for(int j=0;j<LAB_WIDTH;j++){
            labyrinth[i][j].x=i;
            labyrinth[i][j].y=j;
            labyrinth[i][j].value=value++;
        }
    }
    return labyrinth;
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


void generate_lab(LabyrinthCell ** labyrinth, int ** vertical_walls, int  ** horizontal_walls, int length, int width){
    int count=0;
    while(count < (length*width)+1){
        int rand_x = rand()%length;
        int rand_y = rand()%width;
        
        


        count++;
    }

}

int main(){

    LabyrinthCell ** labyrinth = allocate_labyrinth();

    int ** vertical_walls = allocate_matrix_walls(LAB_LENGTH+1, LAB_WIDTH);
    int ** horizontal_walls = allocate_matrix_walls(LAB_LENGTH, LAB_WIDTH+1);


    display_matrix(vertical_walls, LAB_LENGTH+1, LAB_WIDTH);

    printf("\n");

    display_matrix(horizontal_walls, LAB_LENGTH, LAB_WIDTH+1);

     printf("\n");

    display_labyrinth(labyrinth, LAB_LENGTH, LAB_WIDTH);
}