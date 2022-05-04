/*
                                  The MIT License (MIT)

                               Copyright (c) 2022 adasdead

    Permission is hereby granted, free of charge, to any person obtaining a copy of this
    software and associated documentation files (the "Software"), to deal in the Software
    without restriction, including without limitation the rights to use, copy, modify,
    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR
    A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "graphics/texture.h"

#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define IMAGE_LOAD_ERR_FMT "Cannot load \"%s\" image\n"

tex2d_t *new_texture2d(const char *path)
{
    GLubyte *bytes;
    int width, height;
    tex2d_t *new_texture;

    new_texture = malloc(sizeof(tex2d_t));

    bytes = stbi_load(path, &width, &height,
                      NULL, STBI_rgb_alpha);
    
    if (!bytes) {
        fprintf(stderr, IMAGE_LOAD_ERR_FMT, path);
        return NULL;
    }

    new_texture->height = height;
    new_texture->width = width;

    glGenTextures(1, &new_texture->id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, new_texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, bytes);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(bytes);
    return new_texture;
}

void texture2d_bind(const tex2d_t *tex)
{
    if (tex)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex->id);
    }
}

void texture2d_destroy(tex2d_t *tex)
{
    free(tex);
}