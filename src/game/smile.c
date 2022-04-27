#include "game/smile.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/resources.h"
#include "game/input.h"
#include "game/field.h"
#include "game/window.h"
#include "game/game.h"

#include "graphics/renderer.h"

#include "math/matrix4.h"
#include "math/transform.h"
#include "math/vector3.h"

#include "definitions.h"

extern game_difficulty_t game_diff_current;

smile_t *new_smile(int right, int margin_top, int state)
{
    smile_t *smile = malloc(sizeof(smile_t));
    smile->margin_top = margin_top;
    smile->right = right;
    smile->state = state;

    return smile;
}

void smile_draw(const smile_t *smile, renderer_t *r)
{
    float width_32 = smile->right / 2.0f;

    mat4_t model = new_unit_matrix4();
    render_target_t *target;
    vec3_t pos;

    if (smile)
    {
        pos.x = (width_32 - 1.0f) / 2.0f;
        pos.y = smile->margin_top - 0.5f;

        matrix4_translate(model, pos);
        matrix4_scale(model, new_vector3(2.0f, 2.0f, 0));

        target = resources_get(RES_SMILE, smile->state);

        renderer_draw(r, model, target);
    }

    matrix4_destroy(model);
}

void smile_on_mouse(smile_t *smile, mouse_event_t e)
{
    if (e.button == INPUT_MOUSE_LEFT)
    {
        if (smile->state == SMILE_CLICK && e.is_press)
            return;

        if (smile->state != SMILE_DEAD &&
            smile->state != SMILE_COOL)
        {
            if (e.is_press)
                smile->state = SMILE_O;
            else
                smile->state = SMILE_DEFAULT;
        }

        if (e.is_press)
        {
            double scale_factor = window_get_scale_factor();
            float cell_width_px = scale_factor * CELL_WIDTH;

            float margin_left = (smile->right / 2.0f) - 1.0f;
            
            if (e.y <= smile->margin_top * cell_width_px)
                return;

            if (e.y >= (smile->margin_top + 2.0f) * cell_width_px)
                return;

            if (e.x <= margin_left * cell_width_px)
                return;

            if (e.x >= (margin_left + 2.0f) * cell_width_px)
                return;
            
            smile_on_click(smile);
        }
    }
}

void smile_on_click(smile_t *smile)
{
    smile->state = SMILE_CLICK;
    game_new(game_diff_current);
}

void smile_destroy(smile_t *smile)
{
    if (smile)
        free(smile);
}