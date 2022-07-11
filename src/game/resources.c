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

#include "game/resources.h"

#include <stdio.h>
#include <string.h>

#include "game/window.h"

#include "game/border.h"
#include "game/smile.h"
#include "game/cell.h"

#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "graphics/shader.h"

#include "definitions.h"

static shader_t            _resources_default_shader;

static render_target_t     _resources_cell_rt[CELL_TYPES_TOTAL];
static render_target_t     _resources_border_rt[BORDER_DIR_TOTAL];
static render_target_t     _resources_smile_rt[SMILE_STATES_TOTAL];
static render_target_t     _resources_counter_rt[10];

static render_target_t     _resources_bg_tex = {0};

static char                _resources_root_path[512] = {'\0'};

static int                 _resources_loaded = 0;

static void _resources_get_root_path(char *exe_path)
{
    if (_resources_root_path[0] == '\0')
    {
        strncpy(_resources_root_path, exe_path, strlen(exe_path));

        for (int i = strlen(_resources_root_path); i != 0; i--)
        {
            if (_resources_root_path[i] == '\\' ||
                _resources_root_path[i] == '/')
            {
                _resources_root_path[i] = '\0';
                break;
            }
        }
    }
}

static void _resources_load_rt(render_target_t *res_ptr,
                               const char *path_fmt,
                               size_t ptr_size)
{
    char file_path[1024];

    for (int i = 0; i < ptr_size; i++)
    {
        snprintf(file_path, 1024, path_fmt,
                 _resources_root_path, i);

        render_target_t *target = res_ptr + i;
        target->texture = new_texture2d(file_path);
        target->shader  = _resources_default_shader;
    }
}

static void _resources_load_bg_tex(void)
{
    char tex_path[1024];

    snprintf(tex_path, 1024, BACKGROUND_TEX_PATH,
             _resources_root_path);

    _resources_bg_tex.texture = new_texture2d(tex_path);
    _resources_bg_tex.shader  = _resources_default_shader;
}

static void _resources_set_win_icon(void)
{
    char icon_path[1024];
    snprintf(icon_path, 1024, ICON_PATH, _resources_root_path);
    window_set_icon(icon_path);
}

static void _resources_create_shader(void)
{
    char shaders_path[2][1024];

    snprintf(shaders_path[0], 1024, DEFAULT_VSHADER_PATH,
             _resources_root_path);
    
    snprintf(shaders_path[1], 1024, DEFAULT_FSHADER_PATH,
             _resources_root_path);

    _resources_default_shader = new_shader(shaders_path[0],
                                           shaders_path[1]);
}

void resources_load_all(int argc, char **argv)
{
    if (!_resources_loaded)
    {
        _resources_get_root_path(argv[0]);
        _resources_create_shader();
        _resources_set_win_icon();

        _resources_load_bg_tex();

        _resources_load_rt(_resources_cell_rt,
                           CELL_TEX_PATH_FMT,
                           CELL_TYPES_TOTAL);

        _resources_load_rt(_resources_border_rt,
                          BORDER_TEX_PATH_FMT,
                          BORDER_DIR_TOTAL);

        _resources_load_rt(_resources_smile_rt,
                           SMILE_TEX_PATH_FMT,
                           SMILE_STATES_TOTAL);

        _resources_load_rt(_resources_counter_rt,
                           COUNTER_TEX_PATH_FMT,
                           10);
        
        _resources_loaded = 1;
    }
}

render_target_t *resources_get(int res_type, int id)
{
    if (_resources_loaded)
    {
        switch (res_type)
        {
        case RES_CELL:
            return _resources_cell_rt + id;

        case RES_BORDER:
            return _resources_border_rt + id;
        
        case RES_SMILE:
            return _resources_smile_rt + id;
        
        case RES_COUNTER:
            return _resources_counter_rt + id;

        case RES_BG_TEX:
            return &_resources_bg_tex;
        }
    }

    return NULL;
}

void resources_free(void)
{
    if (_resources_loaded)
    {
        shader_destroy(_resources_default_shader);

        for (int i = 0; i < CELL_TYPES_TOTAL; i++)
            texture2d_destroy(_resources_cell_rt[i].texture);

        for (int i = 0; i < BORDER_DIR_TOTAL; i++)
            texture2d_destroy(_resources_border_rt[i].texture);

        for (int i = 0; i < SMILE_STATES_TOTAL; i++)
            texture2d_destroy(_resources_smile_rt[i].texture);
        
        for (int i = 0; i < 10; i++)
            texture2d_destroy(_resources_counter_rt[i].texture);

        texture2d_destroy(_resources_bg_tex.texture);

        _resources_loaded = 0;
    }
}