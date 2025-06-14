#ifndef __PIECE_H__
#define __PIECE_H__

#include <stdint.h>


#define PIECE_BLOCKS 4
#define PIECE_ROTATIONS 4
#define PIECE_POSSIBLE_ROTATIONS PIECE_ROTATIONS * 2
#define PIECE_WALL_DATA_TESTS 5


typedef enum {
    PIECE_I,
    PIECE_J,
    PIECE_L,
    PIECE_O,
    PIECE_S,
    PIECE_T,
    PIECE_Z,
    __PIECE_COUNT
} PieceType;


typedef struct {
    PieceType type;
    uint8_t position[2];
    uint8_t rotation;
} Piece;


extern uint8_t PIECES[__PIECE_COUNT][4][PIECE_BLOCKS][PIECE_BLOCKS];
extern uint8_t PIECE_SPAWNS[__PIECE_COUNT][2];

// Wall data test cases
extern int8_t PIECE_I_WALL_KICK_DATA[PIECE_POSSIBLE_ROTATIONS][PIECE_WALL_DATA_TESTS][2];
extern int8_t PIECE_JLTSZ_WALL_KICK_DATA[PIECE_POSSIBLE_ROTATIONS][PIECE_WALL_DATA_TESTS][2];


int8_t get_wall_data_tests_index(uint8_t old_rot, uint8_t new_rot);

#endif  // __PIECE_H__
