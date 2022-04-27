#ifndef _GAME_CELL_H_
#define _GAME_CELL_H_

enum cell_state
{
    CELL_STATE_OPENED,
    CELL_STATE_CLOSED,
    CELL_STATE_FLAGGED,
    CELL_STATE_QUESTIONED,
    CELL_STATES_TOTAL
};

enum cell_type
{
    CELL_TYPE_0,
    CELL_TYPE_1,
    CELL_TYPE_2,
    CELL_TYPE_3,
    CELL_TYPE_4,
    CELL_TYPE_5,
    CELL_TYPE_6,
    CELL_TYPE_7,
    CELL_TYPE_8,
    CELL_TYPE_BOMB,
    CELL_TYPE_NO_BOMB,
    CELL_TYPE_BOMB_E,
    CELL_TYPE_CLOSE,
    CELL_TYPE_QUESTION,
    CELL_TYPE_FLAG,
    CELL_TYPES_TOTAL
};

typedef struct
{
    int type;
    int state;

} cell_t;

#endif