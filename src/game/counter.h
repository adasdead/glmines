#ifndef _GAME_COUNTER_H_
#define _GAME_COUNTER_H_

#include "graphics/renderer.h"

typedef struct
{
    int left, top;
    int value;

} counter_t;

counter_t *new_counter(int start_val, int left, int top);
void counter_draw(const counter_t *c, renderer_t *r);
void counter_destroy(counter_t *c);

#endif