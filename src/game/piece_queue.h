#ifndef __PIECE_QUEUE_H__
#define __PIECE_QUEUE_H__

#include "piece.h"
#include "board.h"
#include "../screen/screen_object.h"


#define PIECE_QUEUE_SIZE 3
#define PIECE_QUEUE_NEXT_PIECE_WIDTH PIECE_BLOCKS
#define PIECE_QUEUE_NEXT_PIECE_HEIGHT 2
#define PIECE_QUEUE_MARGIN 6
#define PIECE_QUEUE_GAP 1
#define PIECE_QUEUE_SCREEN_OBJECT_WIDTH (PIECE_QUEUE_NEXT_PIECE_WIDTH * 3 + 2)  // * 3 +  because of |[].|
#define PIECE_QUEUE_SCREEN_OBJECT_HEIGHT (PIECE_QUEUE_NEXT_PIECE_HEIGHT + PIECE_QUEUE_GAP) * PIECE_QUEUE_SIZE
#define PIECE_QUEUE_SCREEN_OBJECT_X (BOARD_SCREEN_OBJECT_X + BOARD_WIDTH + PIECE_QUEUE_MARGIN)
#define PIECE_QUEUE_SCREEN_OBJECT_Y PIECE_QUEUE_GAP


typedef struct {
    ScreenObject *object;
    PieceType queue[PIECE_QUEUE_SIZE];
    uint8_t current;
} PieceQueue;


void piece_queue_init(PieceQueue *pq);
void piece_queue_cleanup(PieceQueue *pq);

void piece_queue_reset(PieceQueue *pq);

void piece_queue_update(PieceQueue *pq);

PieceType piece_queue_next(PieceQueue *pq);

#endif  // __PIECE_QUEUE_H__
