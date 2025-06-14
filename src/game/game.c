#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


void game_init(Game *game) {
    screen_init(&game->screen);

    board_init(&game->board);

    game->last_tick     = time(NULL);
    game->tick_speed    = 1.0;
    game->running       = false;

    // Add random pieces to the queue
    piece_queue_init(&game->piece_queue);

    piece_holder_init(&game->piece_holder);

    game_spawn_next_piece(game);
}


int game_run(Game *game) {
    game_display(game);

    game->running = true;
    while (game->running) {
        game_update(game);

        time_t now = time(NULL);
        if (now - game->last_tick >= game->tick_speed) {
            game_tick(game);
            game->last_tick = now;
        }
    }

    game_quit(game);
    return 0;
}


void game_quit(Game *game) {
    game->running = false;
    fputs("\n\nPress ENTER to exit...\n", stdout);
    getchar();

    piece_queue_cleanup(&game->piece_queue);
    piece_holder_cleanup(&game->piece_holder);
    board_cleanup(&game->board);
    screen_exit(&game->screen);
}


void game_update(Game *game) {
    if (_kbhit()) {
        int key = _getch();

        GameEvent event = game_handle_key_press(key);
        if (event == GAME_QUIT) {
            game->running = false;
            return;
        }

        if (event != GAME_NONE) {
            if (event == GAME_PIECE_ROTATE_LEFT) {
                uint8_t rotation = (game->current_piece.rotation + 3) % 4;
                game_piece_rotate(game, rotation);
            }

            if (event == GAME_PIECE_ROTATE_RIGHT) {
                uint8_t rotation = (game->current_piece.rotation + 1) % 4;
                game_piece_rotate(game, rotation);
            }

            if (event == GAME_PIECE_MOVE_LEFT) {
                game_piece_move(game, -1, 0);
            }

            if (event == GAME_PIECE_MOVE_RIGHT) {
                game_piece_move(game, 1, 0);
            }

            if (event == GAME_PIECE_MOVE_DOWN) {
                game_piece_move(game, 0, 1);
                game->last_tick = time(NULL);
            }

            if (event == GAME_PIECE_HOLD) {
                if (!game->piece_holder.used_hold) {
                    PieceType swapped = piece_holder_swap(&game->piece_holder, game->current_piece.type);
                    if (swapped == __PIECE_COUNT) {
                        game_spawn_next_piece(game);
                    } else {
                        game_spawn_piece(game, swapped);
                    }

                    piece_holder_disable(&game->piece_holder);
                }
            }

            game_display(game);
        }
    }
}


void game_tick(Game *game) {
    game_piece_move(game, 0, 1);
    game_display(game);
}


void game_display(Game *game) {
    board_draw(&game->board, &game->current_piece);
    screen_draw(&game->screen, game->piece_queue.object);
    screen_draw(&game->screen, game->piece_holder.object);
    screen_draw(&game->screen, game->board.object);
    screen_display(&game->screen);
}


GameEvent game_handle_key_press(int key) {
    switch (key) {
        case 0:
        case 224:
            int arrow = _getch();
            switch (arrow) {
                case 75:
                    return GAME_PIECE_ROTATE_LEFT;
                
                case 77:
                    return GAME_PIECE_ROTATE_RIGHT;
            }
            break;

        case 27:
            return GAME_QUIT;

        case 'a':
            return GAME_PIECE_MOVE_LEFT;

        case 'd':
            return GAME_PIECE_MOVE_RIGHT;

        case 's':
            return GAME_PIECE_MOVE_DOWN;

        case 'q':
            return GAME_PIECE_HOLD;
    }

    return GAME_NONE;
}


void game_spawn_piece(Game *game, PieceType type) {
    game->current_piece.type = type;
    game->current_piece.rotation = 0;
    game->current_piece.position[0] = PIECE_SPAWNS[type][0];
    game->current_piece.position[1] = PIECE_SPAWNS[type][1];

    if (!board_is_possible_move(&game->board, &game->current_piece, 0, 0, 0)) {
        game->running = false;
    }
}


void game_spawn_next_piece(Game *game) {
    game_spawn_piece(game, piece_queue_next(&game->piece_queue));
}


void game_update_board(Game *game) {
    board_update(&game->board, &game->current_piece);

    piece_holder_enable(&game->piece_holder);

    board_clear_lines(&game->board);
    game_spawn_next_piece(game);
}


void game_piece_move(Game *game, int8_t dx, int8_t dy) {
    if (board_is_possible_move(&game->board, &game->current_piece, dx, dy, game->current_piece.rotation)) {
        game->current_piece.position[0] += dx;
        game->current_piece.position[1] += dy;
    } else if (dy > 0) {
        game_update_board(game);
    }
}


void game_piece_rotate(Game *game, uint8_t rotation) {
    int8_t wall_data_index = get_wall_data_tests_index(game->current_piece.rotation, rotation);
    
    if (game->current_piece.type == PIECE_I) {
        for (int i = 0; i < PIECE_WALL_DATA_TESTS; i++) {
            int8_t dx = PIECE_I_WALL_KICK_DATA[wall_data_index][i][0];
            int8_t dy = PIECE_I_WALL_KICK_DATA[wall_data_index][i][1];

            if (board_is_possible_move(&game->board, &game->current_piece, dx, dy, rotation)) {
                game->current_piece.rotation = rotation;
                game->current_piece.position[0] += dx;
                game->current_piece.position[1] += dy;
                break;
            }
        }
    } else {
        for (int i = 0; i < PIECE_WALL_DATA_TESTS; i++) {
            int8_t dx = PIECE_JLTSZ_WALL_KICK_DATA[wall_data_index][i][0];
            int8_t dy = PIECE_JLTSZ_WALL_KICK_DATA[wall_data_index][i][1];

            if (board_is_possible_move(&game->board, &game->current_piece, dx, dy, rotation)) {
                game->current_piece.rotation = rotation;
                game->current_piece.position[0] += dx;
                game->current_piece.position[1] += dy;
                break;
            }
        }
    }
}
