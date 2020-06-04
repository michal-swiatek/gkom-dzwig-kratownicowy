/*
 *  Created by michal-swiatek on 19.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#ifndef OPENGLAPP_H
#define OPENGLAPP_H

#include <cstdint>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"

void initOpenGL();

class Core
{
    friend void initOpenGL();   //  Creates graphic context and initializes Window

    //  Default main camera callbacks
    friend void scroll_callback(GLFWwindow* window, double xpos, double ypos);
    friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);

public:
    using uint = uint32_t;
    using uchar = uint8_t;

public:
    explicit Core(std::string&& name, uint32_t appVersionMajor = 1, uint32_t appVersionMinor = 0, uint32_t appVersionPatch = 0);
    ~Core();

    //  Start application
    void initApp(uint32_t width = 1280, uint32_t height = 720, bool fullscreen = false, bool showCursor = true);
    void run();

protected:
    //  User Interface
    virtual void updateInput();
    virtual void updateLogic();
    virtual void draw();

    virtual void init();
    virtual void quit();

    //  TODO: implement ConfigFile
    //virtual void loadConfig(const char* path);
    //virtual void saveConfig(const char* path);

    //  OpenGL context has to be created before app start for proper exception handling
    //  so window is actually created before the Core instance and stored as static object
    static std::unique_ptr<Window> mainWindow;
    static std::unique_ptr<cam::Camera> mainCamera;

    double deltaTime;
    double lastTime;
    uint32_t framesCounter;
    float framesPerSecond;

private:
    uint32_t appVersionMajor;
    uint32_t appVersionMinor;
    uint32_t appVersionPatch;

    std::string name;
    std::string windowTitle;
};

#endif //OPENGLAPP_H
