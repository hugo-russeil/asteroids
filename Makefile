CC = gcc
CFLAGS = -I ~/raylib/src -I $(INCLUDE_DIR) -L ~/raylib/release/libs/linux
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
TARGET = main
SOURCES = $(wildcard $(SRC_DIR)/*.c)

$(OBJ_DIR)/$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	rm -f $(SRC_DIR)/*.o

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/$(TARGET)