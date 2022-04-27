#ifndef _GAME_WINDOW_H_
#define _GAME_WINDOW_H_

typedef void (*window_mouse_fun_t)(int, int, int, int);

void window_create(const char *window_name,
                   int base_width, int base_height);

void window_resize(int width, int height);

double window_get_scale_factor(void);

void window_clear(float r, float g, float b);

void window_set_icon(char *icon_path);

int window_is_opened(void);

void window_close(void);

void window_swap_buffers(void);

int window_get_height(void);

int window_get_width(void);

void window_free(void);

#endif