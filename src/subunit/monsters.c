#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "monsters.h"

static int clamp(int v, int lo, int hi){ return v < lo ? lo : (v > hi ? hi : v); }

int is_monster_char(char c) {
    return c == GHOST_CHAR || c == OGRE_CHAR;
}

static void place_monster_on_grid(Labyrinth *lab, Monster *m, int x, int y) {
    if (m->under_char) {
        lab->grid[m->x][m->y] = m->under_char;
    }
    m->x = x; m->y = y;
    m->under_char = lab->grid[x][y];
    lab->grid[x][y] = (char)m->type;
}

static void ghost_move(Monster *m, Labyrinth *lab) {
    int px = lab->starting_x;
    int py = lab->starting_y;
    int dx = 0, dy = 0;
    if (px > m->x) dx = 1; else if (px < m->x) dx = -1;
    if (py > m->y) dy = 1; else if (py < m->y) dy = -1;

    dx = clamp(dx, -m->mobility_range, m->mobility_range);
    dy = clamp(dy, -m->mobility_range, m->mobility_range);

    int nx = m->x + (dx == 0 ? 0 : (dx > 0 ? 1 : -1));
    int ny = m->y + (dy == 0 ? 0 : (dy > 0 ? 1 : -1));

    int rows = lab->length * 2 + 1;
    int cols = lab->width * 2 + 1;
    nx = clamp(nx, 0, rows - 1);
    ny = clamp(ny, 0, cols - 1);

    place_monster_on_grid(lab, m, nx, ny);
}

static int manhattan(int x1, int y1, int x2, int y2){
    int dx = x1 - x2; if (dx < 0) dx = -dx;
    int dy = y1 - y2; if (dy < 0) dy = -dy;
    return dx + dy;
}

static void find_nearest_chest(Labyrinth *lab, int x, int y, int *outx, int *outy) {
    int rows = lab->length * 2 + 1;
    int cols = lab->width * 2 + 1;
    int bestd = INT_MAX; *outx = x; *outy = y;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (lab->grid[i][j] == CHEST) {
                int d = manhattan(x,y,i,j);
                if (d < bestd) { bestd = d; *outx = i; *outy = j; }
            }
        }
    }
}

static int can_step(Labyrinth *lab, int x, int y) {
    char c = lab->grid[x][y];
    if (c == WALL || c == DOOR) return 0;
    return 1;
}

static void ogre_move(Monster *m, Labyrinth *lab) {
    int cx, cy;
    find_nearest_chest(lab, m->x, m->y, &cx, &cy);

    int rows = lab->length * 2 + 1;
    int cols = lab->width * 2 + 1;

    if (manhattan(m->x, m->y, cx, cy) > m->mobility_range) {
        int cand[4][2] = {{m->x+1,m->y},{m->x-1,m->y},{m->x,m->y+1},{m->x,m->y-1}};
        int besti = -1; int bestd = INT_MAX;
        for (int k=0;k<4;k++){
            int nx=cand[k][0], ny=cand[k][1];
            if (nx<0||ny<0||nx>=rows||ny>=cols) continue;
            if (!can_step(lab,nx,ny)) continue;
            int d = manhattan(nx,ny,cx,cy);
            if (d < bestd) { bestd = d; besti = k; }
        }
        if (besti != -1) {
            place_monster_on_grid(lab, m, cand[besti][0], cand[besti][1]);
            return;
        }
    }

    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for (int t=0;t<4;t++){
        int r = rand()%4;
        int nx = m->x + dirs[r][0];
        int ny = m->y + dirs[r][1];
        if (nx>=0 && ny>=0 && nx<rows && ny<cols && can_step(lab,nx,ny)){
            place_monster_on_grid(lab, m, nx, ny);
            return;
        }
    }
}

static void ensure_extras(Labyrinth *lab) {
    if (!lab->extras) {
        lab->extras = (LabyrinthInternalExtras*)calloc(1, sizeof(LabyrinthInternalExtras));
        lab->extras->extra.difficulty = DIFF_EASY;
        lab->extras->extra.monsters = NULL;
        lab->extras->extra.monster_count = 0;
    }
}

void init_monsters(Labyrinth *lab, Difficulty diff) {
    ensure_extras(lab);
    lab->extras->extra.difficulty = diff;

    int cells = lab->length * lab->width;
    int count = diff == DIFF_HARD ? (cells / 8) : (cells / 16);
    if (count < 2) count = 2;

    lab->extras->extra.monsters = (Monster*)calloc((size_t)count, sizeof(Monster));
    lab->extras->extra.monster_count = count;

    int rows = lab->length * 2 + 1;
    int cols = lab->width * 2 + 1;

    for (int i = 0; i < count; ++i) {
        Monster *m = &lab->extras->extra.monsters[i];
        if (i % 2 == 0) {
            m->type = MONSTER_GHOST;
            m->penalty_points = 300;
            m->mobility_range = 2;
            m->move = ghost_move;
        } else {
            m->type = MONSTER_OGRE;
            m->penalty_points = 500;
            m->mobility_range = 4;
            m->move = ogre_move;
        }
        m->alive = 1;

        int x,y; int tries=0;
        do {
            x = rand()%rows; y = rand()%cols; tries++;
        } while (tries < 1000 && (lab->grid[x][y] != PATH || (x==lab->starting_x && y==lab->starting_y) || (x==lab->ending_x && y==lab->ending_y)));
        if (lab->grid[x][y] != PATH) { x = lab->starting_x; y = lab->starting_y; }
        m->under_char = 0;
        place_monster_on_grid(lab, m, x, y);
    }
}

void move_monsters(Labyrinth *lab) {
    if (!lab->extras) return;
    Monster *arr = lab->extras->extra.monsters;
    int count = lab->extras->extra.monster_count;
    for (int i=0;i<count;i++){
        if (!arr[i].alive) continue;
        arr[i].move(&arr[i], lab);
    }
}

void handle_player_monster_collisions(Labyrinth *lab) {
    if (!lab->extras) return;
    int px = lab->starting_x;
    int py = lab->starting_y;
    Monster *arr = lab->extras->extra.monsters;
    int count = lab->extras->extra.monster_count;
    for (int i=0;i<count;i++){
        Monster *m = &arr[i];
        if (!m->alive) continue;
        if (m->x == px && m->y == py) {
            lab->coins -= m->penalty_points;
            lab->grid[m->x][m->y] = PLAYER; 
            m->alive = 0;
        }
    }
}
