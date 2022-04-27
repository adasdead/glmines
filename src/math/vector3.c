#include "math/vector3.h"

#include <math.h>

vec3_t new_vector3(float x, float y, float z)
{
    return (vec3_t) { x, y, z };
}

void vector3_copy(vec3_t *dest, const vec3_t src)
{
    dest->x = src.x;
    dest->y = src.y;
    dest->z = src.z;
}

void vector3_mult(vec3_t *dest, const vec3_t src)
{
    dest->x = dest->x * src.x;
    dest->y = dest->y * src.y;
    dest->z = dest->z * src.z;
}

void vector3_add(vec3_t *dest, const vec3_t src)
{
    dest->x = dest->x + src.x;
    dest->y = dest->y + src.y;
    dest->z = dest->z + src.z;
}

void vector3_sub(vec3_t *dest, const vec3_t src)
{
    dest->x = dest->x - src.x;
    dest->y = dest->y - src.y;
    dest->z = dest->z - src.z;
}

float vector3_dot(const vec3_t vec1,
                  const vec3_t vec2)
{
    return vec1.x * vec2.x +
           vec1.y * vec2.y +
           vec1.z * vec2.z;
}

void vector3_cross(vec3_t *dest, const vec3_t src)
{
    float x = dest->x,
          y = dest->y,
          z = dest->z;
    
    dest->x = y * src.z - z * src.y;
    dest->y = z * src.x - x * src.z;
    dest->z = x * src.y - y * src.x;
}

void vector3_normalize(vec3_t *dest)
{
    float n = powf(dest->x, 2.0f) +
              powf(dest->y, 2.0f) +
              powf(dest->z, 2.0f);

    if (n > 0)
    {
        float factor = 1 / sqrtf(n);
        
        dest->x *= factor;
        dest->y *= factor;
        dest->z *= factor;
    }
}