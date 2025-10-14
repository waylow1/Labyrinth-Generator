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


void generate_objects(Labyrinth * labyrinth, int length, int width) {
        int grid_rows = 2 * length + 1;
        int grid_cols = 2 * width + 1;

        do { 
            labyrinth->starting_y = rand() % grid_cols;
        } while (labyrinth->starting_y % 2 == 0);
        labyrinth->starting_x = 1;

        do {
            labyrinth->ending_y = rand() % grid_cols;
        } while (labyrinth->ending_y % 2 == 0);
        labyrinth->ending_x = grid_rows - 2;

        do {
            labyrinth->key_x = rand() % grid_rows;
        } while (labyrinth->key_x % 2 == 0);
        do {
            labyrinth->key_y = rand() % grid_cols;
        } while (labyrinth->key_y % 2 == 0);

        int nb_chests = rand() %  5 + 3;
        for (int i = 0; i < nb_chests; i++) {
            int chest_x, chest_y;
            do {
                chest_x = rand() % grid_rows;
            } while (chest_x % 2 == 0 || (chest_x == labyrinth->starting_x && chest_x == labyrinth->starting_y) || (chest_x == labyrinth->ending_x && chest_x == labyrinth->ending_y) || (chest_x == labyrinth->key_x && chest_x == labyrinth->key_y));
            do {
                chest_y = rand() % grid_cols;
            } while (chest_y % 2 == 0 || (chest_y == labyrinth->starting_x && chest_y == labyrinth->starting_y) || (chest_y == labyrinth->ending_x && chest_y == labyrinth->ending_y) || (chest_y == labyrinth->key_x && chest_y == labyrinth->key_y));
            labyrinth->grid[chest_x][chest_y] = CHEST; 
        }

        labyrinth->grid[labyrinth->starting_x][labyrinth->starting_y] = PLAYER;
        labyrinth->grid[labyrinth->ending_x][labyrinth->ending_y] = END;
        labyrinth->grid[labyrinth->key_x][labyrinth->key_y] = KEY;
        labyrinth->has_key = 0;
    }

Labyrinth concat_vertical_horizontal_walls(LabyrinthWalls vertical_walls, LabyrinthWalls horizontal_walls, int length, int width) {
    Labyrinth labyrinth;

    int grid_rows = 2 * length + 1;
    int grid_cols = 2 * width + 1;

    labyrinth.grid = malloc(sizeof(char*) * grid_rows);
    for (int i = 0; i < grid_rows; i++) {
        labyrinth.grid[i] = malloc(sizeof(char) * (grid_cols + 1)); 
        for (int j = 0; j < grid_cols; j++) {
            labyrinth.grid[i][j] = WALL;
        }
        labyrinth.grid[i][grid_cols] = '\0'; 
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            int gi = 2 * i + 1;
            int gj = 2 * j + 1; 
            labyrinth.grid[gi][gj] = PATH;

            if (i + 1 < length && vertical_walls.walls[i+1][j] == 0) {
                labyrinth.grid[gi + 1][gj] = PATH;
            }

            if (j + 1 < width && horizontal_walls.walls[i][j+1] == 0) {
                labyrinth.grid[gi][gj + 1] = PATH;
            }
        }
    }

    generate_objects(&labyrinth, length, width);

    return labyrinth;
}


Labyrinth generate_labyrinth(int length, int width){

    LabyrinthCell ** labyrinth = allocate_labyrinth(length, width);

    LabyrinthWalls vertical_walls, horizontal_walls;
    vertical_walls.walls = allocate_matrix_walls(length+1, width);
    horizontal_walls.walls = allocate_matrix_walls(length, width+1);

    get_opened_walls(labyrinth, vertical_walls, horizontal_walls, length, width);

    Labyrinth generated_labyrinth = concat_vertical_horizontal_walls(vertical_walls, horizontal_walls, length, width);

    generated_labyrinth.length = length;
    generated_labyrinth.width = width;

    free_labyrinth_cells(labyrinth, length);
    free_matrix(vertical_walls.walls, length+1);
    free_matrix(horizontal_walls.walls, length);
    return generated_labyrinth;
}
