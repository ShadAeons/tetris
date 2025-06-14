#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include <stdbool.h>

#include "board.h"
#include "piece_queue.h"
#include "piece_holder.h"
#include "../screen/screen.h"


typedef enum {
    GAME_NONE,
    GAME_QUIT,
    GAME_PIECE_ROTATE_LEFT,
    GAME_PIECE_ROTATE_RIGHT,
    GAME_PIECE_MOVE_LEFT,
    GAME_PIECE_MOVE_RIGHT,
    GAME_PIECE_MOVE_DOWN,
    GAME_PIECE_HOLD
} GameEvent;


typedef struct {
    Screen screen;
    Board board;
    bool running;

    // Piece spawn
    Piece current_piece;
    PieceQueue piece_queue;

    // Piece holding
    PieceHolder piece_holder;

    // Game difficulty
    time_t last_tick;
    float tick_speed;
} Game;


void game_init(Game *game);
int game_run(Game *game);
void game_quit(Game *game);

// Game runtime
void game_update(Game *game);
void game_tick(Game *game);

void game_display(Game *game);

// Game events
GameEvent game_handle_key_press(int key);

// Game logic
void game_spawn_piece(Game *game, PieceType type);
void game_spawn_next_piece(Game *game);

void game_update_board(Game *game);

// Piece control
void game_piece_move(Game *game, int8_t dx, int8_t dy);
void game_piece_rotate(Game *game, uint8_t rotation);
void game_piece_hold(Game *game);

#endif  // __GAME_H__
