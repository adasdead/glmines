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

#ifndef GAME_INPUT_H
#define GAME_INPUT_H

enum input_mouse_button
{
    INPUT_MOUSE_RIGHT,
    INPUT_MOUSE_LEFT
};

enum input_key_button
{
    INPUT_KEY_ESC,
    INPUT_KEY_D
};

typedef struct
{
    int button;
    int is_press;

} key_event_t;

typedef struct
{
    double x, y;
    int button;
    int is_press;

} mouse_event_t;

typedef void (*input_key_fn_t)(key_event_t e);
typedef void (*input_mouse_fn_t)(mouse_event_t e);

void input_mouse_callback(input_mouse_fn_t fn);
void input_key_callback(input_key_fn_t fn);

void input_handle(void);

#endif /* GAME_INPUT_H */