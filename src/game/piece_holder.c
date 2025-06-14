#include "piece_holder.h"

#include <string.h>


void piece_holder_init(PieceHolder *ph) {
    ph->object = screen_object_create(
        PIECE_HOLDER_SCREEN_OBJECT_X, PIECE_HOLDER_SCREEN_OBJECT_Y, 
        PIECE_HOLDER_SCREEN_OBJECT_WIDTH, PIECE_HOLDER_SCREEN_OBJECT_HEIGHT
    );

    piece_holder_reset(ph);
}


void piece_holder_cleanup(PieceHolder *ph) {
    screen_object_destroy(ph->object);
}


void piece_holder_reset(PieceHolder *ph) {
    ph->held_piece_type = __PIECE_COUNT;
    ph->used_hold = false;

    int counter = 0;

    for (int i = 0; i < PIECE_HOLDER_SCREEN_OBJECT_WIDTH; i++) {
        ph->object->data[counter++] = '=';
    }

    for (int i = 0; i < PIECE_HOLDER_HEIGHT; i++) {
        ph->object->data[counter++] = '!';
        for (int j = 0; j < PIECE_HOLDER_WIDTH; j++) {
            ph->object->data[counter++] = ' ';
            ph->object->data[counter++] = ' ';
            ph->object->data[counter++] = '.';
        }
        ph->object->data[counter++] = '!';
    }

    memcpy(&ph->object->data[counter], &ph->object->data[0], sizeof(char) * PIECE_HOLDER_SCREEN_OBJECT_WIDTH);
}


void piece_holder_update(PieceHolder *ph) {
    PieceType type = ph->held_piece_type;
    for (int i = 0; i < PIECE_HOLDER_HEIGHT; i++) {
        for (int j = 0; j < PIECE_HOLDER_WIDTH; j++) {
            uint8_t y = i + 1;

            if (PIECES[type][0][i][j] == 1) {
                ph->object->data[y * PIECE_HOLDER_SCREEN_OBJECT_WIDTH + (3 * j + 1)] = '[';
                ph->object->data[y * PIECE_HOLDER_SCREEN_OBJECT_WIDTH + (3 * j + 2)] = ']';
            }
            else {
                ph->object->data[y * PIECE_HOLDER_SCREEN_OBJECT_WIDTH + (3 * j + 1)] = ' ';
                ph->object->data[y * PIECE_HOLDER_SCREEN_OBJECT_WIDTH + (3 * j + 2)] = ' ';
            }
        }
    }
}


PieceType piece_holder_swap(PieceHolder *ph, PieceType type) {
    PieceType old = ph->held_piece_type;
    ph->held_piece_type = type;

    piece_holder_update(ph);
    return old;
}


void piece_holder_enable(PieceHolder *ph) {
    ph->used_hold = false;
}


void piece_holder_disable(PieceHolder *ph) {
    ph->used_hold = true;
}
