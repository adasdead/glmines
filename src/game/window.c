#include "game/window.h"

#include <stdlib.h>

#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include "stb/stb_image.h"

#include "definitions.h"

GLFWwindow             *glfw_window;

int                     window_width;
int                     window_height;

void window_create(const char *window_name,
                   int base_width, int base_height)
{
    if (!glfwInit())
    {
        fprintf(stderr, "GLFW initialization failed");
        exit(EXIT_FAILURE);
    }

    double window_scale_factor = window_get_scale_factor();

    window_width  = base_width  * window_scale_factor;
    window_height = base_height * window_scale_factor;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfw_window = glfwCreateWindow(window_width, window_height,
                                   window_name, NULL, NULL);

    if (!glfw_window)
    {
        fprintf(stderr, "GLFW window is not created");
        glfwTerminate();

        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(glfw_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        fprintf(stderr, "GLAD initialization failed");
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, window_width, window_height);

    glfwSwapInterval(1);
}

void window_resize(int width, int height)
{
    glfwSetWindowSize(glfw_window, width, height);
    glViewport(0, 0, width, height);

    window_height = height;
    window_width = width;
}

double window_get_scale_factor(void)
{
    const GLFWvidmode *video_mode;
    video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return (video_mode->height) / SCREEN_BASE_HEIGHT;
}

void window_clear(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void window_set_icon(char *icon_path)
{
    GLFWimage image;
    image.pixels = stbi_load(icon_path, &image.width,
                             &image.height, NULL,
                             STBI_rgb_alpha);

    glfwSetWindowIcon(glfw_window, 1, &image);

    stbi_image_free(image.pixels);
}

int window_is_opened(void)
{
    return !glfwWindowShouldClose(glfw_window);
}

void window_close(void)
{
    glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
}

void window_swap_buffers(void)
{
    glfwSwapBuffers(glfw_window);
}

int window_get_height(void)
{
    return window_height;
}

int window_get_width(void)
{
    return window_width;
}

void window_free(void)
{
    if (glfw_window)
    {
        glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }
}