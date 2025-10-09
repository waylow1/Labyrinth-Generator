#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include <time.h>

int choose_wall(int length, int width, int x, int y, int *nx, int *ny) {
    int dir = rand() % 4;
    *nx = x;
    *ny = y;

    if (dir == 0 && x + 1 < length) {        
        *nx = x + 1;
    } else if (dir == 1 && y + 1 < width) {  
        *ny = y + 1;
    } else if (dir == 2 && x - 1 >= 0) {     
        *nx = x - 1;
    } else if (dir == 3 && y - 1 >= 0) {     
        *ny = y - 1;
    } else {
        return -1; 
    }

    return dir;
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

void open_wall(int dir, int x, int y, LabyrinthWalls vertical_walls, LabyrinthWalls horizontal_walls) {
    switch (dir) {
        case 0:
            vertical_walls.walls[x+1][y] = 0;
            break;
        case 1:
            horizontal_walls.walls[x][y+1] = 0;
            break;
        case 2:
            vertical_walls.walls[x][y] = 0;
            break;
        case 3:
            horizontal_walls.walls[x][y] = 0;
            break;
    }
}

void get_opened_walls(LabyrinthCell **labyrinth, LabyrinthWalls vertical_walls, LabyrinthWalls horizontal_walls, int length, int width) {
    int nb_iterations = 0;
    int total_walls_needed = length * width - 1;

    while (nb_iterations < total_walls_needed) {
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
            nb_iterations++;
        }
    }
}


void generate_starting_ending(Labyrinth labyrinth, int length, int width) {
    
    do{ 
        labyrinth.starting_y = rand() % (2*length);
    }while(labyrinth.starting_y % 2 == 0);
    labyrinth.starting_x = 0;

    do{
        labyrinth.ending_y = rand() % (2*length);
    }while(labyrinth.ending_y % 2 == 0);
    labyrinth.ending_x = 2 * width;

    labyrinth.grid[labyrinth.starting_x][labyrinth.starting_y] = 'o';
    labyrinth.grid[labyrinth.ending_x][labyrinth.ending_y] = '-';

}

Labyrinth concat_vertical_horizontal_walls(LabyrinthWalls vertical_walls, LabyrinthWalls horizontal_walls, int length, int width) {
    Labyrinth labyrinth;

    int grid_rows = 2 * length + 1;
    int grid_cols = 2 * width + 1;

    char **grid = malloc(sizeof(char*) * grid_rows);
    if (!grid) {
        fprintf(stderr, "Erreur d'allocation mémoire pour grid\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < grid_rows; i++) {
        grid[i] = malloc(sizeof(char) * (grid_cols + 1));
        if (!grid[i]) {
            fprintf(stderr, "Erreur d'allocation mémoire pour grid[%d]\n", i);
            for (int k = 0; k < i; k++) {
                free(grid[k]);
            }
            free(grid);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < grid_cols; j++) {
            grid[i][j] = '#';
        }
        grid[i][grid_cols] = '\0';
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            int gi = 2 * i + 1;
            int gj = 2 * j + 1;
            grid[gi][gj] = ' ';
            if (i + 1 < length && vertical_walls.walls[i+1][j] == 0) {
                grid[gi + 1][gj] = ' ';
            }

            if (j + 1 < width && horizontal_walls.walls[i][j+1] == 0) {
                grid[gi][gj + 1] = ' ';
            }
        }
    }

    labyrinth.grid = grid;

    generate_starting_ending(labyrinth, length, width);

    return labyrinth;
}



Labyrinth generate_labyrinth(int length, int width){

    LabyrinthCell ** labyrinth = allocate_labyrinth(length, width);

    LabyrinthWalls vertical_walls, horizontal_walls;
    vertical_walls.walls = allocate_matrix_walls(length+1, width);
    horizontal_walls.walls = allocate_matrix_walls(length, width+1);

    get_opened_walls(labyrinth, vertical_walls, horizontal_walls, length, width);

    Labyrinth generated_labyrinth = concat_vertical_horizontal_walls(vertical_walls, horizontal_walls, length, width);

    free_labyrinth_cells(labyrinth, length);
    free_matrix(vertical_walls.walls, length+1);
    free_matrix(horizontal_walls.walls, length);
    return generated_labyrinth;
}
