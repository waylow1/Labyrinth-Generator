#include <stdio.h>
#include <stdlib.h>

void display_menu() {
    printf("Welcome to the Labyrinth Generator!\n");
    printf("1. Generate a new labyrinth\n");
    printf("2. Load a labyrinth from file\n");
    printf("3. Play the labyrinth\n");
    printf("4. Exit\n");
    printf("Please enter your choice: ");
}

void ask_for_labyrinth_size_and_name(int *length, int *width, char **name) {
    int w, h, result_w, result_h;
    while (1) {
        printf("Enter labyrinth width (odd number between 5 and 51): ");
        result_w = scanf("%d", &w);
        printf("Enter labyrinth height (odd number between 5 and 51): ");
        result_h = scanf("%d", &h);
        if (result_w == 1 && result_h == 1 &&
            w >= 5 && w <= 51 && w % 2 == 1 &&
            h >= 5 && h <= 51 && h % 2 == 1) {
            break;
        } else {
            printf("Invalid input. Please enter odd numbers between 5 and 101 for both width and height.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
    }
    
    *width = w;
    *length = h;

    *name = malloc(100 * sizeof(char));
    printf("Enter labyrinth name: ");
    scanf("%99s", *name);
}


int get_user_choice() {
    int choice;
    int result;
    while (1) {
        result = scanf("%d", &choice);
        if (result == 1 && choice >= 1 && choice <= 4) {
            break;
        } else {
            printf("Invalid input you must choose between 1 and 4: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
    }
    return choice;
}