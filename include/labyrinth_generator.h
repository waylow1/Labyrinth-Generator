#ifndef LABYRINTH_GENERATOR_H
#define LABYRINTH_GENERATOR_H

#include "utils.h"

/**
 * @brief Generates a complete labyrinth with walls, paths, player, exit, key, chests, and traps.
 *
 * This function uses randomized Prim/Kruskal-like logic to open walls between cells, 
 * then places objects in the labyrinth grid.
 *
 * @param length Logical height of the labyrinth (number of rows of cells, before expansion).
 * @param width Logical width of the labyrinth (number of columns of cells, before expansion).
 * @return Labyrinth structure containing the full generated labyrinth grid.
 */
Labyrinth generate_labyrinth(int length, int width);

/**
 * @brief Randomly chooses a wall adjacent to a given cell.
 *
 * @param length Number of rows of cells.
 * @param width Number of columns of cells.
 * @param x Current cell row index.
 * @param y Current cell column index.
 * @param nx Pointer to store the neighboring cell row index.
 * @param ny Pointer to store the neighboring cell column index.
 * @return Direction of chosen wall (0=down, 1=right, 2=up, 3=left) or -1 if invalid.
 */
int choose_wall(int length, int width, int x, int y, int *nx, int *ny);

/**
 * @brief Merges two sets of cells by replacing all occurrences of old_val with new_val.
 *
 * Used to maintain connectivity when removing walls between cells.
 *
 * @param labyrinth Pointer to the 2D LabyrinthCell array.
 * @param length Number of rows.
 * @param width Number of columns.
 * @param old_val Value to replace.
 * @param new_val New value to assign.
 */
void merge_sets(LabyrinthCell **labyrinth, int length, int width, int old_val, int new_val);

/**
 * @brief Opens a wall in the labyrinth based on the direction.
 *
 * @param dir Direction of the wall (0=down, 1=right, 2=up, 3=left).
 * @param x Cell row index.
 * @param y Cell column index.
 * @param vertical_walls Vertical walls structure.
 * @param horizontal_walls Horizontal walls structure.
 */
void open_wall(int dir, int x, int y, LabyrinthWalls vertical_walls, LabyrinthWalls horizontal_walls);

/**
 * @brief Opens walls randomly to generate the maze connectivity.
 *
 * Uses a randomized approach to ensure all cells are reachable.
 *
 * @param labyrinth 2D LabyrinthCell array.
 * @param vertical_walls Vertical walls structure.
 * @param horizontal_walls Horizontal walls structure.
 * @param length Number of rows of cells.
 * @param width Number of columns of cells.
 */
void get_opened_walls(LabyrinthCell **labyrinth, LabyrinthWalls vertical_walls, LabyrinthWalls horizontal_walls, int length, int width);

/**
 * @brief Generates a key in a random odd position within the labyrinth.
 * @param labyrinth Pointer to the Labyrinth structure.
 * @param length Logical height of the labyrinth.
 * @param width Logical width of the labyrinth.
 */
void generate_key(Labyrinth *labyrinth, int length, int width);

/**
 * @brief Generates random chests in the labyrinth grid.
 *
 * @param labyrinth Pointer to the Labyrinth structure.
 * @param length Logical height of the labyrinth.
 * @param width Logical width of the labyrinth.
 * @return Number of chests placed.
 */
int generate_chests(Labyrinth *labyrinth, int length, int width);

/**
 * @brief Generates traps in the labyrinth grid, usually half the number of chests.
 *
 * @param labyrinth Pointer to the Labyrinth structure.
 * @param length Logical height of the labyrinth.
 * @param width Logical width of the labyrinth.
 * @param nb_chests Number of chests placed (used to compute trap count).
 */
void generate_traps(Labyrinth *labyrinth, int length, int width, int nb_chests);

/**
 * @brief Places the player, exit, key, chests, and traps in the labyrinth grid.
 *
 * @param labyrinth Pointer to the Labyrinth structure.
 * @param length Logical height of the labyrinth.
 * @param width Logical width of the labyrinth.
 */
void generate_objects(Labyrinth *labyrinth, int length, int width);

/**
 * @brief Converts the vertical and horizontal wall matrices into a full labyrinth grid.
 *
 * Also calls generate_objects to place player, exit, key, chests, and traps.
 *
 * @param vertical_walls Vertical walls structure.
 * @param horizontal_walls Horizontal walls structure.
 * @param length Number of rows of cells.
 * @param width Number of columns of cells.
 * @return Labyrinth structure with the completed grid.
 */
Labyrinth concat_vertical_horizontal_walls(LabyrinthWalls vertical_walls, LabyrinthWalls horizontal_walls, int length, int width);

#endif // LABYRINTH_GENERATOR_H
