#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include "game/input.h"

enum game_difficulty
{
    GAME_DIF_BEGGINER,
    GAME_DIF_INTERMEDIATE,
    GAME_DIF_EXPERT
};

typedef struct
{
    int id;
    
    int field_width;
    int field_height;
    int mines_count;

} game_difficulty_t;

enum game_state
{
    GAME_STATE_STARTED,
    GAME_STATE_IDLE,
    GAME_STATE_LOSE,
    GAME_STATE_WON
};

void game_init(void);
void game_loop(void);
void game_new(game_difficulty_t diff);
void game_on_mouse(mouse_event_t e);
void game_on_key(key_event_t e);
void game_set_state(int state);
int game_get_state(void);
void game_free(void);

#endif