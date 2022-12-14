#ifndef GAME_SMILE_H
#define GAME_SMILE_H

/*
                                  The MIT License (MIT)

                               Copyright (c) 2022 adasdead

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR
    A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

#endif /* GAME_SMILE_H */