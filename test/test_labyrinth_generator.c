#include "minunit.h"
#include "utils.h"
#include "labyrinth_generator.h" 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    int **visited = malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; ++i) {
        visited[i] = calloc((size_t)cols, sizeof(int));
    }

    int reachable_cells = visited_count(labyrinth, visited, labyrinth.starting_x, labyrinth.starting_y);

    int total_path_cells = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (labyrinth.grid[i][j] != WALL) total_path_cells++;
        }
    }

    mu_assert_int_eq(total_path_cells, reachable_cells);

    for (int i = 0; i < rows; ++i) free(visited[i]);
    free(visited);
    free_labyrinth(labyrinth, length, width);
}

static int is_odd(int v) { return (v % 2) != 0; }

static int count_char(const Labyrinth *lab, char c) {
    int rows = lab->length * 2 + 1;
    int cols = lab->width * 2 + 1;
    int cnt = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (lab->grid[i][j] == c) cnt++;
        }
    }
    return cnt;
}

MU_TEST(test_utils_allocation) {
    int length = 3, width = 4;
    LabyrinthCell **cells = allocate_labyrinth(length, width);
    int expected = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            mu_assert_int_eq(i, cells[i][j].x);
            mu_assert_int_eq(j, cells[i][j].y);
            mu_assert_int_eq(expected++, cells[i][j].value);
        }
    }
    free_labyrinth_cells(cells, length);

    int lines = 5, columns = 6;
    int **walls = allocate_matrix_walls(lines, columns);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            mu_assert_int_eq(1, walls[i][j]);
        }
    }
    free_matrix(walls, lines);
}

MU_TEST(test_dump_and_load_labyrinth) {
    int seed = 42, lines = 7, columns = 9;
    const char *name = "unittest_tmp123";
    dump_labyrinth(seed, lines, columns, (char*)name);

    int seed2 = 0, lines2 = 0, columns2 = 0;
    load_labyrinth(name, &seed2, &lines2, &columns2);

    mu_assert_int_eq(seed, seed2);
    mu_assert_int_eq(lines, lines2);
    mu_assert_int_eq(columns, columns2);

    char path[256];
    snprintf(path, sizeof(path), "config/%s.cfg", name);
    (void)remove(path);
}

MU_TEST(test_labyrinth_invariants) {
    int length = 7, width = 9;
    srand(1234);
    Labyrinth lab = generate_labyrinth(length, width);

    mu_assert_int_eq(length, lab.length);
    mu_assert_int_eq(width, lab.width);

    int rows = length * 2 + 1;

    mu_assert_int_eq(1, lab.starting_x);
    mu_assert(is_odd(lab.starting_y), "starting_y doit être impair");
    mu_assert_int_eq(rows - 2, lab.ending_x);
    mu_assert(is_odd(lab.ending_y), "ending_y doit être impair");

    mu_assert_int_eq(PLAYER, lab.grid[lab.starting_x][lab.starting_y]);
    mu_assert_int_eq(DOOR, lab.grid[lab.ending_x][lab.ending_y]);
    mu_assert_int_eq(END, lab.grid[lab.ending_x + 1][lab.ending_y]);

    int key_count = count_char(&lab, KEY);
    mu_assert_int_eq(1, key_count);

    int chest_count = count_char(&lab, CHEST);
    int trap_count = count_char(&lab, TRAP);
    int max_chests = (length * width) / 4 + 5;
    mu_assert(chest_count >= 5 && chest_count <= max_chests, "Nombre de coffres hors bornes");
    int expected_traps = chest_count / 2;
    mu_assert(trap_count <= expected_traps && trap_count >= expected_traps - 2,
              "Nombre de pièges incohérent avec le nombre de coffres");

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            int gi = 2 * i + 1;
            int gj = 2 * j + 1;
            char v = lab.grid[gi][gj];
            mu_assert(
                v == PATH || v == PLAYER || v == DOOR || v == KEY || v == CHEST || v == TRAP,
                "Centre de cellule invalide"
            );
        }
    }

    free_labyrinth(lab, length, width);
}

MU_TEST(test_deterministic_generation_with_seed) {
    int length = 6, width = 6;

    srand(777);
    Labyrinth a = generate_labyrinth(length, width);

    srand(777);
    Labyrinth b = generate_labyrinth(length, width);

    int rows = length * 2 + 1;
    int cols = width * 2 + 1;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mu_assert_int_eq(a.grid[i][j], b.grid[i][j]);
        }
    }

    mu_assert_int_eq(a.starting_x, b.starting_x);
    mu_assert_int_eq(a.starting_y, b.starting_y);
    mu_assert_int_eq(a.ending_x, b.ending_x);
    mu_assert_int_eq(a.ending_y, b.ending_y);

    free_labyrinth(a, length, width);
    free_labyrinth(b, length, width);
}

MU_TEST(test_choose_wall_contract_and_merge_sets) {
    int length = 3, width = 3;
    srand(42);

    for (int t = 0; t < 200; ++t) {
        int x = rand() % length;
        int y = rand() % width;
        int nx = -1, ny = -1;
        int dir = choose_wall(length, width, x, y, &nx, &ny);
        mu_assert(dir >= -1 && dir <= 3, "dir hors bornes");
        if (dir == -1) continue; 
        mu_assert(nx >= 0 && nx < length && ny >= 0 && ny < width, "voisin hors bornes");
        int dx = nx - x;
        int dy = ny - y;
        mu_assert((dx == 0 && (dy == 1 || dy == -1)) || (dy == 0 && (dx == 1 || dx == -1)), "voisin non adjacent");
        if (dir == 0) mu_assert_int_eq(1, dx);
        if (dir == 1) mu_assert_int_eq(1, dy);
        if (dir == 2) mu_assert_int_eq(-1, dx);
        if (dir == 3) mu_assert_int_eq(-1, dy);
    }

    LabyrinthCell **cells = allocate_labyrinth(length, width);

    cells[0][0].value = 2;
    cells[1][1].value = 2;
    merge_sets(cells, length, width, 2, 0);
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            mu_assert(cells[i][j].value != 2, "merge_sets n'a pas remplacé toutes les valeurs");
        }
    }
    free_labyrinth_cells(cells, length);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_labyrinth_is_perfect);
    MU_RUN_TEST(test_utils_allocation);
    MU_RUN_TEST(test_dump_and_load_labyrinth);
    MU_RUN_TEST(test_labyrinth_invariants);
    MU_RUN_TEST(test_deterministic_generation_with_seed);
    MU_RUN_TEST(test_choose_wall_contract_and_merge_sets);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
