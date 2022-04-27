#include "graphics/renderer.h"

#include <stdio.h>
#include <stdlib.h>

#include "math/matrix4.h"

#include "glad/glad.h"

static GLfloat render_vertices[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
};

renderer_t *new_renderer(mat4_t *projection)
{
    renderer_t *renderer = malloc(sizeof(renderer_t));
    renderer->projection = projection;

    glGenVertexArrays(1, &renderer->VAO);
    glGenBuffers(1, &renderer->VBO);

    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(render_vertices),
                 render_vertices, GL_STATIC_DRAW);

    glBindVertexArray(renderer->VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
                          4 * sizeof(float), NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return renderer;
}

void renderer_draw(renderer_t *r, mat4_t model,
                   render_target_t *target)
{
    shader_use(target->shader);

    shader_set_uniform_m4fv(target->shader, "model", model);
    shader_set_uniform_m4fv(target->shader, "projection",
                            *r->projection);

    if (target->texture)
        texture2d_bind(target->texture);
    
    glBindVertexArray(r->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void renderer_destroy(renderer_t *r)
{
    glDeleteVertexArrays(1, &r->VAO);
    glDeleteBuffers(1, &r->VBO);

    free(r);
}