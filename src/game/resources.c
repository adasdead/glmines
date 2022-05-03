#include "game/resources.h"

#include <stdio.h>

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

void resources_load_rt(render_target_t *res_ptr,
                      char *path_fmt, int max);

void resources_load_all(void)
{
    if (!resources_loaded)
    {
        resources_default_shader = new_shader(DEFAULT_VSHADER_PATH,
                                              DEFAULT_FSHADER_PATH);

        resources_load_rt(resources_cell_rt, CELL_TEX_PATH_FMT,
                          CELL_TYPES_TOTAL);

        resources_load_rt(resources_border_rt, BORDER_TEX_PATH_FMT,
                          BORDER_DIR_TOTAL);

        resources_load_rt(resources_smile_rt, SMILE_TEX_PATH_FMT,
                          SMILE_STATES_TOTAL);

        resources_load_rt(resources_counter_rt, COUNTER_TEX_PATH_FMT, 10);
        
        resources_loaded = 1;
    }
}

void resources_load_rt(render_target_t *res_ptr,
                      char *path_fmt, int max)
{
    char file_path[256];

    for (int i = 0; i < max; i++)
    {
        sprintf(file_path, path_fmt, i);

        render_target_t *target = res_ptr + i;
        target->texture = new_texture2d(file_path);
        target->shader  = resources_default_shader;
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