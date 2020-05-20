/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "Window.h"

#include <stdexcept>

//  Internal
GLFWwindow* createWindow(const WindowSettings& settings);

//  Default callbacks
void window_framebuffer_size_callback(GLFWwindow* window, int width, int height);

WindowSettings::WindowSettings() : width(1), height(1), title(""), fullscreen(false), showCursor(true) { }
WindowSettings::WindowSettings(int32_t width,
                               int32_t height,
                               const char *title,
                               bool fullscreen,
                               bool showCursor) :
                                    width(width), height(height), title(title),
                                    fullscreen(fullscreen), showCursor(showCursor) { }

Window::Window(const WindowSettings& settings) : settings(settings)
{
    window = WindowPtr(createWindow(settings));
    glfwMakeContextCurrent(getWindow());

    setDefaultCallbacks();
}

Window::~Window()
{
    window.reset(); //  Window destruction is handled by unique_ptr deleter
}

GLFWwindow* Window::getWindow() const
{
    return window.get();
}

void Window::close() const
{
    glfwSetWindowShouldClose(window.get(), true);
}

bool Window::isClosed() const
{
    return glfwWindowShouldClose(window.get());
}

void Window::setDefaultCallbacks() const
{
    glfwSetFramebufferSizeCallback(window.get(), window_framebuffer_size_callback);
}

const WindowSettings& Window::getWindowSettings() const
{
    return settings;
}

void Window::updateWindowSettings(const WindowSettings &newSettings)
{
    settings = newSettings;

    glfwSetWindowTitle(window.get(), settings.title.c_str());
    glfwSetWindowSize(window.get(), settings.width, settings.height);
    if (settings.fullscreen)
        glfwSetWindowMonitor(window.get(), glfwGetPrimaryMonitor(), 0, 0, settings.width, settings.height, 60);
    if (!settings.showCursor)
        glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    setDefaultCallbacks();
}

//
//  Window creation
//

GLFWwindow* createWindow(const WindowSettings &settings)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);
    if (!window)
        throw std::runtime_error("Failed to create GLFWWindow!\n");

    if (settings.fullscreen)
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, settings.width, settings.height, 60);
    if (!settings.showCursor)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}

//
//  Callbacks
//
void window_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
