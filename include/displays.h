#ifndef DISPLAYS_H
#define DISPLAYS_H

/**
 * @file displays.h
 * @brief Text-mode and numeric display helpers for labyrinth structures.
 * @details Provides functions to print the labyrinth as ASCII art or as raw
 * integer matrices for debugging and visualization in the terminal.
 */

#include "utils.h"

/**
 * @brief Displays the labyrinth in a human-readable format using ASCII characters.
 *
 * Walls are represented by solid blocks, while other cells display their character.
 *
 * @param labyrinth The Labyrinth structure containing the grid.
 * @param lines Number of logical rows of the labyrinth (before scaling by 2+1).
 * @param columns Number of logical columns of the labyrinth (before scaling by 2+1).
 */
void display_labyrinth(Labyrinth labyrinth, int lines, int columns);

/**
 * @brief Displays the labyrinth numerically.
 *
 * Each cell of the labyrinth is printed as its integer value from the LabyrinthCell structure.
 *
 * @param labyrinth Pointer to a 2D array of LabyrinthCell.
 * @param lines Number of rows in the array.
 * @param columns Number of columns in the array.
 */
void display_labyrinth_numerically(LabyrinthCell **labyrinth, int lines, int columns);

/**
 * @brief Displays a simple 2D integer matrix.
 *
 * Each element is printed with a fixed width for proper alignment.
 *
 * @param matrix Pointer to a 2D array of integers.
 * @param lines Number of rows in the matrix.
 * @param columns Number of columns in the matrix.
 */
void display_matrix(int **matrix, int lines, int columns);

#endif // DISPLAYS_H
