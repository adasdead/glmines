#ifndef _MATH_VECTOR3_H_
#define _MATH_VECTOR3_H_

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

#endif