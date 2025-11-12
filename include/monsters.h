#ifndef MONSTERS_H
#define MONSTERS_H

#include "utils.h"

#define GHOST_CHAR ((char)MONSTER_GHOST)
#define OGRE_CHAR  ((char)MONSTER_OGRE)
#define GHOST_COLOR 0, 200, 200, 255
#define OGRE_COLOR  200, 100, 0, 255


void init_monsters(Labyrinth *lab, Difficulty diff);
void move_monsters(Labyrinth *lab);
void handle_player_monster_collisions(Labyrinth *lab);

int is_monster_char(char c);

#endif // MONSTERS_H
