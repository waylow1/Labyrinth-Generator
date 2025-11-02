#ifndef LABYRINTH_MENU_H
#define LABYRINTH_MENU_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Displays the main menu for the Labyrinth Generator.
 *
 * Options:
 * 1. Generate a new labyrinth
 * 2. Load a labyrinth from file
 * 3. Play the labyrinth
 * 4. Exit
 */
void display_menu(void);

/**
 * @brief Asks the user for the labyrinth size and its name.
 *
 * Ensures that width and height are odd numbers between 5 and 51.
 *
 * @param length Pointer to an integer where the labyrinth height will be stored.
 * @param width Pointer to an integer where the labyrinth width will be stored.
 * @param name Pointer to a char pointer where the labyrinth name will be stored.
 *
 * @note The function allocates memory for `name` using malloc.
 *       The caller is responsible for freeing this memory after use.
 */
void ask_for_labyrinth_size_and_name(int *length, int *width, char **name);

/**
 * @brief Prompts the user to enter a menu choice and validates the input.
 *
 * @return Integer representing the user's choice (1 to 4).
 */
int get_user_choice(void);

#endif // LABYRINTH_MENU_H
