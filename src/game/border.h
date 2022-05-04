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

#ifndef GAME_BORDER_H
#define GAME_BORDER_H

#include "game/field.h"

enum border_direction
{
    BORDER_DIR_NW,
    BORDER_DIR_NE,
    BORDER_DIR_SE,
    BORDER_DIR_SW,
    BORDER_DIR_N,
    BORDER_DIR_E,
    BORDER_DIR_S,
    BORDER_DIR_W,
    BORDER_DIR_S_W,
    BORDER_DIR_S_E,
    BORDER_DIR_TOTAL
};

void border_draw(renderer_t *r, const field_t *field);

void border_draw_separator(renderer_t *r, int bottom, int right);
void border_draw_edges(renderer_t *r, int bottom, int right);
void border_draw_corners(renderer_t *r, int bottom, int right);

#endif /* GAME_BORDER_H */