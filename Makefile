CC = gcc
CFLAGS = -I ~/raylib/src -I $(INCLUDE_DIR) -L ~/raylib/release/libs/linux
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
TARGET = main

$(OBJ_DIR)/$(TARGET): $(SRC_DIR)/main.c $(SRC_DIR)/asteroid.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	rm -f $(SRC_DIR)/*.o

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/$(TARGET)