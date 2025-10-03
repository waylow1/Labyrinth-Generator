#ifndef LABYRINTH_GENERATOR_H
#define LABYRINTH_GENERATOR_H

#include "utils.h"

#define LAB_LENGTH 11
#define LAB_WIDTH 25


LabyrinthCell ** allocate_labyrinth(int length, int width);
int ** allocate_matrix_walls(int lines, int columns);
int choose_wall(int length, int width, int x, int y, int *nx, int *ny);
void merge_sets(LabyrinthCell **labyrinth, int length, int width, int old_val, int new_val);
void open_wall(int orientation, int x, int y, int **vertical_walls, int **horizontal_walls);
void get_opened_walls(LabyrinthCell **labyrinth, int **vertical_walls, int **horizontal_walls, int length, int width);
void generate_labyrinth(LabyrinthCell **labyrinth, int length, int width);

#endif 