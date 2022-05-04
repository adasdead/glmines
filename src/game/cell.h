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

#ifndef GAME_CELL_H
#define GAME_CELL_H

enum cell_state
{
    CELL_STATE_OPENED,
    CELL_STATE_CLOSED,
    CELL_STATE_FLAGGED,
    CELL_STATE_QUESTIONED,
    CELL_STATES_TOTAL
};

enum cell_type
{
    CELL_TYPE_0,
    CELL_TYPE_1,
    CELL_TYPE_2,
    CELL_TYPE_3,
    CELL_TYPE_4,
    CELL_TYPE_5,
    CELL_TYPE_6,
    CELL_TYPE_7,
    CELL_TYPE_8,
    CELL_TYPE_BOMB,
    CELL_TYPE_NO_BOMB,
    CELL_TYPE_BOMB_E,
    CELL_TYPE_CLOSE,
    CELL_TYPE_QUESTION,
    CELL_TYPE_FLAG,
    CELL_TYPES_TOTAL
};

typedef struct
{
    int type;
    int state;

} cell_t;

#endif /* GAME_CELL_H */