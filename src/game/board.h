#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdint.h>
#include <stdbool.h>

#include "../screen/screen_object.h"
#include "piece.h"

// DEFINES
#define BOARD_GRID_WIDTH 10
#define BOARD_GRID_HEIGHT 22
#define BOARD_WIDTH (3 * BOARD_GRID_WIDTH + 4)
#define BOARD_HEIGHT (BOARD_GRID_HEIGHT + 2)
#define BOARD_SCREEN_OBJECT_X 22
#define BOARD_SCREEN_OBJECT_Y 0


typedef uint16_t board_line;

#define BOARD_FULL_LINE 0xFFFF >> (16 - BOARD_GRID_WIDTH)


typedef struct {
    board_line lines[BOARD_GRID_HEIGHT];
} BoardGrid;


typedef struct {
    ScreenObject *object;
    BoardGrid grid;
} Board;


// FUNCTIONS
void board_init(Board *board);
void board_cleanup(Board *board);

void board_reset(Board *board);

void board_clear(Board *board);
void board_update(Board *board, Piece *piece);

void board_draw(Board *board, Piece *piece);

void board_clear_lines(Board *board);

bool board_is_possible_move(Board *board, Piece *piece, int8_t dx, int8_t dy, uint8_t rotation);

#endif // __BOARD_H__
