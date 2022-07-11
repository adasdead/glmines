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

#include "math/transform.h"

#include <math.h>

#include "math/matrix4.h"
#include "math/vector3.h"

mat4_t new_ortho(float left, float right,
                 float bottom, float top,
                 float near, float far)
{
    mat4_t ortho_mtrx = new_unit_matrix4();

    ortho_mtrx[0][0] = 2 / (right - left);
    ortho_mtrx[1][1] = 2 / (top - bottom);
    ortho_mtrx[2][2] = 2 / (far - near);

    ortho_mtrx[3][0] = -((right + left) / (right - left));
    ortho_mtrx[3][1] = -((top + bottom) / (top - bottom));
    ortho_mtrx[3][2] = -((far + near) / (far - near));

    return ortho_mtrx;
}

void matrix4_scale(mat4_t dest, const vec3_t vec)
{
    mat4_t scale_mtrx = new_unit_matrix4();

    scale_mtrx[0][0] *= vec.x;
    scale_mtrx[1][1] *= vec.y;
    scale_mtrx[2][2] *= vec.z;

    matrix4_mult(dest, scale_mtrx);
    matrix4_destroy(scale_mtrx);
}

void matrix4_translate(mat4_t dest, const vec3_t vec)
{
    mat4_t translate_mtrx = new_unit_matrix4();

    translate_mtrx[3][0] = vec.x;
    translate_mtrx[3][1] = vec.y;
    translate_mtrx[3][2] = vec.z;

    matrix4_mult(dest, translate_mtrx);
    matrix4_destroy(translate_mtrx);
}