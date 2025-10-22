#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "labyrinth_player_movement.h"
#include "utils.h"
#include <unistd.h>
#include "labyrinth_score.h"


int define_cell_size(int length, int width) {
    int max_dimension = length > width ? length : width;
    if (max_dimension <= 20) {
        return 30;
    } else if (max_dimension <= 35) {
        return 20;
    } else if(max_dimension > 40){
        return 8;
    }
    return 15;
}

void redraw_case(SDL_Renderer *renderer, Labyrinth *labyrinth, int x, int y) {
    int CELL_SIZE = define_cell_size(labyrinth->length, labyrinth->width);
    SDL_Rect cell = { y * CELL_SIZE, x * CELL_SIZE, CELL_SIZE, CELL_SIZE };

    if (labyrinth->grid[x][y] == WALL) {
        SDL_SetRenderDrawColor(renderer, WALL_COLOR);

    } else if (labyrinth->grid[x][y] == END) {
        SDL_SetRenderDrawColor(renderer, END_COLOR);

    } else if (labyrinth->grid[x][y] == PLAYER) {
        if (labyrinth->has_key) {
            SDL_SetRenderDrawColor(renderer, HAS_KEY_COLOR);
        } else {
            SDL_SetRenderDrawColor(renderer, PLAYER_COLOR);
        }

    } else if (labyrinth->grid[x][y] == KEY) {
        SDL_SetRenderDrawColor(renderer, KEY_COLOR);

    }else if(labyrinth->grid[x][y] == CHEST){
        SDL_SetRenderDrawColor(renderer, CHEST_COLOR);
    }
    else if(labyrinth->grid[x][y] == TRAP){
        SDL_SetRenderDrawColor(renderer, TRAP_COLOR);
    }
    else {
        SDL_SetRenderDrawColor(renderer, PATH_COLOR);
    }

    SDL_RenderFillRect(renderer, &cell);
}

int is_ended(Labyrinth *labyrinth, int nb_iterations, float elapsed_sec) {
    if (labyrinth->starting_x == labyrinth->ending_x &&
        labyrinth->starting_y == labyrinth->ending_y) {
        if (labyrinth->has_key) {
            printf("🎉 Congratulations! You've reached the end with the key!\n");
            printf("⏱️ Time taken: %.2f seconds\n", elapsed_sec);
            printf("🔄 Total moves made: %d\n", nb_iterations);
            printf("💰 Total points: %d\n", labyrinth->coins);
            return 1;
        } else {
            printf("🔒 You need the key to finish the labyrinth!\n");
            return 0;
        }
    }
    return 0;
}

void move_player(Labyrinth *labyrinth, int dx, int dy, SDL_Renderer *renderer) {
    int old_x = labyrinth->starting_x;
    int old_y = labyrinth->starting_y;

    int new_x = old_x + dx;
    int new_y = old_y + dy;

    if (new_x >= 0 && new_x < labyrinth->length * 2 + 1 &&
        new_y >= 0 && new_y < labyrinth->width * 2 + 1 &&
        labyrinth->grid[new_x][new_y] != WALL) {

        if (labyrinth->grid[new_x][new_y] == KEY) {
            labyrinth->has_key = 1;
            printf("🔑 You picked up the key!\n");
        }
        else if (labyrinth->grid[new_x][new_y] == CHEST)
        {
            labyrinth->grid[new_x][new_y] = PATH;
            printf("🎁 You opened a chest and received 1000 coins\n");
            labyrinth->coins += 1000;
        }
        else if (labyrinth->grid[new_x][new_y] == TRAP)
        {
            labyrinth->grid[new_x][new_y] = PATH;
            printf("💀 You stepped on a trap and lost 500 coins\n");
            labyrinth->coins -= 500;
        }
        
        char old_char = labyrinth->grid[old_x][old_y];
        if (old_char != END) {
            labyrinth->grid[old_x][old_y] = PATH;
            redraw_case(renderer, labyrinth, old_x, old_y);
        } else {
            redraw_case(renderer, labyrinth, old_x, old_y);
        }

        labyrinth->starting_x = new_x;
        labyrinth->starting_y = new_y;
        if (labyrinth->grid[new_x][new_y] != END) {
            labyrinth->grid[new_x][new_y] = PLAYER;
        }

        redraw_case(renderer, labyrinth, new_x, new_y);
        SDL_RenderPresent(renderer);
    } else {
        printf("❌ Move blocked! (%d,%d) -> (%d,%d)\n", old_x, old_y, new_x, new_y);
    }
}

