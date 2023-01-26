CC = gcc

SRC = $(wildcard src/*.c)

BIN_DIR = bin
BIN_FILE = main
BIN = $(BIN_DIR)/$(BIN_FILE)

COMMON_CFLAGS = -Wall -Wextra
CFLAGS = $(COMMON_CFLAGS) -O3
DB_CFLAGS = $(COMMON_CFLAGS) -ggdb

LFLAGS = -lmingw32 -lSDL2_ttf -lSDL2_image -lSDL2main -lSDL2
IDIR = include

LDIR = lib

comp:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LFLAGS) -I $(IDIR) -L $(LDIR)
	./bin/main

db:
	$(CC) $(SRC) -o $(BIN) $(DB_CFLAGS) $(LFLAGS) -I $(IDIR) -L $(LDIR)
	gdb bin/main