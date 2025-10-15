#ifndef LABYRINTH_PLAYER_MOVEMENT_H
#define LABYRINTH_PLAYER_MOVEMENT_H

#include "utils.h"
#include <SDL2/SDL.h>


#define PLAYER_COLOR 0, 255, 0, 255
#define WALL_COLOR 0, 0, 0, 255
#define PATH_COLOR 255, 255, 255, 255
#define END_COLOR 255, 0, 0, 255
#define CHEST_COLOR 139, 69, 19, 255
#define HAS_KEY_COLOR 255, 215, 0, 255
#define KEY_COLOR 0, 0, 255, 255
#define TRAP_COLOR 255, 0, 255, 255

Score display_labyrinth_sdl(Labyrinth labyrinth, int length, int width);

#endif