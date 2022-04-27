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

void matrix4_add(mat4_t dest, const mat4_t src)
{
    for (int i = 0; i < MATRIX4_SIZE; i++)
    {
        for (int j = 0; j < MATRIX4_SIZE; j++)
            dest[i][j] += src[i][j];
    }
}

void matrix4_sub(mat4_t dest, const mat4_t src)
{
    for (int i = 0; i < MATRIX4_SIZE; i++)
    {
        for (int j = 0; j < MATRIX4_SIZE; j++)
            dest[i][j] -= src[i][j];
    }
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