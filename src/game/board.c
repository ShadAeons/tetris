#include "board.h"

#include <stdio.h>
#include <string.h>


void board_init(Board *board) {
    board->object = screen_object_create(BOARD_SCREEN_OBJECT_X, BOARD_SCREEN_OBJECT_Y, BOARD_WIDTH, BOARD_HEIGHT);
    board_reset(board);
}


void board_cleanup(Board *board) {
    screen_object_destroy(board->object);
}


void board_reset(Board *board) {
    for (int i = 0; i < BOARD_GRID_WIDTH * BOARD_GRID_HEIGHT; i++) {
        board->grid.lines[i] = 0;
    }

    int counter = 0;

    // Game board
    for (int i = 0; i < BOARD_GRID_HEIGHT; i++) {
        board->object->data[counter++] = '<';
        board->object->data[counter++] = '!';

        for (int j = 0; j < BOARD_GRID_WIDTH; j++) {
            board->object->data[counter++] = ' ';
            board->object->data[counter++] = ' ';
            board->object->data[counter++] = '.';
        }
        
        board->object->data[counter++] = '!';
        board->object->data[counter++] = '>';
    }

    // Ground level
    board->object->data[counter++] = '<';
    board->object->data[counter++] = '!';
    for (int i = 2; i < BOARD_WIDTH - 2; i++) {
        board->object->data[counter++] = '=';
    }
    board->object->data[counter++] = '!';
    board->object->data[counter++] = '>';

    board->object->data[counter++] = ' ';
    board->object->data[counter++] = ' ';
    for (int i = 2; i < (BOARD_WIDTH - 4) / 2 + 2; i++) {
        board->object->data[counter++] = '\\';
        board->object->data[counter++] = '/';
    }
    board->object->data[counter++] = ' ';
    board->object->data[counter++] = ' ';
}


void board_clear(Board *board) {
    // Clears the board's screen object to follow the board's grid
    for (int i = 0; i < BOARD_GRID_WIDTH * BOARD_GRID_HEIGHT; i++) {
        uint8_t x = i % BOARD_GRID_WIDTH;
        uint8_t y = (uint8_t) (i / BOARD_GRID_WIDTH);

        if ((board->grid.lines[y] & (1 << x)) != 0) {
            board->object->data[y * BOARD_WIDTH + (3 * x + 2)] = '[';
            board->object->data[y * BOARD_WIDTH + (3 * x + 3)] = ']';
        } else {
            board->object->data[y * BOARD_WIDTH + (3 * x + 2)] = ' ';
            board->object->data[y * BOARD_WIDTH + (3 * x + 3)] = ' ';
        }
    }
}


void board_update(Board *board, Piece *piece) {
    // Update the board grid to add a new piece
    for (int i = 0; i < PIECE_BLOCKS * PIECE_BLOCKS; i++) {
        uint8_t px = i % PIECE_BLOCKS;
        uint8_t py = (uint8_t) (i / PIECE_BLOCKS);

        if (PIECES[piece->type][piece->rotation][py][px] == 0) continue;

        uint8_t x = piece->position[0] + px;
        uint8_t y = piece->position[1] + py;
        board->grid.lines[y] |= PIECES[piece->type][piece->rotation][py][px] << x;
    }
}


void board_draw(Board *board, Piece *piece) {
    board_clear(board);

    // Draw a new piece temporarily
    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            uint8_t x = piece->position[0] + j;
            uint8_t y = piece->position[1] + i;

            if (PIECES[piece->type][piece->rotation][i][j] == 1) {
                board->object->data[y * BOARD_WIDTH + (3 * x + 2)] = '[';
                board->object->data[y * BOARD_WIDTH + (3 * x + 3)] = ']';
            }
        }
    }
}


void board_clear_lines(Board *board) {
    int index = BOARD_GRID_HEIGHT - 1;
    while (index >= 0) {
        if (board->grid.lines[index] != BOARD_FULL_LINE) {
            index--;
            continue;
        }

        // Move all lines above down
        for (int j = index; j > 0; j--) {
            board->grid.lines[j] = board->grid.lines[j - 1];
        }
        
        // Top line is empty
        board->grid.lines[0] = 0;
    }
}


bool board_is_possible_move(Board *board, Piece *piece, int8_t dx, int8_t dy, uint8_t rotation) {
    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            if (PIECES[piece->type][rotation][i][j] == 0) continue;
            int8_t x = piece->position[0] + dx + j;
            int8_t y = piece->position[1] + dy + i;

            if (0 > x || x >= BOARD_GRID_WIDTH || y >= BOARD_GRID_HEIGHT
                || (board->grid.lines[y] & (1 << x)) != 0) {
                return false;
            }
        }
    }

    return true;
}
