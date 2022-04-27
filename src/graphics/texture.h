#ifndef _GRAPHICS_TEXTURE_H_
#define _GRAPHICS_TEXTURE_H_

#include "glad/glad.h"

typedef struct
{
    GLuint id;

    int width;
    int height;
    
} tex2d_t;

tex2d_t *new_texture2d(const char *path);

void texture2d_bind(const tex2d_t *tex);

void texture2d_destroy(tex2d_t *tex);

#endif