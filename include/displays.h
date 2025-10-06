#ifndef DISPLAYS_H
#define DISPLAYS_H

#include "utils.h"

void display_labyrinth(Labyrinth labyrinth, int lines, int columns);
void display_labyrinth_numerically(LabyrinthCell ** labyrinth, int lines, int columns);
void display_matrix(int ** matrix, int lines, int columns);

#endif