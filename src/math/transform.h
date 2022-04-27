#ifndef _MATH_TRANSFORM_H_
#define _MATH_TRANSFORM_H_

#include "math/matrix4.h"
#include "math/vector3.h"

mat4_t new_ortho(float left, float right,
                 float bottom, float top,
                 float near, float far);

void matrix4_scale(mat4_t dest, const vec3_t vec);

void matrix4_translate(mat4_t dest, const vec3_t vec);

void matrix4_rotate(mat4_t dest, float angle, const vec3_t axis);

#endif