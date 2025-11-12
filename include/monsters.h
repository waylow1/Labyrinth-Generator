#ifndef MONSTERS_H
#define MONSTERS_H

/**
 * @file monsters.h
 * @brief Monster API: initialization, movement, and collisions.
 * @details Declares functions to spawn monsters, move them using per-type
 * function pointers, and resolve interactions with the player.
 */

#include "utils.h"

#define GHOST_CHAR ((char)MONSTER_GHOST)
#define OGRE_CHAR  ((char)MONSTER_OGRE)
#define GHOST_COLOR 0, 200, 200, 255
#define OGRE_COLOR  200, 100, 0, 255

/**
 * @brief Initialize monsters for a given labyrinth and difficulty.
 * @param lab Labyrinth to populate with monsters.
 * @param diff Difficulty level driving number/types of monsters.
 */
void init_monsters(Labyrinth *lab, Difficulty diff);

/**
 * @brief Move all alive monsters one step according to their behavior.
 * @param lab Labyrinth containing the monsters and grid.
 */
void move_monsters(Labyrinth *lab);

/**
 * @brief Handle collisions between player and monsters (apply penalties, remove monsters).
 * @param lab Labyrinth containing player state and monsters.
 */
void handle_player_monster_collisions(Labyrinth *lab);

/**
 * @brief Utility to check whether a character corresponds to a monster tile.
 * @param c The grid character to test.
 * @return 1 if the character denotes a monster, 0 otherwise.
 */
int is_monster_char(char c);

#endif // MONSTERS_H
