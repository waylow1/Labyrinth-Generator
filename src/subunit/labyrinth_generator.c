#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include <time.h>


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
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

int choose_wall(int length, int width, int x, int y, int *nx, int *ny) {
    int orientation = rand() % 2;
    *nx = x;
    *ny = y;

    if (orientation == 0 && x+1 < length) {
        *nx = x+1;
    } else if (orientation == 1 && y+1 < width) {
        *ny = y+1;
    } else {
        return -1;
    }
    return orientation;
}

void merge_sets(LabyrinthCell **labyrinth, int length, int width, int old_val, int new_val) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (labyrinth[i][j].value == old_val) {
                labyrinth[i][j].value = new_val;
            }
        }
    }
}

void open_wall(int orientation, int x, int y, int **vertical_walls, int **horizontal_walls) {
    if (orientation == 0) {
        vertical_walls[x+1][y] = 1; 
    } else {
        horizontal_walls[x][y+1] = 1;
    }
}

void get_opened_walls(LabyrinthCell **labyrinth, int **vertical_walls, int **horizontal_walls, int length, int width) {
    int walls_opened = 0;
    int total_walls_needed = length * width - 1;

    while (walls_opened < total_walls_needed) {
        int x = rand() % length;
        int y = rand() % width;
        int nx, ny;

        int orientation = choose_wall(length, width, x, y, &nx, &ny);
        if (orientation == -1) continue; 

        if (labyrinth[x][y].value != labyrinth[nx][ny].value) {
            int old_val = labyrinth[nx][ny].value;
            int new_val = labyrinth[x][y].value;

            merge_sets(labyrinth, length, width, old_val, new_val);
            open_wall(orientation, x, y, vertical_walls, horizontal_walls);
            walls_opened++;
        }
    }
}

void generate_labyrinth(LabyrinthCell **labyrinth, int length, int width){

    int ** vertical_walls = allocate_matrix_walls(length+1, width);
    int ** horizontal_walls = allocate_matrix_walls(length, width+1);

    get_opened_walls(labyrinth, vertical_walls, horizontal_walls, length, width);
    for(int i=0;i<length;i++){
        for(int j=0;j<width+1;j++){
            if(vertical_walls[i][j] == 1 || horizontal_walls[i][j] == 1){
                labyrinth[i][j].value = 1;
            }
            else{
                labyrinth[i][j].value = 0;
            }
        }
    }
}

