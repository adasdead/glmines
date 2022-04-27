#include "game/input.h"

#include <stdio.h>

#include <GLFW/glfw3.h>

extern GLFWwindow       *glfw_window;

input_mouse_fn_t         input_mouse_fn;
input_key_fn_t           input_key_fn;

int                      input_mouse_pos_x;
int                      input_mouse_pos_y;

void glfw_key_callback(GLFWwindow* window,
                       int key, int scancode,
                       int action, int mods);

void glfw_mouse_callback(GLFWwindow* window,
                         int button, int action,
                         int mods);

void glfw_cur_pos_callback(GLFWwindow* window,
                           double x, double y);

void input_mouse_callback(input_mouse_fn_t fn)
{
    glfwSetCursorPosCallback(glfw_window,
                             glfw_cur_pos_callback);
                             
    glfwSetMouseButtonCallback(glfw_window,
                               glfw_mouse_callback);

    input_mouse_fn = fn;
}

void input_key_callback(input_key_fn_t fn)
{
    glfwSetKeyCallback(glfw_window, glfw_key_callback);

    input_key_fn = fn;
}

void input_handle(void)
{
    glfwPollEvents();
}

void glfw_key_callback(GLFWwindow* window,
                       int key, int scancode,
                       int action, int mods)
{
    if (input_key_fn)
    {
        key_event_t e;
        e.is_press = (action == GLFW_PRESS);

        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            e.button = INPUT_KEY_ESC;
            input_key_fn(e);
            break;
        
        case GLFW_KEY_D:
            e.button = INPUT_KEY_D;
            input_key_fn(e);
            break;
        }
    }
}

void glfw_mouse_callback(GLFWwindow* window,
                         int button, int action,
                         int mods)
{
    if (input_mouse_fn)
    {
        mouse_event_t e;
        e.is_press = (action == GLFW_PRESS);
        e.x = input_mouse_pos_x;
        e.y = input_mouse_pos_y;

        switch (button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            e.button = INPUT_MOUSE_RIGHT;
            input_mouse_fn(e);
            break;
        
        case GLFW_MOUSE_BUTTON_LEFT:
            e.button = INPUT_MOUSE_LEFT;
            input_mouse_fn(e);
            break;
        }
    }
}

void glfw_cur_pos_callback(GLFWwindow* window,
                           double x, double y)
{
    input_mouse_pos_x = (int) x;
    input_mouse_pos_y = (int) y;
}