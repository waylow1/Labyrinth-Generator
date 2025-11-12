#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief Core data structures and utilities for the labyrinth game.
 * @details Defines fundamental types (cells, walls, labyrinth, score, monsters),
 * enums, and helper functions for allocation, I/O, and persistence.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * @brief Logical cell used during generation (disjoint-set labeling).
 */
typedef struct cell{
    int x;      /**< Row index (0..length-1). */
    int y;      /**< Column index (0..width-1). */
    int value;  /**< Set identifier used for connectivity merges. */
} LabyrinthCell;

/**
 * @brief Wrapper for a 2D matrix of walls (1=wall present, 0=open).
 */
typedef struct walls{
    int ** walls; /**< Matrix of size [length][width] or [length][width+1] depending on orientation. */
} LabyrinthWalls;

/** Forward declaration for the main Labyrinth structure. */
typedef struct Labyrinth Labyrinth;

/**
 * @brief Difficulty levels for generation and gameplay tweaks.
 */
typedef enum {
    DIFF_EASY = 0, /**< Classic maze, no extra loops and no monsters. */
    DIFF_HARD = 1  /**< Extra loops and monsters enabled. */
} Difficulty;

/**
 * @brief Monster kinds available in the game.
 */
typedef enum {
    MONSTER_GHOST = 'G', /**< Ghost: can ignore some walls when moving. */
    MONSTER_OGRE  = 'O'  /**< Ogre: heavy, slower movement, different AI. */
} MonsterType;

/** Forward declaration for Monster structure. */
struct Monster;

/** Function pointer for per-monster movement behavior. */
typedef void (*MonsterMoveFn)(struct Monster *m, struct Labyrinth *lab);

/**
 * @brief Runtime monster entity embedded in a labyrinth.
 */
typedef struct Monster {
    int x, y;                /**< Current grid coordinates (scaled grid). */
    int penalty_points;      /**< Coins lost when colliding with the player. */
    int mobility_range;      /**< Max steps a monster may attempt per turn. */
    MonsterType type;        /**< Monster kind. */
    char under_char;         /**< Tile character stored under the monster (to restore). */
    int alive;               /**< Non-zero if active; zero if removed. */
    MonsterMoveFn move;      /**< Behavior callback used to move this monster. */
} Monster;

/**
 * @brief Optional gameplay extras carried alongside a labyrinth.
 */
typedef struct LabyrinthExtra {
    Difficulty difficulty;  /**< Selected difficulty for this maze. */
    Monster *monsters;      /**< Dynamic array of monsters (may be NULL). */
    int monster_count;      /**< Number of monsters in the array. */
} LabyrinthExtra;

/**
 * @brief Indirection used to keep extras optional/allocatable.
 */
typedef struct LabyrinthInternalExtras {
    LabyrinthExtra extra;   /**< Actual extras payload. */
} LabyrinthInternalExtras;

/**
 * @brief Full labyrinth grid and runtime state.
 * @details The grid uses a scaled representation of size (2*length+1) x (2*width+1)
 * where walls are placed at even coordinates and paths/objects at odd coordinates.
 */
struct Labyrinth {
    char ** grid;                      /**< 2D grid of characters. */
    int starting_x, starting_y;        /**< Player position in grid coordinates. */
    int ending_x, ending_y;            /**< Exit position in grid coordinates. */
    int length, width;                 /**< Logical size (number of cells). */
    int has_key;                       /**< 1 if player currently holds the key. */
    int coins;                         /**< Player's current coin total. */
    LabyrinthInternalExtras *extras;   /**< Optional extras (difficulty, monsters). */
};

/**
 * @brief Player score entry for the leaderboard.
 */
typedef struct score{
    char name[100];  /**< Player name (null-terminated). */
    int coins;       /**< Coin total achieved. */
} Score;

/**
 * @brief Ladder containing multiple score entries.
 */
typedef struct ladder{
    Score * scores;  /**< Dynamic array of scores (may be NULL). */
    int count;       /**< Number of entries in the array. */
} Ladder;

/**
 * @brief Character codes used in the visual grid representation.
 */
enum BOX_TYPE {WALL = '#', PATH = ' ', PLAYER = 'o', END = '-', KEY = 'k', CHEST = 'c', TRAP = 'x', DOOR = 'd'};

/**
 * @brief Allocates memory for a 2D array of LabyrinthCell structures.
 * 
 * @param length The number of rows in the labyrinth.
 * @param width The number of columns in the labyrinth.
 * @return LabyrinthCell** A pointer to the allocated 2D array of LabyrinthCell structures.
 */
LabyrinthCell ** allocate_labyrinth(int length, int width);

/**
 * @brief Allocates memory for a 2D matrix of integers, initializing all elements to 1.
 * 
 * @param lines The number of rows in the matrix.
 * @param columns The number of columns in the matrix.
 * @return int** A pointer to the allocated 2D matrix of integers.
 */
int ** allocate_matrix_walls(int lines, int columns);

/**
 * @brief Frees the memory allocated for a 2D matrix of integers.
 * 
 * @param matrix The matrix to be freed.
 * @param length The number of rows in the matrix.
 */
void free_matrix(int ** matrix, int length);

/**
 * @brief Frees the memory allocated for a 2D array of LabyrinthCell structures.
 * 
 * @param labyrinth The labyrinth to be freed.
 * @param length The number of rows in the labyrinth.
 */
void free_labyrinth_cells(LabyrinthCell ** labyrinth, int length);

/**
 * @brief Frees the memory allocated for a Labyrinth structure, including its grid.
 * 
 * @param labyrinth The Labyrinth structure to be freed.
 * @param lines The number of rows in the labyrinth grid.
 * @param columns The number of columns in the labyrinth grid.
 */
void free_labyrinth(Labyrinth labyrinth, int lines, int columns);

/**
 * @brief Dumps the labyrinth configuration (seed, lines, columns) to a file.
 * 
 * @param seed The seed used for generating the labyrinth.
 * @param lines The number of rows in the labyrinth.
 * @param columns The number of columns in the labyrinth.
 * @param filename The name of the file to save the configuration (without extension).
 */
void dump_labyrinth(int seed, int lines, int columns, char * filename);

/**
 * @brief Extended dump: also persists difficulty as a 4th field.
 * @param seed RNG seed used to generate the labyrinth.
 * @param lines Logical number of rows.
 * @param columns Logical number of columns.
 * @param diff Difficulty to persist alongside the config.
 * @param filename Basename (without extension) for the output file.
 */
void dump_labyrinth_ext(int seed, int lines, int columns, Difficulty diff, char *filename);

/**
 * @brief Displays all available labyrinth configuration files and prompts the user to select one.
 * 
 * @param labyrinth_name A pointer to a string where the selected labyrinth name will be stored.
 */
void display_all_available_files(char ** labyrinth_name);

/**
 * @brief Loads the labyrinth configuration (seed, lines, columns) from a file.
 * 
 * @param filename The name of the file to load the configuration from (without extension).
 * @param seed A pointer to store the loaded seed value.
 * @param lines A pointer to store the loaded number of rows.
 * @param columns A pointer to store the loaded number of columns.
 */
void load_labyrinth(const char * filename, int * seed, int * lines, int * columns);

/**
 * @brief Extended load: reads difficulty if present (defaults to DIFF_EASY).
 * @param filename Basename (without extension) of the config to load.
 * @param seed Output seed.
 * @param lines Output logical rows.
 * @param columns Output logical cols.
 * @param diff Output difficulty (DIFF_EASY if not present in file).
 */
void load_labyrinth_ext(const char *filename, int *seed, int *lines, int *columns, Difficulty *diff);


#endif