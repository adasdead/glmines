#ifndef _GAME_FIELD_H_
#define _GAME_FIELD_H_

#include "graphics/renderer.h"

#include "game/input.h"
#include "game/cell.h"

typedef struct
{
    int width, height;
    int mines_count;

    cell_t **cells;

} field_t;


field_t *new_field(int width, int height, int mines_count);

void field_check_won(field_t *field);

void field_check_lost(field_t *field, int clck_x, int clck_y);

void field_generate(field_t *field, int clck_x, int clck_y);

void field_draw(const field_t *field, renderer_t *r);

void field_on_mouse(field_t *field, mouse_event_t e);

cell_t *field_get_cell(field_t *field, int cell_x, int cell_y);

cell_t *field_reveal_cell(field_t *field, int cell_x, int cell_y);

// cell_t *field_flag_cell(field_t *field, int cell_x, int cell_y);

int field_get_adjacent_mines(field_t *field, int cell_x, int cell_y);

// void field_reveal_all_cells(field_t *field);

void field_destroy(field_t *field);

#endif