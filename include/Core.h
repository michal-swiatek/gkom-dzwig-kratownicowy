/*
 *  Created by michal-swiatek on 19.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#ifndef OPENGLAPP_H
#define OPENGLAPP_H

#include <cstdint>
#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

class Core
{
public:
    using uint = uint32_t;
    using uchar = uint8_t;

public:
    explicit Core(std::string&& name, uint32_t appVersionMajor = 1, uint32_t appVersionMinor = 0);
    ~Core();

    //  Start application
    void initApp(uint32_t width = 1280, uint32_t height = 720, bool fullscreen = false, bool showCursor = true);
    void run();

protected:
    //  User Interface
    void updateInput();
    void updateLogic();
    void draw();

    void init();
    void quit();

    //  TODO: implement ConfigFile
    //virtual void loadConfig(const char* path);
    //virtual void saveConfig(const char* path);

    std::unique_ptr<Window> mainWindow;

    double deltaTime;
    double lastTime;
    uint32_t framesCounter;
    float framesPerSecond;

private:
    uint32_t appVersionMajor;
    uint32_t appVersionMinor;

    std::string name;
    std::string windowTitle;
};

#endif //OPENGLAPP_H
