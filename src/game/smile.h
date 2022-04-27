#ifndef _GAME_SMILE_H_
#define _GAME_SMILE_H_

#include "game/input.h"

#include "graphics/renderer.h"

enum smile_state
{
    SMILE_DEFAULT,
    SMILE_CLICK,
    SMILE_O,
    SMILE_DEAD,
    SMILE_COOL,
    SMILE_STATES_TOTAL
};

typedef struct
{
    int margin_top;
    int right;
    int state;
    
} smile_t;

smile_t *new_smile(int right, int margin_top, int state);

void smile_draw(const smile_t *smile, renderer_t *r);

void smile_on_mouse(smile_t *smile, mouse_event_t e);

void smile_on_click(smile_t *smile);

void smile_destroy(smile_t *smile);

#endif