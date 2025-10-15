#include "labyrinth_generator.h"
#include "labyrinth_menu.h"
#include "labyrinth_player_movement.h"
#include <time.h>
#include "utils.h"
#include "displays.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
 
    while (1) {
        display_menu();
        Score final_score;
        int choice = get_user_choice();
        int length = 0, width = 0;
        int seed = 0;
        char *labyrinth_name = NULL;
        Labyrinth labyrinth = {NULL, 0, 0, 0, 0, 0, 0, 0, 0};

        length = 15;
        width = 15;
        seed = (int)time(NULL);
        srand(seed);
        labyrinth = generate_labyrinth(length, width);
        switch (choice) {
            case 1:
                seed = (int)time(NULL);
                srand(seed);
                printf("Generating a new labyrinth...\n");
                ask_for_labyrinth_size_and_name(&length, &width, &labyrinth_name);
                printf("Generating labyrinth of size %dx%d\n", length, width);

                labyrinth = generate_labyrinth(length, width);
                display_labyrinth(labyrinth, length, width);

                dump_labyrinth(seed, length, width, labyrinth_name);
                final_score = display_labyrinth_sdl(labyrinth, length, width);
                free_labyrinth(labyrinth, length, width);
                break;

            case 2:
                printf("Loading a saved labyrinth...\n");

                display_all_available_files(&labyrinth_name);

                load_labyrinth(labyrinth_name, &seed, &length, &width);

                srand(seed);

                printf("Loaded labyrinth '%s' with size %dx%d and seed %d\n", labyrinth_name, length, width, seed);

                labyrinth = generate_labyrinth(length, width);

                display_labyrinth(labyrinth,length, width);
                final_score = display_labyrinth_sdl(labyrinth, length, width);
                break;

            case 3:
                printf("Play !\n");
                final_score = display_labyrinth_sdl(labyrinth, length, width);
                break;

            case 4:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        //dump_score(final_score, labyrinth_name);
        free(labyrinth_name);
        //free_labyrinth(labyrinth, length*2+1, width*2+1);
        
    }

    return 0;
}