#ifndef UTILS_H
#define UTILS_H

typedef struct cell{
    int x, y, value;
} LabyrinthCell;

typedef struct walls{
    int ** walls;
} LabyrinthWalls;

typedef struct Labyrinth{
    int starting_point_x, starting_point_y;
    int ending_point_x, ending_point_y;
    int length, width;
    char ** grid;
} Labyrinth;


int ** allocate_matrix_walls(int lines, int columns);
LabyrinthCell ** allocate_labyrinth(int length, int width);
void free_matrix(int ** matrix, int n);
void free_labyrinth_cells(LabyrinthCell ** labyrinth, int lines);
void free_labyrinth(Labyrinth labyrinth, int lines, int columns);
void dump_labyrinth(Labyrinth labyrinth, int lines, int columns);

#endif