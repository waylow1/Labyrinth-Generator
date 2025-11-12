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
    ladder->count = 0;
    ladder->scores = malloc(10 * sizeof(Score));
    char * labyrinth_name = NULL;
    Labyrinth labyrinth = {0};
    int length = 0, width = 0;
    int seed;
    Difficulty chosen_diff = DIFF_EASY;

    while (1) {
        display_menu();
        int choice = get_user_choice();
        switch (choice) {
            case 1:
                seed = (int)time(NULL);
                srand(seed);
                printf("Generating a new labyrinth...\n");
                ask_for_labyrinth_size_and_name(&length, &width, &labyrinth_name);
                int d = ask_for_difficulty();
                chosen_diff = (d == 1 ? DIFF_HARD : DIFF_EASY);
                printf("Generating labyrinth of size %dx%d\n", length, width);

                labyrinth = generate_labyrinth_with_difficulty(length, width, chosen_diff);
                display_labyrinth(labyrinth, length, width);

                dump_labyrinth_ext(seed, length, width, chosen_diff, labyrinth_name);
                create_score_file_if_not_exists(labyrinth_name);
                free(labyrinth_name);
                labyrinth_name = NULL;
                free_labyrinth(labyrinth, length, width);
                labyrinth.grid = NULL;
                labyrinth.extras = NULL;
                length = width = 0;
                break;

            case 2:
                printf("Loading a saved labyrinth...\n");

                display_all_available_files(&labyrinth_name);

                Difficulty loaded_diff = DIFF_EASY;
                load_labyrinth_ext(labyrinth_name, &seed, &length, &width, &loaded_diff);
                chosen_diff = loaded_diff;

                load_labyrinth_scores(ladder, labyrinth_name);
                
                if (length <= 0 || width <= 0) {
                    printf("❌ Failed to load labyrinth '%s'. Please check that the file exists in config/.\n", labyrinth_name);
                    if (labyrinth_name) {
                        free(labyrinth_name);
                        labyrinth_name = NULL;
                    }
                    break; 
                }

                srand(seed);

                printf("Loaded labyrinth '%s' with size %dx%d and seed %d\n", labyrinth_name, length, width, seed);

                labyrinth = generate_labyrinth_with_difficulty(length, width, chosen_diff);

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
                display_ladder(*ladder);
                sort_scores(ladder);
                dump_scores(*ladder, labyrinth_name);
                display_ladder(*ladder);

                free(labyrinth_name);
                free_labyrinth(labyrinth, length, width);
                labyrinth_name = NULL;
                labyrinth.grid = NULL;
                labyrinth.extras = NULL;
                length = width = 0;
                break;

            case 4:
                printf("Exiting the program. Goodbye!\n");

                if (ladder) {
                    if (ladder->scores) {
                        free(ladder->scores);
                        ladder->scores = NULL;
                    }
                    free(ladder);
                    ladder = NULL;
                }

                if (labyrinth.grid) {
                    free_labyrinth(labyrinth, length, width);
                    labyrinth.grid = NULL;
                    labyrinth.extras = NULL;
                    length = width = 0;
                }

                if (labyrinth_name) {
                    free(labyrinth_name);
                    labyrinth_name = NULL;
                }

                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } 
    return 0;
}