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

#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "graphics/renderer.h"

#include "game/input.h"
#include "game/cell.h"

typedef struct
{
    int width, height;
    int mines_count;

    cell_t **cells;

} field_t;


field_t *new_field(int width, int height, int mines_count);

void field_check_won(field_t *field);

void field_check_lost(field_t *field, int clck_x, int clck_y);

void field_generate(field_t *field, int clck_x, int clck_y);

void field_draw(const field_t *field, renderer_t *r);

void field_on_mouse(field_t *field, mouse_event_t e);

cell_t *field_get_cell(field_t *field, int cell_x, int cell_y);

cell_t *field_reveal_cell(field_t *field, int cell_x, int cell_y);

int field_get_adjacent_mines(field_t *field, int cell_x, int cell_y);

void field_destroy(field_t *field);

#endif /* GAME_FIELD_H */