#include "minunit.h"
#include "utils.h"
#include "labyrinth_generator.h" 
#include <stdlib.h>

int visited_count(Labyrinth labyrinth, int **visited, int x, int y) {
    if (x < 0 || y < 0 || x >= labyrinth.length * 2 + 1 || y >= labyrinth.width * 2 + 1) return 0;
    if (visited[x][y]) return 0;
    if (labyrinth.grid[x][y] == WALL) return 0;

    visited[x][y] = 1;
    int count = 1;

    count += visited_count(labyrinth, visited, x + 1, y);
    count += visited_count(labyrinth, visited, x - 1, y);
    count += visited_count(labyrinth, visited, x, y + 1);
    count += visited_count(labyrinth, visited, x, y - 1);

    return count;
}

MU_TEST(test_labyrinth_is_perfect) {
    int length = 5;
    int width = 5;
    Labyrinth labyrinth = generate_labyrinth(length, width);

    int rows = length * 2 + 1;
    int cols = width * 2 + 1;

    int **visited = allocate_matrix_walls(rows, cols);

    int reachable_cells = visited_count(labyrinth, visited, labyrinth.starting_x, labyrinth.starting_y);

    int total_path_cells = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (labyrinth.grid[i][j] != WALL) total_path_cells++;
        }
    }

    mu_assert_int_eq(total_path_cells, reachable_cells);

    free_matrix(visited, rows);
    free_labyrinth(labyrinth, length, width);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_labyrinth_is_perfect);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
