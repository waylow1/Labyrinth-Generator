typedef struct cell{
    int x,y, value;
} LabyrinthCell;

void display_matrix(int ** matrix, int lines, int columns);
void free_matrix(int ** matrix, int n);
void display_labyrinth(LabyrinthCell ** labyrinth, int lines, int columns);
void display_labyrinth_numerically(LabyrinthCell ** labyrinth, int lines, int columns);
void free_labyrinth(LabyrinthCell ** labyrinth, int lines);
