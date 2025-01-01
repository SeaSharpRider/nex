#ifndef FALCON_H
#define FALCON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
// TODO: Add stb_image.h

#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION

typedef struct {
    int width;
    int height;
    GLFWwindow* handle;
    const char* title;
    bool is_fullscreen;
    bool is_maximized;
    bool is_resizable;
    bool is_decorated;
    bool is_visible;
    bool is_focused;
    float bg_color[4];
} Window;

static inline Window* window_create(int width, int height, const char* title) {
    if (!glfwInit()) {
        fprintf(stderr, "failed to initialize glfw: debug - error on line 19\n");
        return NULL;
    }

    Window* window = (Window*)malloc(sizeof(Window));
    window->width = width;
    window->height = height;
    window->title = title;
    window->is_fullscreen = false;
    window->is_maximized = false;
    window->is_resizable = true;
    window->is_decorated = true;
    window->is_visible = true;
    window->is_focused = true;

    window->bg_color[0] = 1.0f;
    window->bg_color[1] = 1.0f;
    window->bg_color[2] = 1.0f;
    window->bg_color[3] = 1.0f;

    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window->handle) {
        fprintf(stderr, "failed to create window with glfw: debug - error on line 47\n");
        free(window);
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window->handle);
    glfwSwapInterval(1);

    return window;
}

static inline void window_destroy(Window* window) {
    if (window) {
        glfwDestroyWindow(window->handle);
        free(window);
        glfwTerminate();
    }
}

static inline void window_set_fullscreen(Window* window, bool fullscreen) {
    if (!window) return;

    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window->handle, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        window->is_fullscreen = true;
    } else {
        glfwSetWindowMonitor(window->handle, NULL, 100, 100, window->width, window->height, 0);
        window->is_fullscreen = false;
    }
}

static inline void window_set_maximized(Window* window, bool maximized) {
    if (!window) return;

    if (maximized) {
        glfwMaximizeWindow(window->handle);
        window->is_maximized = true;
    } else {
        glfwRestoreWindow(window->handle);
        window->is_maximized = false;
    }
}

static inline void window_set_resizable(Window* window, bool resizable) {
    if (!window) return;

    glfwSetWindowAttrib(window->handle, GLFW_RESIZABLE, resizable);
    window->is_resizable = resizable;
}

static inline void window_set_decorated(Window* window, bool decorated) {
    if (!window) return;

    glfwSetWindowAttrib(window->handle, GLFW_DECORATED, decorated);
    window->is_decorated = decorated;
}

static inline void window_set_visible(Window* window, bool visible) {
    if (!window) return;

    glfwShowWindow(window->handle);
    window->is_visible = true;
}

static inline void window_set_focused(Window* window, bool focused) {
    if (!window) return;

    glfwFocusWindow(window->handle);
    window->is_focused = true;
}

static inline void window_set_bg_color(Window* window, float r, float g, float b, float a) {
    if (!window) return;

    window->bg_color[0] = r;
    window->bg_color[1] = g;
    window->bg_color[2] = b;
    window->bg_color[3] = a;
}

static inline void window_set_title(Window* window, const char* title) {
    if (!window) return;

    window->title = title;
    glfwSetWindowTitle(window->handle, title);
}


// TODO: Implement icon setting
//static inline void window_set_icon(Window* window, const char* icon_path) {
//    if (!window) return;
//    GLFWimage icon;
//    icon.pixels = stbi_load(icon_path, &icon.width, &icon.height, NULL, 4);
//    glfwSetWindowIcon(window->handle, 1, &icon);
//    stbi_image_free(icon.pixels);
//}

static inline void window_set_size(Window* window, int width, int height) {
    if (!window) return;

    window->width = width;
    window->height = height;
    glfwSetWindowSize(window->handle, width, height);
}

static inline void window_set_position(Window* window, int x, int y) {
    if (!window) return;

    glfwSetWindowPos(window->handle, x, y);
}

static inline void window_update(Window* window) {
    if (!window) return;
    
    glClearColor(window->bg_color[0], window->bg_color[1], window->bg_color[2], window->bg_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window->handle);
    glfwPollEvents();
}

static inline bool window_should_close(Window* window) {
    return window ? glfwWindowShouldClose(window->handle) : true;
}

#endif