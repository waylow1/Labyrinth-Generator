#ifndef UTILS_H
#define UTILS_H

typedef struct cell{
    int x, y, value;
} LabyrinthCell;

typedef struct walls{
    int ** walls;
} LabyrinthWalls;

typedef struct Labyrinth{

    char ** grid;

    int starting_x, starting_y;
    int ending_x, ending_y;
    
    int key_x, key_y;
    int length, width;
    int has_key;
    
} Labyrinth;

enum BOX_TYPE {WALL = '#', PATH = ' ', PLAYER = 'o', END = '-', KEY = 'k'};

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

#endif