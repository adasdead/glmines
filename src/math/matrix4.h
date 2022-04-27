#ifndef _MATH_MATRIX4_H_
#define _MATH_MATRIX4_H_

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
void matrix4_add(mat4_t dest, const mat4_t src);
void matrix4_sub(mat4_t dest, const mat4_t src);

float *matrix4_to_array(const mat4_t mat);

void matrix4_destroy(mat4_t mat);

#endif