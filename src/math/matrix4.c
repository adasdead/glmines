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

#include "math/matrix4.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MATRIX4_SIZE 4
#define MATRIX4_ARR_SIZE 16

mat4_t new_matrix4(void)
{
    mat4_t new_mtrx;
    
    new_mtrx = calloc(MATRIX4_SIZE, sizeof(mat4_t));

    for (int i = 0; i < MATRIX4_SIZE; i++)
        new_mtrx[i] = calloc(MATRIX4_SIZE, sizeof(float));

    return new_mtrx;
}

mat4_t new_unit_matrix4(void)
{
    mat4_t new_mtrx = new_matrix4();
    matrix4_reset(new_mtrx, MATRIX4_UNIT);
    return new_mtrx;
}

void matrix4_reset(mat4_t matrix, int mode)
{
    for (int i = 0; i < MATRIX4_SIZE; i++)
    {
        for (int j = 0; j < MATRIX4_SIZE; j++)
            matrix[i][j] = 0.0f;
    }
    
    if (mode == MATRIX4_UNIT)
    {
        for (int i = 0; i < MATRIX4_SIZE; i++)
            matrix[i][i] = 1.0f;
    }
}

void matrix4_copy(mat4_t dest, const mat4_t src)
{
    for (int i = 0; i < MATRIX4_SIZE; i++)
        memcpy(dest[i], src[i], MATRIX4_SIZE * sizeof(float));
}

void matrix4_mult(mat4_t dest, const mat4_t src)
{
    mat4_t temp_mtrx = new_matrix4();

    for (int i = 0; i < MATRIX4_SIZE; i++)
    {
        for (int j = 0; j < MATRIX4_SIZE; j++)
        {
            temp_mtrx[i][j] = 0.0f;

            for (int k = 0; k < MATRIX4_SIZE; k++)
                temp_mtrx[i][j] += dest[i][k] * src[k][j];
        }
    }

    matrix4_copy(dest, temp_mtrx);
    matrix4_destroy(temp_mtrx);
}

float *matrix4_to_array(const mat4_t mat)
{
    float *array;
    
    array = malloc(MATRIX4_ARR_SIZE * sizeof(float));
    
    int arr_index = 0;

    for (int i = 0; i < MATRIX4_SIZE; i++)
    {
        for (int j = 0; j < MATRIX4_SIZE; j++)
        {
            array[arr_index++] = mat[i][j];
        }
    }
    
    return array;
}

void matrix4_destroy(mat4_t mat)
{
    for (int i = 0; i < MATRIX4_SIZE; i++)
        free(mat[i]);

    free(mat);
}