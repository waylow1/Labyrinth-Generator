CC = gcc
CFLAGS = -Wall -pedantic -I$(INCLUDE_DIR)
INCLUDE_DIR = include
SRC_DIR = src
SUBUNIT_DIR = $(SRC_DIR)/subunit
BUILD_DIR = build
BIN_DIR = bin
APP = $(BIN_DIR)/app.x
APP_SRC = $(SRC_DIR)/main.c
APP_OBJ = $(BUILD_DIR)/main.o

.PHONY: all clean docs test help

all: $(APP) $(BIN_DIR)/labyrinth_generator.x

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(APP): $(APP_OBJ) | $(BIN_DIR)
	$(CC) $(APP_OBJ) $(CFLAGS) -o $@

$(APP_OBJ): $(APP_SRC) | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(BIN_DIR)/labyrinth_generator.x: $(SUBUNIT_DIR)/labyrinth_generator.c $(BUILD_DIR)/utils.o | $(BIN_DIR)
	$(CC) $(SUBUNIT_DIR)/labyrinth_generator.c $(BUILD_DIR)/utils.o $(CFLAGS) -o $@

$(BUILD_DIR)/utils.o: $(SUBUNIT_DIR)/utils.c | $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) -o $@

docs: Doxyfile
	doxygen Doxyfile

clean:
	rm -f $(APP) $(APP_OBJ) $(BIN_DIR)/labyrinth_generator.x $(BUILD_DIR)/utils.o

help:
	@echo "Makefile targets:"
	@echo "  all                - Build the application and labyrinth generator"
	@echo "  docs               - Generate documentation using Doxygen"
	@echo "  clean              - Remove built files"
	@echo "  help               - Show this help message"