# Labyrinth Generator

A small C + SDL2 project that generates, plays, and documents mazes. It features Easy/Hard difficulty, optional monsters with function-pointer AI, a simple score ladder, and a unit test suite.

## Features
- Maze generation (Kruskal-like) with objects (player, exit, door+key, chests, traps)
- Difficulty modes (Hard: extra loops + monsters)
- Monsters (ghosts/ogres) with behavior via function pointers
- Config I/O (seed, size, difficulty) and score persistence
- SDL rendering (grid, time, points) + ASCII debug displays
- Unit tests (minunit)

## Project Layout
```
Labyrinth-Generator/
├─ Doxyfile
├─ Makefile
├─ README.md
├─ asset/
├─ bin/
│  ├─ labyrinth
│  └─ test_labyrinth
├─ build/
├─ config/
│  ├─ labyrinth8572.cfg-example
│  └─ toto.cfg
├─ docs/      (generated output: html/, latex/)
│  └─ mainpage.md   (this page)
├─ include/
│  ├─ displays.h
│  ├─ labyrinth_generator.h
│  ├─ labyrinth_menu.h
│  ├─ labyrinth_player_movement.h
│  ├─ labyrinth_score.h
│  ├─ minunit.h
│  ├─ monsters.h
│  └─ utils.h
├─ score/
│  └─ *.score
├─ src/
│  ├─ main.c
│  └─ subunit/
│     ├─ displays.c
│     ├─ labyrinth_generator.c
│     ├─ labyrinth_menu.c
│     ├─ labyrinth_player_movement.c
│     ├─ labyrinth_score.c
│     ├─ monsters.c
│     └─ utils.c
└─ test/
   └─ test_labyrinth_generator.c
```

## Build & Run
```bash
make
./bin/labyrinth
# Run tests
./bin/test_labyrinth
```

## Documentation
- Regenerate: `doxygen Doxyfile`
- Open: `docs/html/index.html`
