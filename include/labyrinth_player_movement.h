#ifndef LABYRINTH_PLAYER_MOVEMENT_H
#define LABYRINTH_PLAYER_MOVEMENT_H

#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// --------------------------------
// SDL Rendering Colors
// --------------------------------
#define PLAYER_COLOR 0, 255, 0, 255
#define WALL_COLOR 0, 0, 0, 255
#define PATH_COLOR 255, 255, 255, 255
#define END_COLOR 255, 0, 0, 255
#define CHEST_COLOR 139, 69, 19, 255
#define HAS_KEY_COLOR 255, 215, 0, 255
#define KEY_COLOR 0, 0, 255, 255
#define TRAP_COLOR 255, 0, 255, 255
#define DOOR_COLOR 160, 82, 45, 255
#define GHOST_SDL_COLOR 0, 200, 200, 255
#define OGRE_SDL_COLOR  200, 100, 0, 255

// --------------------------------
// SDL and Player Movement Functions
// --------------------------------

/**
 * @brief Determines the cell size based on the labyrinth dimensions.
 * @param length Height of the labyrinth.
 * @param width Width of the labyrinth.
 * @return Cell size in pixels.
 */
int define_cell_size(int length, int width);

/**
 * @brief Redraws a specific cell of the labyrinth in the SDL window.
 * @param renderer SDL renderer used to draw.
 * @param labyrinth Pointer to the labyrinth structure.
 * @param x X-coordinate (row) of the cell.
 * @param y Y-coordinate (column) of the cell.
 */
void redraw_case(SDL_Renderer *renderer, Labyrinth *labyrinth, int x, int y);

/**
 * @brief Attempts to unlock the door in front of the exit if the player has the key.
 * @param labyrinth Pointer to the labyrinth structure.
 * @param renderer SDL renderer to update the display.
 */
void try_unlock_door(Labyrinth *labyrinth, SDL_Renderer *renderer);

/**
 * @brief Checks whether the player has reached the end of the labyrinth.
 * @param labyrinth Pointer to the labyrinth structure.
 * @param nb_iterations Number of moves made.
 * @param elapsed_sec Time elapsed since the start of the game.
 * @return 1 if the game is finished, 0 otherwise.
 */
int is_ended(Labyrinth *labyrinth, int nb_iterations, float elapsed_sec);

/**
 * @brief Moves the player in the labyrinth according to the given direction.
 * @param labyrinth Pointer to the labyrinth structure.
 * @param dx Horizontal displacement (-1, 0, 1).
 * @param dy Vertical displacement (-1, 0, 1).
 * @param renderer SDL renderer to update the display.
 *
 * @note If the player moves onto a key (KEY), they acquire it.
 * @note If the player moves onto a chest (CHEST), 1000 coins are added.
 * @note If the player moves onto a trap (TRAP), 500 coins are subtracted.
 * @note Movement blocked by a wall (WALL) or door (DOOR) is ignored.
 */
void move_player(Labyrinth *labyrinth, int dx, int dy, SDL_Renderer *renderer);

/**
 * @brief Handles keyboard input to orchestrate player movement or actions.
 * @param e SDL event corresponding to a key press.
 * @param labyrinth Pointer to the labyrinth structure.
 * @param renderer SDL renderer to update the display.
 * @return 1 if a movement occurred, 0 otherwise.
 */
int movement_orchestrator(SDL_Event e, Labyrinth *labyrinth, SDL_Renderer *renderer);

/**
 * @brief Displays the elapsed time on the SDL interface.
 * @param start_time Start time of the game (SDL_GetTicks).
 * @param renderer SDL renderer used to draw the text.
 * @param font TTF font used for rendering text.
 */
void display_time_on_ui(Uint32 start_time, SDL_Renderer *renderer, TTF_Font *font);

/**
 * @brief Displays the player's coin count on the SDL interface.
 * @param labyrinth Pointer to the labyrinth structure.
 * @param renderer SDL renderer used to draw the text.
 * @param font TTF font used for rendering text.
 */
void display_points_on_ui(Labyrinth *labyrinth, SDL_Renderer *renderer, TTF_Font *font);

/**
 * @brief Launches the SDL display of the labyrinth and handles interactive gameplay.
 * @param labyrinth Labyrinth to display and interact with.
 * @param length Height of the labyrinth.
 * @param width Width of the labyrinth.
 * @return Final score of the player.
 */
Score display_labyrinth_sdl(Labyrinth labyrinth, int length, int width);

#endif // LABYRINTH_PLAYER_MOVEMENT_H
