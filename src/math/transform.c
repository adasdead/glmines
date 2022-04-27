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

void matrix4_rotate(mat4_t dest, float angle,
                    const vec3_t axis)
{
    mat4_t rotate_mtrx = new_unit_matrix4();

    float cos_0 = cosf(angle), sin_0 = sinf(angle);

    rotate_mtrx[0][0] = cos_0 + powf(axis.x, 2.0f) * (1 - cos_0);
    rotate_mtrx[0][1] = axis.y * axis.x * (1 - cos_0) + axis.z * sin_0;
    rotate_mtrx[0][2] = axis.z * axis.x * (1 - cos_0) - axis.y * sin_0;

    rotate_mtrx[1][0] = axis.x * axis.y * (1 - cos_0) - axis.z * sin_0;
    rotate_mtrx[1][1] = cos_0 + powf(axis.y, 2.0f) * (1 - cos_0);
    rotate_mtrx[1][2] = axis.z * axis.y * (1 - cos_0) + axis.x * sin_0;

    rotate_mtrx[2][0] = axis.x * axis.z * (1 - cos_0) + axis.y * sin_0;
    rotate_mtrx[2][1] = axis.y * axis.z * (1 - cos_0) - axis.x * sin_0;
    rotate_mtrx[2][2] = cos_0 + powf(axis.z, 2.0f) * (1 - cos_0);

    matrix4_mult(dest, rotate_mtrx);
    matrix4_destroy(rotate_mtrx);
}