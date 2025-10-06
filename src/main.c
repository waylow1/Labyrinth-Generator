#include "labyrinth_generator.h"
#include "labyrinth_menu.h"
#include <time.h>
#include "utils.h"
#include "displays.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

    srand(time(NULL));

    display_menu();
    int choice = get_user_choice();

   switch (choice)
  {
    case 1:
        printf("Generating a new labyrinth...\n");
        int length, width;
        ask_for_labyrinth_size(&length, &width);
        printf("Generating labyrinth of size %dx%d\n", length, width);
        
        Labyrinth labyrinth = generate_labyrinth(length, width);

        display_labyrinth(labyrinth, length*2+1, width*2+1);

        //dump_labyrinth(labyrinth, length, width);
        break;
    case 2:
        printf("Loading a saved labyrinth...\n");
        break;
    case 3:
        printf("Exiting the program. Goodbye!\n");
        exit(0);
        break;
  }
    return 0;
}