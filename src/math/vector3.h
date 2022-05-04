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

#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

typedef struct
{
    float x;
    float y;
    float z;

} vec3_t;

vec3_t new_vector3(float x, float y, float z);

void vector3_copy(vec3_t *dest, const vec3_t src);

void vector3_mult(vec3_t *dest, const vec3_t src);
void vector3_add(vec3_t *dest, const vec3_t src);
void vector3_sub(vec3_t *dest, const vec3_t src);

float vector3_dot(const vec3_t vec1, const vec3_t vec2);

void vector3_cross(vec3_t *dest, const vec3_t src);

void vector3_normalize(vec3_t *dest);

#endif /* MATH_VECTOR3_H */