#include "game/game.h"

#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    Game game;

    game_init(&game);
    return game_run(&game);
}
