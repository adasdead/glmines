#include "game/field.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game/resources.h"
#include "game/game.h"
#include "game/window.h"
#include "game/input.h"
#include "game/cell.h"
#include "game/smile.h"
#include "game/counter.h"

#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "graphics/shader.h"

#include "math/matrix4.h"
#include "math/transform.h"

#include "definitions.h"

int                             mouse_cur_cell_x;
int                             mouse_cur_cell_y;

extern int                      input_mouse_pos_x;
extern int                      input_mouse_pos_y;

extern counter_t               *game_mines_counter;

field_t *new_field(int width, int height, int mines_count)
{
    srand(time(NULL));

    field_t *field = malloc(sizeof(field_t));
    field->mines_count = mines_count;
    field->height = height;
    field->width = width;

    field->cells = calloc(width, sizeof(field->cells));

    for (int x = 0; x < width; x++)
    {
        field->cells[x] = calloc(height, sizeof(cell_t));

        for (int y = 0; y < height; y++)
        {
            field->cells[x][y].state = CELL_STATE_CLOSED;
            field->cells[x][y].type  = CELL_TYPE_0;
        }
    }
    
    return field;
}

void field_check_won(field_t *field)
{
    if (game_get_state() == GAME_STATE_LOSE)
        return;

    for (int x = 0; x < field->width; x++)
    {
        for (int y = 0; y < field->height; y++)
        {
            cell_t *cell = field_get_cell(field, x, y);

            if (cell->type != CELL_TYPE_BOMB &&
                cell->state == CELL_STATE_CLOSED)
            {
                return;
            }

        }
    }

    for (int x = 0; x < field->width; x++)
    {
        for (int y = 0; y < field->height; y++)
        {
            cell_t *cell = field_get_cell(field, x, y);

            if (cell->type == CELL_TYPE_BOMB)
                cell->state = CELL_STATE_FLAGGED;
        }
    }

    game_set_state(GAME_STATE_WON);
}

void field_check_lost(field_t *field, int clck_x, int clck_y)
{
    cell_t *cell = field_get_cell(field, clck_x, clck_y);

    if (cell->type == CELL_TYPE_BOMB)
    {
        cell->type = CELL_TYPE_BOMB_E;

        for (int x = 0; x < field->width; x++)
        {
            for (int y = 0; y < field->height; y++)
            {
                cell_t *cell = field_get_cell(field, x, y);

                if (cell->state == CELL_STATE_FLAGGED &&
                    cell->type != CELL_TYPE_BOMB)
                {
                    cell->type = CELL_TYPE_NO_BOMB;
                }
                
                cell->state = CELL_STATE_OPENED;
            }
        }

        game_set_state(GAME_STATE_LOSE);
    }
}

void field_generate(field_t *field, int clck_x, int clck_y)
{
    int placed_mines = 0;

    //
    //  Generate mines
    //

    while (placed_mines != field->mines_count)
    {
        int rnd_x = rand() % field->width;
        int rnd_y = rand() % field->height;

        if (rnd_x == clck_x && rnd_y == clck_y)
            continue;

        cell_t *cell = field_get_cell(field, rnd_x, rnd_y);

        if (cell->type != CELL_TYPE_BOMB)
        {
            cell->type = CELL_TYPE_BOMB;
            placed_mines++;
        }
    }

    //
    //  Generate numbers
    //

    for (int x = 0; x < field->width; x++)
    {
        for (int y = 0; y < field->height; y++)
        {
            cell_t *cell = field_get_cell(field, x, y);

            if (cell->type != CELL_TYPE_BOMB)
                cell->type = field_get_adjacent_mines(field, x, y);
        }
    }
}

void field_update_cell_mouse_pos(void)
{
    double scale_factor = window_get_scale_factor();
    float cell_width = CELL_WIDTH * scale_factor;

    int m_x = input_mouse_pos_x;
    int m_y = input_mouse_pos_y;

    float margin_left_px = FIELD_MARGIN_LEFT * cell_width;
    float margin_top_px  = FIELD_MARGIN_TOP * cell_width;

    if (m_y <= margin_top_px || m_x <= margin_left_px)
    {
        mouse_cur_cell_x = mouse_cur_cell_y = -1;
        return;
    }
    
    mouse_cur_cell_x = (m_x - margin_left_px) / cell_width;
    mouse_cur_cell_y = (m_y - margin_top_px) / cell_width;
}

