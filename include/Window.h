/*
 *  Created by michal-swiatek on 19.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <string>
#include <memory>

#include <GLFW/glfw3.h>

struct GLFWWindowDelete
{
    void operator() (GLFWwindow* window)
    {
        glfwDestroyWindow(window);
    }
};

struct WindowSettings
{
    int32_t width;
    int32_t height;

    std::string title;

    bool fullscreen;
    bool showCursor;

    WindowSettings();
    WindowSettings(int32_t width, int32_t height, const char* title, bool fullscreen = false, bool showCursor = true);
};

class Window
{
private:
    using WindowPtr = std::unique_ptr<GLFWwindow, GLFWWindowDelete>;

public:
    //  Create window and make context current
    explicit Window(const WindowSettings& settings);
    ~Window();

    //  Window access
    [[nodiscard]] GLFWwindow* getWindow() const;

    void close() const;
    [[nodiscard]] bool isClosed() const;

    //  Callbacks
    void setDefaultCallbacks() const;

    //  Window Settings
    [[nodiscard]] const WindowSettings& getWindowSettings() const;
    void updateWindowSettings(const WindowSettings& newSettings);

private:
    WindowPtr window;

    WindowSettings settings;
};

#endif //WINDOW_H
