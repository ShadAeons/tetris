
#include "piece_queue.h"

#include <stdio.h>
#include <stdlib.h>


void piece_queue_init(PieceQueue *pq) {
    pq->object = screen_object_create(
        PIECE_QUEUE_SCREEN_OBJECT_X, PIECE_QUEUE_SCREEN_OBJECT_Y,
        PIECE_QUEUE_SCREEN_OBJECT_WIDTH, PIECE_QUEUE_SCREEN_OBJECT_HEIGHT
    );

    piece_queue_reset(pq);
}


void piece_queue_cleanup(PieceQueue *pq) {
    screen_object_destroy(pq->object);
}


void piece_queue_reset(PieceQueue *pq) {
    pq->current = 0;
    for (int i = 0; i < PIECE_QUEUE_SIZE; i++) {
        pq->queue[i] = rand() % __PIECE_COUNT;
    }

    int counter = 0;

    for (int n = 0; n < PIECE_QUEUE_SIZE; n++) {
        for (int i = 0; i < PIECE_QUEUE_NEXT_PIECE_HEIGHT; i++) {
            pq->object->data[counter++] = '!';
            for (int j = 0; j < PIECE_QUEUE_NEXT_PIECE_WIDTH; j++) {
                pq->object->data[counter++] = ' ';
                pq->object->data[counter++] = ' ';
                pq->object->data[counter++] = '.';
            }
            pq->object->data[counter++] = '!';
        }

        counter += PIECE_QUEUE_GAP * PIECE_QUEUE_SCREEN_OBJECT_WIDTH;
    }
}


void piece_queue_update(PieceQueue *pq) {
    for (int n = 0; n < PIECE_QUEUE_SIZE; n++) {
        PieceType type = pq->queue[(pq->current + n) % PIECE_QUEUE_SIZE];
        for (int i = 0; i < PIECE_QUEUE_NEXT_PIECE_HEIGHT; i++) {
            for (int j = 0; j < PIECE_QUEUE_NEXT_PIECE_WIDTH; j++) {
                uint8_t x = j;
                uint8_t y = (i + n * (PIECE_QUEUE_NEXT_PIECE_HEIGHT + PIECE_QUEUE_GAP)) * PIECE_QUEUE_SCREEN_OBJECT_WIDTH;

                if (PIECES[type][0][i][j] == 1) {
                    pq->object->data[y + (3 * x + 1)] = '[';
                    pq->object->data[y + (3 * x + 2)] = ']';
                }
                else {
                    pq->object->data[y + (3 * x + 1)] = ' ';
                    pq->object->data[y + (3 * x + 2)] = ' ';
                }
            }
        }
    }
}


PieceType piece_queue_next(PieceQueue *pq) {
    PieceType type = pq->queue[pq->current];
    pq->queue[pq->current] = rand() % __PIECE_COUNT;
    pq->current = (pq->current + 1) % PIECE_QUEUE_SIZE;

    piece_queue_update(pq);
    return type;
}
