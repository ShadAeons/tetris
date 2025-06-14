CC 		:= gcc
CFLAGS 	:= -Wall -g

SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

SRC_FILES := main.c game/board.c game/game.c game/piece.c game/piece_queue.c game/piece_holder.c screen/screen.c screen/screen_object.c memory/alloc.c
OBJ_FILES := $(SRC_FILES:%.c=%.o)

SRC := $(SRC_FILES:%.c=$(SRC_DIR)/%.c)
OBJ := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

ifeq ($(OS),Windows_NT)
	TARGET_FILE := tetris.exe
	PATH_SEP := \\
	DEL := del /Q
else
	TARGET_FILE := tetris
	DEL := rm
	PATH_SEP := /
endif

TARGET := $(BIN_DIR)/$(TARGET_FILE)

#################################################################

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $^


$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(DEL) $(BIN_DIR)$(PATH_SEP)$(TARGET_FILE)
	$(DEL) $(OBJ_DIR)$(PATH_SEP)*.o
