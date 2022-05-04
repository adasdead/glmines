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

#include "game/border.h"

#include "game/resources.h"

#include "graphics/renderer.h"

#include "math/matrix4.h"
#include "math/transform.h"

#include "definitions.h"

void border_draw(renderer_t *r, const field_t *field)
{
    int border_bottom = field->height + FIELD_MARGIN_TOP;
    int border_right  = field->width + FIELD_MARGIN_LEFT;

    border_draw_edges(r, border_bottom, border_right);
    border_draw_separator(r, border_bottom, border_right);
    border_draw_corners(r, border_bottom, border_right);
}

void border_draw_separator(renderer_t *r, int bottom, int right)
{
    render_target_t *target;

    mat4_t model = new_unit_matrix4();
    vec3_t pos;

    int sep_margin = BORDER_SEP_MARGIN_TOP;
    
    target = resources_get(RES_BORDER, BORDER_DIR_N);

    for (int i = 0; i < right - 1; i++)
    {
        pos = new_vector3(i + 1, sep_margin, 0.0f);
        matrix4_reset(model, MATRIX4_UNIT);
        matrix4_translate(model, pos);

        renderer_draw(r, model, target);
    }

    for (int j = BORDER_DIR_S_W - 1; j <= BORDER_DIR_S_E; j++)
    {
        target = resources_get(RES_BORDER, j);

        switch (j)
        {
        case BORDER_DIR_S_W:
            pos = new_vector3(0.0f, sep_margin, 0.0f);
            break;
        
        case BORDER_DIR_S_E:
            pos = new_vector3(right, sep_margin, 0.0f);
            break;
        }

        matrix4_translate(model, pos);
        renderer_draw(r, model, target);
        matrix4_reset(model, MATRIX4_UNIT);
    }

    matrix4_destroy(model);
}

void border_draw_edges(renderer_t *r, int bottom, int right)
{
    render_target_t *N, *E, *S, *W;
    N = resources_get(RES_BORDER, BORDER_DIR_N);
    E = resources_get(RES_BORDER, BORDER_DIR_E);
    S = resources_get(RES_BORDER, BORDER_DIR_S);
    W = resources_get(RES_BORDER, BORDER_DIR_W);

    mat4_t model = new_unit_matrix4();
    vec3_t pos;

    for (int i = 0; i < right - 1; i++)
    {
        pos = new_vector3(i + 1, 0.0f, 0.0f);
        matrix4_reset(model, MATRIX4_UNIT);
        matrix4_translate(model, pos);

        renderer_draw(r, model, N);

        pos = new_vector3(i + 1, bottom, 0.0f);
        matrix4_reset(model, MATRIX4_UNIT);
        matrix4_translate(model, pos);

        renderer_draw(r, model, S);
    }

    for (int j = 0; j < bottom - 1; j++)
    {
        pos = new_vector3(0.0f, j + 1, 0.0f);
        matrix4_reset(model, MATRIX4_UNIT);
        matrix4_translate(model, pos);

        renderer_draw(r, model, W);

        pos = new_vector3(right, j + 1, 0.0f);
        matrix4_reset(model, MATRIX4_UNIT);
        matrix4_translate(model, pos);

        renderer_draw(r, model, E);
    }

    matrix4_destroy(model);
}

void border_draw_corners(renderer_t *r, int bottom, int right)
{
    render_target_t *target;
    
    mat4_t model = new_unit_matrix4();
    vec3_t pos;

    for (int i = 0; i < 4; i++)
    {
        target = resources_get(RES_BORDER, i);

        switch (i)
        {
        case BORDER_DIR_NW:
            pos = new_vector3(0.0f, 0.0f, 0.0f);
            break;
        
        case BORDER_DIR_NE:
            pos = new_vector3(right, 0.0f, 0.0f);
            break;
        
        case BORDER_DIR_SE:
            pos = new_vector3(right, bottom, 0.0f);
            break;
        
        case BORDER_DIR_SW:
            pos = new_vector3(0.0f, bottom, 0.0f);
            break;
        }

        matrix4_translate(model, pos);
        renderer_draw(r, model, target);
        matrix4_reset(model, MATRIX4_UNIT);
    }

    matrix4_destroy(model);
}