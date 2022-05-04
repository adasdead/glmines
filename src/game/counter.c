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

#include "game/counter.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/resources.h"

#include "graphics/renderer.h"

#include "math/matrix4.h"
#include "math/transform.h"
#include "math/vector3.h"

#include "definitions.h"

counter_t *new_counter(int start_val, int left, int top)
{
    counter_t *counter = malloc(sizeof(counter_t));
    counter->value = start_val;
    counter->left = left;
    counter->top = top;

    return counter;
}

void counter_draw(const counter_t *c, renderer_t *r)
{
    mat4_t model = new_unit_matrix4();
    render_target_t *target;

    vec3_t size;
    size.x = COUNTER_WIDTH_F;
    size.y = COUNTER_HEIGHT_F;
    size.z = 1.0f;

    vec3_t pos;
    pos.x = (c->left - 1.7f) / size.x;
    pos.y = c->top * size.y - 0.6f;
    pos.z = size.z;

    int numbers[3] = {
        c->value / 100 % 10,
        c->value / 10  % 10,
        c->value       % 10,
    };

    if (c)
    {
        for (int i = 0; i < 3; i++)
        {
            if (c->value >= 1000)
                target = resources_get(RES_COUNTER, 9);
            else if (c->value < 0)
                target = resources_get(RES_COUNTER, 0);
            else
                target = resources_get(RES_COUNTER, numbers[i]);

            matrix4_reset(model, MATRIX4_UNIT);
            matrix4_translate(model, pos);
            matrix4_scale(model, size);

            renderer_draw(r, model, target);

            pos.x += 1.0f;
        }
    }

    matrix4_destroy(model);
}

void counter_destroy(counter_t *c)
{
    free(c);
}