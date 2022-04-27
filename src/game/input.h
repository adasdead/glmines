#ifndef _GAME_INPUT_H_
#define _GAME_INPUT_H_

enum input_mouse_button
{
    INPUT_MOUSE_RIGHT,
    INPUT_MOUSE_LEFT
};

enum input_key_button
{
    INPUT_KEY_ESC,
    INPUT_KEY_D
};

typedef struct
{
    int button;
    int is_press;

} key_event_t;

typedef struct
{
    double x, y;
    int button;
    int is_press;

} mouse_event_t;

typedef void (*input_key_fn_t)(key_event_t e);
typedef void (*input_mouse_fn_t)(mouse_event_t e);

void input_mouse_callback(input_mouse_fn_t fn);
void input_key_callback(input_key_fn_t fn);

void input_handle(void);

#endif