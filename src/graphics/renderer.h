#ifndef _GRAPHICS_RENDER_H_
#define _GRAPHICS_RENDER_H_

#include "graphics/shader.h"
#include "graphics/texture.h"

#include "math/matrix4.h"

typedef struct
{
    shader_t shader;
    tex2d_t *texture;

} render_target_t;

typedef struct
{
    GLuint VAO, VBO;
    mat4_t *projection;

} renderer_t;

renderer_t *new_renderer(mat4_t *projection);

void renderer_draw(renderer_t *r, mat4_t model,
                   render_target_t *target);

void renderer_destroy(renderer_t *r);

#endif