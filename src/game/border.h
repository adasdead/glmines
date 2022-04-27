#ifndef _GAME_BORDER_H_
#define _GAME_BORDER_H_

#include "game/field.h"

enum border_direction
{
    BORDER_DIR_NW,
    BORDER_DIR_NE,
    BORDER_DIR_SE,
    BORDER_DIR_SW,
    BORDER_DIR_N,
    BORDER_DIR_E,
    BORDER_DIR_S,
    BORDER_DIR_W,
    BORDER_DIR_S_W,
    BORDER_DIR_S_E,
    BORDER_DIR_TOTAL
};

void border_draw(renderer_t *r, const field_t *field);

void border_draw_separator(renderer_t *r, int bottom, int right);
void border_draw_edges(renderer_t *r, int bottom, int right);
void border_draw_corners(renderer_t *r, int bottom, int right);

#endif