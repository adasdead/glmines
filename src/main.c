#include "game/game.h"

int main(void)
{
    game_init();
    game_loop();
    game_free();
    return 0;
}