int movement_orchestrator(SDL_Event e, Labyrinth *labyrinth, SDL_Renderer *renderer) {
    switch (e.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_z:
            move_player(labyrinth, -1, 0, renderer);
            return 1;
        case SDLK_DOWN:
        case SDLK_s:
            move_player(labyrinth, 1, 0, renderer);
            return 1;
        case SDLK_LEFT:
        case SDLK_q:
            move_player(labyrinth, 0, -1, renderer);
            return 1;
        case SDLK_RIGHT:
        case SDLK_d:
            move_player(labyrinth, 0, 1, renderer);
            return 1;
        default:
            return 0;
    }
}

void display_time_on_ui(Uint32 start_time, SDL_Renderer *renderer, TTF_Font *font) {
    Uint32 elapsed_ms = SDL_GetTicks() - start_time;
    float elapsed_sec = elapsed_ms / 1000.0f;
    char time_text[64];
        snprintf(time_text, sizeof(time_text), "Temps: %.1f s", elapsed_sec);
        SDL_Color text_color = {235, 64, 52, 255};

        SDL_Surface *text_surface = TTF_RenderText_Blended(font, time_text, text_color);
        if (text_surface) {
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (text_texture) {
                SDL_Rect text_rect = {10, 10, text_surface->w, text_surface->h};
                SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
                SDL_DestroyTexture(text_texture);
            }
            SDL_FreeSurface(text_surface);
        }
}

void display_points_on_ui(Labyrinth *labyrinth, SDL_Renderer *renderer, TTF_Font *font) {
    char points_text[64];
    snprintf(points_text, sizeof(points_text), "Coins :  %d", labyrinth->coins);
    SDL_Color text_color = {255, 215, 0, 255};

    SDL_Surface *text_surface = TTF_RenderText_Blended(font, points_text, text_color);
    if (text_surface) {
        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (text_texture) {
            SDL_Rect text_rect = {10, 40, text_surface->w, text_surface->h};
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
            SDL_DestroyTexture(text_texture);
        }
        SDL_FreeSurface(text_surface);
    }
}


Score display_labyrinth_sdl(Labyrinth labyrinth, int length, int width) {
    width = width * 2 + 1;
    length = length * 2 + 1;
    int count = 0;

    int CELL_SIZE = define_cell_size(labyrinth.length, labyrinth.width);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        perror("SDL_Init");
    }

    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        perror("SDL_Quit");
    }

    TTF_Font *font = TTF_OpenFont("asset/arial.ttf", 24); 
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_Quit();
        perror("SDL_Quit");
    }

    SDL_Window *win = SDL_CreateWindow(
        "Labyrinth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width * CELL_SIZE, length * CELL_SIZE,
        SDL_WINDOW_SHOWN
    );

    if (!win) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        perror("SDL_Quit");
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        perror("SDL_Quit");
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            redraw_case(renderer, &labyrinth, i, j);
        }
    }
    SDL_RenderPresent(renderer);

    int running = 1;
    SDL_Event e;

    Uint32 start_time = SDL_GetTicks();
    float elapsed_sec = 0.0f;

    while (running) {
        Uint32 elapsed_ms = SDL_GetTicks() - start_time;
        elapsed_sec = elapsed_ms / 1000.0f;
        display_time_on_ui(start_time, renderer, font);
        display_points_on_ui(&labyrinth, renderer, font);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || is_ended(&labyrinth, count, elapsed_sec)) {
                running = 0;
            } else if (e.type == SDL_KEYDOWN) {
                if (movement_orchestrator(e, &labyrinth, renderer)) {
                    count++;
                    labyrinth.coins -= 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                redraw_case(renderer, &labyrinth, i, j);
            }
        }

        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    Score final_score;
    final_score.coins = labyrinth.coins;
    final_score.name = malloc(100 * sizeof(char));
    end_of_game_dialog(&final_score);
    return final_score;
}

