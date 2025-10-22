#include "labyrinth_generator.h"
#include "labyrinth_menu.h"
#include "labyrinth_player_movement.h"
#include "labyrinth_score.h"
#include <time.h>
#include "utils.h"
#include "displays.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
 
    Score final_score;

    Ladder * ladder = malloc(sizeof(Ladder));
    ladder->scores = malloc(10 * sizeof(Score));
    char * labyrinth_name = NULL;
    Labyrinth labyrinth;
    int length = 0, width = 0;

    while (1) {
        display_menu();
        int choice = get_user_choice();
        switch (choice) {
            case 1:
                int seed = (int)time(NULL);
                srand(seed);
                printf("Generating a new labyrinth...\n");
                ask_for_labyrinth_size_and_name(&length, &width, &labyrinth_name);
                printf("Generating labyrinth of size %dx%d\n", length, width);

                labyrinth = generate_labyrinth(length, width);
                display_labyrinth(labyrinth, length, width);

                dump_labyrinth(seed, length, width, labyrinth_name);
                create_score_file_if_not_exists(labyrinth_name);
                free(labyrinth_name);
                labyrinth_name = NULL;
                free_labyrinth(labyrinth, length, width);
                break;

            case 2:
                printf("Loading a saved labyrinth...\n");

                display_all_available_files(&labyrinth_name);

                load_labyrinth(labyrinth_name, &seed, &length, &width);

                load_labyrinth_scores(ladder, labyrinth_name);
                
                printf("%d", ladder->count);

                srand(seed);

                printf("Loaded labyrinth '%s' with size %dx%d and seed %d\n", labyrinth_name, length, width, seed);

                labyrinth = generate_labyrinth(length, width);

                display_labyrinth(labyrinth,length, width);
                display_ladder(*ladder);
                break;

            case 3:
                printf("Play !\n");
                if (!labyrinth_name || labyrinth_name == NULL) {
                    printf("No labyrinth loaded. Please load a labyrinth first.\n");
                    break;
                }

                final_score = display_labyrinth_sdl(labyrinth, length, width);

                add_new_score(ladder, final_score);
                sort_scores(ladder);
                dump_scores(*ladder, labyrinth_name);
                display_ladder(*ladder);

                free(labyrinth_name);
                free_labyrinth(labyrinth, length, width);
                labyrinth_name = NULL;
                break;

            case 4:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    }

    return 0;
}