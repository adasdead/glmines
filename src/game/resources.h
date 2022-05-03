#ifndef _GAME_RESOURCES_H_
#define _GAME_RESOURCES_H_

#include "graphics/renderer.h"

enum resource_type
{
    RES_CELL,
    RES_BORDER,
    RES_SMILE,
    RES_COUNTER
};

void resources_load_all(void);

render_target_t *resources_get(int res_type, int id);

void resources_free(void);

#endif