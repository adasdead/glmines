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

#include "graphics/shader.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "glad/glad.h"

#include "math/vector3.h"
#include "math/matrix4.h"

#define IO_WARN_FMT      "IO Error / %s: %s\n"
#define SHADER_WARN_FMT  "OpenGL shader error / %s:\n %s\n"
#define PROGRAM_WARN_FMT "OpenGL shader program error:\n %s\n"

int _shader_check_errors(GLuint id, const char *file_path);
char *_shader_read_file(const char *file_path);

shader_t new_shader(const char *vert_path,
                    const char *frag_path)
{
    char *vertex_source = _shader_read_file(vert_path);
    char *fragment_source = _shader_read_file(frag_path);

    if (!(vertex_source && fragment_source))
        return 0;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1,
                   (const char**) &vertex_source,
                   NULL);

    glCompileShader(vertex_shader);

    if (!_shader_check_errors(vertex_shader, vert_path))
        return 0;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1,
                   (const char**) &fragment_source,
                   NULL);
    
    glCompileShader(fragment_shader);

    if (!_shader_check_errors(fragment_shader, frag_path))
        return 0;

    GLuint program = glCreateProgram();
    glAttachShader(program, fragment_shader);
    glAttachShader(program, vertex_shader);
    glLinkProgram(program);

    if (!_shader_check_errors(program, NULL))
        return 0;

    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);

    free(fragment_source);
    free(vertex_source);

    return program;
}

void shader_use(shader_t shader)
{
    glUseProgram(shader);
}

void shader_set_uniform_1i(shader_t shader,
                           const char *name,
                           int val)
{
    GLint loc = glGetUniformLocation(shader, name);
    glUniform1i(loc, val);
}

void shader_set_uniform_1f(shader_t shader,
                           const char *name,
                           float val)
{
    GLint loc = glGetUniformLocation(shader, name);
    glUniform1f(loc, val);
}

void shader_set_uniform_3fv(shader_t shader,
                            const char *name,
                            vec3_t vec)
{
    GLint loc = glGetUniformLocation(shader, name);
    glUniform3f(loc, vec.x, vec.y, vec.z);
}

void shader_set_uniform_m4fv(shader_t shader,
                             const char *name,
                             mat4_t mat)
{
    GLfloat *mat_data = matrix4_to_array(mat);
    GLint loc = glGetUniformLocation(shader, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat_data);
    free(mat_data);
}

void shader_destroy(shader_t shader)
{
    glDeleteProgram(shader);
}

/////////////////////////////////////////////////////////

int _shader_check_errors(GLuint id, const char *file_path)
{
    char info_log[1024];
    int status;

    if (glIsShader(id))
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            glGetShaderInfoLog(id, 1024, NULL, info_log);
            fprintf(stderr, SHADER_WARN_FMT, file_path, info_log);
            return 0;
        }
    }
    else if (glIsProgram(id))
    {
        glGetProgramiv(id, GL_LINK_STATUS, &status);

        if (!status)
        {
            glGetProgramInfoLog(id, 1024, NULL, info_log);
            fprintf(stderr, PROGRAM_WARN_FMT, info_log);
            return 0;
        }
    }
    else
        return 0;

    return 1;
}

char *_shader_read_file(const char *file_path)
{
    errno = 0;
    FILE *fp = fopen(file_path, "r");

    if (!fp)
    {
        fprintf(stderr, IO_WARN_FMT, file_path, strerror(errno));
        return NULL;
    }
    
    fseek(fp, 0L, SEEK_END);

    size_t size = ftell(fp);
    char *buffer = calloc(size, sizeof(char));
    rewind(fp);

    fread(buffer, size, sizeof(char), fp);
    return buffer;
}