void field_draw(const field_t *field, renderer_t *r)
{
    field_update_cell_mouse_pos();

    mat4_t model = new_unit_matrix4();

    for (int x = 0; x < field->width; x++)
    {
        for (int y = 0; y < field->height; y++)
        {
            int cell_type;
            render_target_t *target;
            
            switch (field->cells[x][y].state)
            {
            case CELL_STATE_CLOSED:
                cell_type = CELL_TYPE_CLOSE;
                break;

            case CELL_STATE_FLAGGED:
                cell_type = CELL_TYPE_FLAG;
                break;

            case CELL_STATE_QUESTIONED:
                cell_type = CELL_TYPE_QUESTION;
                break;
            
            default:
                cell_type = field->cells[x][y].type;
            }

            target = resources_get(RES_CELL, cell_type);

            vec3_t pos = new_vector3(x + FIELD_MARGIN_LEFT,
                                     y + FIELD_MARGIN_TOP,
                                     0.0f);

            matrix4_translate(model, pos);

            if (x == mouse_cur_cell_x && y == mouse_cur_cell_y &&
                field->cells[x][y].state != CELL_STATE_OPENED)
            {
                shader_set_uniform_1i(target->shader, "is_hover", 1);
            }

            renderer_draw(r, model, target);
            shader_set_uniform_1i(target->shader, "is_hover", 0);
            matrix4_reset(model, MATRIX4_UNIT);
        }
    }

    matrix4_destroy(model);
}

void field_on_mouse(field_t *field, mouse_event_t e)
{
    int game_state = game_get_state();
    
    int cell_x = mouse_cur_cell_x;
    int cell_y = mouse_cur_cell_y;

    cell_t *cell = field_get_cell(field, cell_x, cell_y);

    if (cell && game_state < GAME_STATE_LOSE)
    {
        if (e.is_press)
        {
            switch (e.button)
            {
            case INPUT_MOUSE_LEFT:

                if (game_state == GAME_STATE_IDLE)
                {
                    field_generate(field, cell_x, cell_y);
                    game_set_state(GAME_STATE_STARTED);
                }

                if (cell->state != CELL_STATE_FLAGGED)
                {
                    field_check_lost(field, cell_x, cell_y);
                    field_reveal_cell(field, cell_x, cell_y);
                    field_check_won(field);
                }
                
                break;
            
            case INPUT_MOUSE_RIGHT:

                switch (cell->state)
                {
                case CELL_STATE_FLAGGED:
                    cell->state = CELL_STATE_QUESTIONED;
                    game_mines_counter->value++;
                    break;

                case CELL_STATE_QUESTIONED:
                    cell->state = CELL_STATE_CLOSED;
                    break;
                
                case CELL_STATE_CLOSED:
                    cell->state = CELL_STATE_FLAGGED;
                    game_mines_counter->value--;
                    break;
                }

                break;
            }
        }
    }

}

cell_t *field_get_cell(field_t *field, int cell_x, int cell_y)
{
    if (cell_x >= field->width || cell_y >= field->height)
        return NULL;
    
    if (cell_x < 0 || cell_y < 0)
        return NULL;
    
    return &field->cells[cell_x][cell_y];
}

cell_t *field_reveal_cell(field_t *field, int cell_x, int cell_y)
{
    cell_t *cell = field_get_cell(field, cell_x, cell_y);

    if (!cell) return NULL;

    if (cell->state == CELL_STATE_OPENED)
        return cell;

    cell->state = CELL_STATE_OPENED;

    if (cell->type == CELL_TYPE_0)
    {
        for (int off_x = -1; off_x <= 1; off_x++)
        {
            for (int off_y = -1; off_y <= 1; off_y++)
            {
                if (off_x == 0 && off_y == 0)
                    continue;
                
                int x = cell_x + off_x;
                int y = cell_y + off_y;

                cell_t *nb_cell = field_get_cell(field, x, y);

                if (nb_cell)
                {
                    if (nb_cell->state == CELL_STATE_FLAGGED)
                        continue;

                    if (nb_cell->type != CELL_TYPE_BOMB)
                        field_reveal_cell(field, x, y);
                }
            }
        }
    }

    
    return cell;
}

int field_get_adjacent_mines(field_t *field,
                             int cell_x,
                             int cell_y)
{
    int mines_count = 0;

    for (int off_x = -1; off_x <= 1; off_x++)
    {
        for (int off_y = -1; off_y <= 1; off_y++)
        {
            if (off_x == 0 && off_y == 0)
                continue;
            
            int x = cell_x + off_x;
            int y = cell_y + off_y;

            cell_t *cell = field_get_cell(field, x, y);

            if (cell)
            {
                if (cell->type == CELL_TYPE_BOMB)
                    mines_count++;
            }
        }
    }

    return mines_count;
}

void field_destroy(field_t *field)
{
    if (field)
    {
        for (int i = 0; i < field->width; i++)
            free(field->cells[i]);

        free(field->cells);
        free(field);
    }
}