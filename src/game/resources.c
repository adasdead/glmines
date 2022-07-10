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

shader_t            resources_default_shader;

render_target_t     resources_cell_rt[CELL_TYPES_TOTAL];
render_target_t     resources_border_rt[BORDER_DIR_TOTAL];
render_target_t     resources_smile_rt[SMILE_STATES_TOTAL];
render_target_t     resources_counter_rt[10];

int                 resources_loaded = 0;

static char _exe_root_path[512];

static void _resources_load_rt(render_target_t *res_ptr,
                               const char *path_fmt, int max)
{
    char file_path[1024];

    for (int i = 0; i < max; i++)
    {
        snprintf(file_path, 1024, path_fmt, _exe_root_path, i);

        render_target_t *target = res_ptr + i;
        target->texture = new_texture2d(file_path);
        target->shader  = resources_default_shader;
    }
}

void resources_load_all(int argc, char **argv)
{
    if (!resources_loaded)
    {
        strncpy(_exe_root_path, argv[0], strlen(argv[0]));

        for (int i = strlen(_exe_root_path); i != 0; i--)
        {
            if (_exe_root_path[i] == '\\' ||
                _exe_root_path[i] == '/')
            {
                _exe_root_path[i] = '\0';
                break;
            }
        }

        char icon_path[1024];
        snprintf(icon_path, 1024, ICON_PATH, _exe_root_path);
        window_set_icon(icon_path);

        char shaders_path[2][1024];

        snprintf(shaders_path[0], 1024, DEFAULT_VSHADER_PATH, _exe_root_path);
        snprintf(shaders_path[1], 1024, DEFAULT_FSHADER_PATH, _exe_root_path);

        resources_default_shader = new_shader(shaders_path[0],
                                              shaders_path[1]);

        _resources_load_rt(resources_cell_rt, CELL_TEX_PATH_FMT,
                          CELL_TYPES_TOTAL);

        _resources_load_rt(resources_border_rt, BORDER_TEX_PATH_FMT,
                          BORDER_DIR_TOTAL);

        _resources_load_rt(resources_smile_rt, SMILE_TEX_PATH_FMT,
                          SMILE_STATES_TOTAL);

        _resources_load_rt(resources_counter_rt, COUNTER_TEX_PATH_FMT,
                           10);
        
        resources_loaded = 1;
    }
}

render_target_t *resources_get(int res_type, int id)
{
    if (resources_loaded)
    {
        switch (res_type)
        {
        case RES_CELL:
            return resources_cell_rt + id;

        case RES_BORDER:
            return resources_border_rt + id;
        
        case RES_SMILE:
            return resources_smile_rt + id;
        
        case RES_COUNTER:
            return resources_counter_rt + id;
        }
    }

    return NULL;
}

void resources_free(void)
{
    if (resources_loaded)
    {
        shader_destroy(resources_default_shader);

        for (int i = 0; i < CELL_TYPES_TOTAL; i++)
            texture2d_destroy(resources_cell_rt[i].texture);

        for (int i = 0; i < BORDER_DIR_TOTAL; i++)
            texture2d_destroy(resources_border_rt[i].texture);

        for (int i = 0; i < SMILE_STATES_TOTAL; i++)
            texture2d_destroy(resources_smile_rt[i].texture);
        
        for (int i = 0; i < 10; i++)
            texture2d_destroy(resources_counter_rt[i].texture);

        resources_loaded = 0;
    }
}