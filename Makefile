CC = gcc
CFLAGS = -Wall -pedantic

SRC_DIR = src
SUBUNIT_DIR = $(SRC_DIR)/subunit

APP = app.x
APP_SRC = $(SRC_DIR)/main.c
APP_OBJ = $(SRC_DIR)/main.o

all: $(APP) lab_generator

$(APP): $(APP_OBJ)
	$(CC) $(APP_OBJ) $(CFLAGS) -o $@

$(APP_OBJ): $(APP_SRC)
	$(CC) -c $< $(CFLAGS) -o $@

lab_generator: $(SUBUNIT_DIR)/lab_generator.c $(SUBUNIT_DIR)/utils.o
	$(CC) $(SUBUNIT_DIR)/lab_generator.c $(SUBUNIT_DIR)/utils.o $(CFLAGS) -o $@

$(SUBUNIT_DIR)/utils.o: $(SUBUNIT_DIR)/utils.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(APP) $(APP_OBJ) lab_generator $(SUBUNIT_DIR)/utils.o
