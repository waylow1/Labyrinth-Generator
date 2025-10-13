#include <stdio.h>
#include <stdlib.h>
#include "labyrinth_player_movement.h"
#include <SDL2/SDL.h>
#include "utils.h"
#define CELL_SIZE 20

void redraw_case(SDL_Renderer *renderer, Labyrinth labyrinth, int x, int y) {
    SDL_Rect cell = { y * CELL_SIZE, x * CELL_SIZE, CELL_SIZE, CELL_SIZE };

    if (labyrinth.grid[x][y] == '#') {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    } else if (labyrinth.grid[x][y] == '-') {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    } else if (labyrinth.grid[x][y] == 'o') {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    }

    SDL_RenderFillRect(renderer, &cell);
}

int is_ended(Labyrinth * labyrinth){
    if(labyrinth->starting_x == labyrinth->ending_x && labyrinth->starting_y == labyrinth->ending_y){
        return 1;
    }   
    return 0;-
}


void move_player(Labyrinth *labyrinth, int dx, int dy, SDL_Renderer *renderer) {
    int old_x = labyrinth->starting_x;
    int old_y = labyrinth->starting_y;

    int new_x = old_x + dx; 
    int new_y = old_y + dy;

    int mid_x = old_x + dx; 
    int mid_y = old_y + dy;


    if (new_x >= 0 && new_x < labyrinth->length*2+1 &&
        new_y >= 0 && new_y < labyrinth->width*2+1 &&
        labyrinth->grid[mid_x][mid_y] != '#' && labyrinth->grid[new_x][new_y] != '#') {

        labyrinth->grid[old_x][old_y] = ' ';
        redraw_case(renderer, *labyrinth, old_x, old_y);

        labyrinth->starting_x = new_x;
        labyrinth->starting_y = new_y;
        labyrinth->grid[new_x][new_y] = 'o';

        redraw_case(renderer, *labyrinth, new_x, new_y);

        SDL_RenderPresent(renderer);
       
    } else {
        printf("❌ Move blocked! (%d,%d) -> (%d,%d)\n", old_x, old_y, new_x, new_y);
    }

    if(is_ended(labyrinth)){
        printf("🎉 Congratulations! You've reached the end of the labyrinth! 🎉\n");
        exit(0);
    }
}

void display_labyrinth_sdl(Labyrinth labyrinth, int length, int width) {

    width = width * 2 + 1;
    length = length * 2 + 1;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Window *win = SDL_CreateWindow("Labyrinth", 100, 100, width * CELL_SIZE, length * CELL_SIZE, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            redraw_case(renderer, labyrinth, i, j);
        }
    }
    SDL_RenderPresent(renderer);

    int running = 1;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } 
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_z:
                        move_player(&labyrinth, -1, 0, renderer);
                        break;
                    case SDLK_DOWN:
                    case SDLK_s:
                        move_player(&labyrinth, 1, 0, renderer);
                        break;
                    case SDLK_LEFT:
                    case SDLK_q:
                        move_player(&labyrinth, 0, -1, renderer);
                        break;
                    case SDLK_RIGHT:
                    case SDLK_d:
                        move_player(&labyrinth, 0, 1, renderer);
                        break;
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
