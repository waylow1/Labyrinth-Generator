CC = gcc
CFLAGS = -Wall -pedantic -I$(INCLUDE_DIR)
INCLUDE_DIR = include
SRC_DIR = src
SUBUNIT_DIR = $(SRC_DIR)/subunit
APP = app.x
APP_SRC = $(SRC_DIR)/main.c
APP_OBJ = $(SRC_DIR)/main.o


.PHONY: all clean docs test

all: $(APP) labyrinth_generator.x

$(APP): $(APP_OBJ)
	$(CC) $(APP_OBJ) $(CFLAGS) -o $@

$(APP_OBJ): $(APP_SRC)
	$(CC) -c $< $(CFLAGS) -o $@

labyrinth_generator.x: $(SUBUNIT_DIR)/labyrinth_generator.c $(SUBUNIT_DIR)/utils.o
	$(CC) $(SUBUNIT_DIR)/labyrinth_generator.c $(SUBUNIT_DIR)/utils.o $(CFLAGS) -o $@

$(SUBUNIT_DIR)/utils.o: $(SUBUNIT_DIR)/utils.c
	$(CC) -c $< $(CFLAGS) -o $@



docs: 
	doxygen Doxyfile

clean:
	rm -f $(APP) $(APP_OBJ) lab_generator $(SUBUNIT_DIR)/utils.o
