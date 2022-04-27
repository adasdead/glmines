#ifndef _GRAPHICS_SHADER_H_
#define _GRAPHICS_SHADER_H_

#include "glad/glad.h"

#include "math/vector3.h"
#include "math/matrix4.h"

typedef GLuint shader_t;

shader_t new_shader(const char *vert_path,
                    const char *frag_path);

void shader_use(shader_t shader);

void shader_set_uniform_1i(shader_t shader,
                           const char *name,
                           int val);

void shader_set_uniform_1f(shader_t shader,
                           const char *name,
                           float val);

void shader_set_uniform_3fv(shader_t shader,
                            const char *name,
                            vec3_t vec);

void shader_set_uniform_m4fv(shader_t shader,
                             const char *name,
                             mat4_t mat);

void shader_destroy(shader_t shader);

#endif