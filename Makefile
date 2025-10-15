CC = gcc
CFLAGS = -Wall -pedantic -I$(INCLUDE_DIR) -g `sdl2-config --cflags --libs` -lSDL2_ttf
INCLUDE_DIR = include
SRC_DIR = src
SUBUNIT_DIR = $(SRC_DIR)/subunit
BUILD_DIR = build
CFG_DIR = config
BIN_DIR = bin
APP = $(BIN_DIR)/labyrinth

APP_SRC = $(SRC_DIR)/main.c $(SUBUNIT_DIR)/labyrinth_generator.c $(SUBUNIT_DIR)/labyrinth_menu.c $(SUBUNIT_DIR)/utils.c $(SUBUNIT_DIR)/displays.c $(SUBUNIT_DIR)/labyrinth_player_movement.c 
APP_OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/labyrinth_generator.o $(BUILD_DIR)/labyrinth_menu.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/displays.o $(BUILD_DIR)/labyrinth_player_movement.o $(BUILD_DIR)/labyrinth_score.o

.PHONY: all clean docs help

all: $(APP)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SUBUNIT_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(APP): $(APP_OBJ) | $(BIN_DIR)
	$(CC) $(APP_OBJ) $(CFLAGS) -o $@

docs: Doxyfile
	doxygen Doxyfile

clean:
	rm -f $(APP) $(APP_OBJ) $(BUILD_DIR)/* $(BIN_DIR)/* $(CFG_DIR)/*.cfg

help:
	@echo "Makefile targets:"
	@echo "  all     - Build the application"
	@echo "  docs    - Generate docs with Doxygen"
	@echo "  clean   - Remove compiled files"
	@echo "  help    - Show this message"
