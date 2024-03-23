CC = gcc
CC_WIN = i686-w64-mingw32-gcc
CFLAGS = -I ~/raylib/src -I $(INCLUDE_DIR) -L ~/raylib/release/libs/linux
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LDFLAGS_WIN = /usr/local/lib/libraylibwin.a -lgdi32 -lwinmm -luser32 -lm
SRC_DIR = src
INCLUDE_DIR = include
TARGET = asteroids
TARGET_WIN = asteroids.exe
SOURCES = $(wildcard $(SRC_DIR)/*.c)

all: $(TARGET) $(TARGET_WIN)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	rm -f $(SRC_DIR)/*.o

$(TARGET_WIN): $(SOURCES)
	$(CC_WIN) $(CFLAGS) $^ $(LDFLAGS_WIN) -o $@
	rm -f $(SRC_DIR)/*.o

.PHONY: clean all

clean:
	rm -f $(TARGET)
	rm -f $(TARGET_WIN)