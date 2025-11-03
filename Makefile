CC = gcc
INCLUDE_DIR = include
SRC_DIR = src
SUBUNIT_DIR = $(SRC_DIR)/subunit
BUILD_DIR = build
BIN_DIR = bin
CFG_DIR = config
TEST_DIR = test
CFLAGS = -Wall -pedantic -I$(INCLUDE_DIR) -g `sdl2-config --cflags` -lSDL2_ttf
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

APP = $(BIN_DIR)/labyrinth

APP_SRC = $(SRC_DIR)/main.c \
          $(SUBUNIT_DIR)/labyrinth_generator.c \
          $(SUBUNIT_DIR)/labyrinth_menu.c \
          $(SUBUNIT_DIR)/utils.c \
          $(SUBUNIT_DIR)/displays.c \
          $(SUBUNIT_DIR)/labyrinth_player_movement.c \
          $(SUBUNIT_DIR)/labyrinth_score.c

APP_OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(APP_SRC)))

TEST_SRC = $(TEST_DIR)/test_labyrinth_generator.c \
           $(SUBUNIT_DIR)/labyrinth_generator.c \
           $(SUBUNIT_DIR)/utils.c

TEST_OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(TEST_SRC)))
TEST_BIN = $(BIN_DIR)/test_labyrinth

.PHONY: all clean docs help tests

all: $(APP)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SUBUNIT_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(APP): $(APP_OBJ) | $(BIN_DIR)
	$(CC) $(APP_OBJ) $(CFLAGS) $(LDFLAGS) -o $@

tests: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) | $(BIN_DIR)
	$(CC) $(TEST_OBJ) $(CFLAGS) $(LDFLAGS) -o $@

docs: Doxyfile
	doxygen Doxyfile

clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/* $(CFG_DIR)/*.cfg

help:
	@echo "Makefile targets:"
	@echo "  all     - Build the application"
	@echo "  tests   - Build and run unit tests"
	@echo "  docs    - Generate docs with Doxygen"
	@echo "  clean   - Remove compiled files"
	@echo "  help    - Show this message"
