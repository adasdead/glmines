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

#ifndef MATH_MATRIX4_H
#define MATH_MATRIX4_H

enum matrix4_reset_mode
{
    MATRIX4_DEFAULT,
    MATRIX4_UNIT
};

typedef float** mat4_t;

mat4_t new_matrix4(void);
mat4_t new_unit_matrix4(void);

void matrix4_reset(mat4_t matrix, int mode);

void matrix4_copy(mat4_t dest, const mat4_t src);

void matrix4_mult(mat4_t dest, const mat4_t src);

float *matrix4_to_array(const mat4_t mat);

void matrix4_destroy(mat4_t mat);

#endif /* MATH_MATRIX4_H */