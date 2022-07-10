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

#include "game/game.h"

#include <stdio.h>
#include <time.h>

#include "game/border.h"
#include "game/field.h"
#include "game/window.h"
#include "game/input.h"
#include "game/smile.h"
#include "game/resources.h"
#include "game/counter.h"

#include "graphics/renderer.h"

#include "math/matrix4.h"
#include "math/transform.h"

#include "definitions.h"

renderer_t                  *game_renderer;
mat4_t                       game_projection;

field_t                     *game_field;
smile_t                     *game_smile;

counter_t                   *game_timer;
counter_t                   *game_mines_counter;

int                          game_state = GAME_STATE_IDLE;

int                          game_start_time;

game_difficulty_t            game_diff_current;

game_difficulty_t            game_diff[3] = {

    { GAME_DIF_BEGGINER,      9,  9, 10,},
    { GAME_DIF_INTERMEDIATE, 16, 16, 40 },
    { GAME_DIF_EXPERT,       30, 16, 99 }

};

void game_init(int argc, char **argv)
{
    window_create(WINDOW_NAME, WINDOW_BASE_WIDTH,
                  WINDOW_BASE_HEIGHT);

    input_mouse_callback(game_on_mouse);
    input_key_callback(game_on_key);
    
    resources_load_all(argc, argv);
    
    game_projection = new_matrix4();
    game_renderer = new_renderer(&game_projection);

    game_mines_counter = new_counter(0, 3, 1);
    game_timer = new_counter(0, 0, 1);

    game_new(game_diff[GAME_DIF_BEGGINER]);
}

void game_loop(void)
{
    while (window_is_opened())
    {
        input_handle();

        window_clear(0.755f, 0.755f, 0.755f);

        border_draw(game_renderer, game_field);
        field_draw(game_field, game_renderer);
        smile_draw(game_smile, game_renderer);

        if (game_state == GAME_STATE_STARTED)
        {
            if (!game_start_time)
                game_start_time = time(NULL);
            
            game_timer->value = time(NULL) - game_start_time;
        }

        counter_draw(game_mines_counter, game_renderer);
        counter_draw(game_timer, game_renderer);

        window_swap_buffers();
    }
}

void game_new(game_difficulty_t diff)
{
    double scale = window_get_scale_factor();

    int projection_right  = diff.field_width;
    projection_right += FIELD_MARGIN_LEFT;
    projection_right += FIELD_MARGIN_RIGHT;

    int projection_bottom = diff.field_height;
    projection_bottom += FIELD_MARGIN_TOP;
    projection_bottom += FIELD_MARGIN_BOTTOM;

    int window_base_width  = projection_right  * CELL_WIDTH;
    int window_base_height = projection_bottom * CELL_WIDTH;

    int window_width  = window_base_width * scale;
    int window_height = window_base_height * scale;

    window_resize(window_width, window_height);

    matrix4_destroy(game_projection);

    game_projection = new_ortho(0.0f, projection_right,
                                projection_bottom, 0.0f,
                                -1.0f, 1.0f);

    if (!game_smile)
    {
        game_smile = new_smile(projection_right,
                               SMILE_MARGIN_TOP,
                               SMILE_DEFAULT);
    }

    game_smile->right = projection_right;

    field_destroy(game_field);

    game_field = new_field(diff.field_width,
                           diff.field_height,
                           diff.mines_count);

    game_start_time = 0;

    game_timer->left = projection_right - 2;
    game_timer->value = game_start_time;

    game_mines_counter->value = diff.mines_count;

    game_set_state(GAME_STATE_IDLE);

    game_diff_current = diff;
}

void game_on_mouse(mouse_event_t e)
{
    field_on_mouse(game_field, e);
    smile_on_mouse(game_smile, e);
}

void game_on_key(key_event_t e)
{
    if (e.is_press)
    {
        if (e.button == INPUT_KEY_ESC)
        {
            window_close();
            game_free();
        }

        if (e.button == INPUT_KEY_D)
        {
            game_difficulty_t diff;

            switch (game_diff_current.id)
            {
            case GAME_DIF_BEGGINER:
                diff = game_diff[GAME_DIF_INTERMEDIATE];
                break;
            
            case GAME_DIF_INTERMEDIATE:
                diff = game_diff[GAME_DIF_EXPERT];
                break;

            case GAME_DIF_EXPERT:
                diff = game_diff[GAME_DIF_BEGGINER];
                break;
            }

            game_smile->state = SMILE_DEFAULT;

            game_new(diff);
        }
    }
}

void game_set_state(int state)
{
    game_state = state;

    switch (state)
    {
    case GAME_STATE_LOSE:
        game_smile->state = SMILE_DEAD;
        break;
    
    case GAME_STATE_WON:
        game_smile->state = SMILE_COOL;
        break;
    }
}

int game_get_state(void)
{
    return game_state;
}

void game_free(void)
{
    renderer_destroy(game_renderer);
    matrix4_destroy(game_projection);

    counter_destroy(game_mines_counter);
    counter_destroy(game_timer);

    field_destroy(game_field);
    smile_destroy(game_smile);

    resources_free();
    window_free();
}