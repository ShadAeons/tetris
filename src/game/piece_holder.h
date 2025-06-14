#ifndef __PIECE_HOLDER_H__
#define __PIECE_HOLDER_H__

#include <stdbool.h>

#include "piece.h"
#include "../screen/screen_object.h"


#define PIECE_HOLDER_WIDTH PIECE_BLOCKS
#define PIECE_HOLDER_HEIGHT 2
#define PIECE_HOLDER_SCREEN_OBJECT_X 4
#define PIECE_HOLDER_SCREEN_OBJECT_Y 1
#define PIECE_HOLDER_SCREEN_OBJECT_WIDTH (3 * PIECE_HOLDER_WIDTH + 2)
#define PIECE_HOLDER_SCREEN_OBJECT_HEIGHT (PIECE_HOLDER_HEIGHT + 2)


typedef struct {
    ScreenObject *object;
    PieceType held_piece_type;
    bool used_hold;
} PieceHolder;


void piece_holder_init(PieceHolder *ph);
void piece_holder_cleanup(PieceHolder *ph);

void piece_holder_reset(PieceHolder *ph);

void piece_holder_update(PieceHolder *ph);

PieceType piece_holder_swap(PieceHolder *ph, PieceType type);
void piece_holder_enable(PieceHolder *ph);
void piece_holder_disable(PieceHolder *ph);


#endif  // __PIECE_HOLDER_H__
