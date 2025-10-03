#include "labyrinth_generator.h"
#include "labyrinth_menu.h"
#include <time.h>
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

    // Test pour la partie génération du labyrinthe
    srand(time(NULL));
    // LabyrinthCell ** labyrinth = allocate_labyrinth();

    // int ** vertical_walls = allocate_matrix_walls(LAB_LENGTH+1, LAB_WIDTH);
    // int ** horizontal_walls = allocate_matrix_walls(LAB_LENGTH, LAB_WIDTH+1);
    // generate_labyrinth(labyrinth, vertical_walls, horizontal_walls);

    // display_labyrinth(labyrinth, LAB_LENGTH, LAB_WIDTH);


    display_menu();
    int choice = get_user_choice();
    printf("You chose: %d\n", choice);

   switch (choice)
  {
    case 1:
        printf("Generating a new labyrinth...\n");
        int length, width;
        ask_for_labyrinth_size(&length, &width);
        printf("Generating labyrinth of size %dx%d\n", length, width);
        LabyrinthCell ** labyrinth = allocate_labyrinth(length, width);
        generate_labyrinth(labyrinth, length, width);
        dump_labyrinth(labyrinth, length, width);
        display_labyrinth(labyrinth, length, width);
        break;
    case 2:
        printf("Loading a saved labyrinth...\n");
        // Call the function to load a saved labyrinth
        break;
    case 3:
        printf("Exiting the program. Goodbye!\n");
        exit(0);
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        break;
  }


    return 0;
}