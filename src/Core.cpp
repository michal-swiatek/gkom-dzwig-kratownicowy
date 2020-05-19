/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "Core.h"

#include <stdexcept>

std::unique_ptr<Window> Core::mainWindow = nullptr;

//
//  Initialize OpenGL before the application starts
//
void initOpenGL()
{
    //  Initialize GLAD and GLFW, initApp has to be called before any OpenGL call as GLAD must be initialized
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("Failed to initialize GLFW!\n");

    Core::mainWindow = std::make_unique<Window>(WindowSettings());
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD!\n");
}

Core::Core(std::string&& name, uint32_t appVersionMajor, uint32_t appVersionMinor, uint32_t appVersionPatch)
{
    this->appVersionMajor = appVersionMajor;
    this->appVersionMinor = appVersionMinor;
    this->appVersionPatch = appVersionPatch;
    this->name = name;
    this->windowTitle = name + ", version: " + std::to_string(appVersionMajor) + '.' + std::to_string(appVersionMinor) + '.' + std::to_string(appVersionPatch);

    lastTime = deltaTime = 0.0;
    framesCounter = 0;
    framesPerSecond = 0.0;
}

Core::~Core()
{
    glfwTerminate();
}

void Core::initApp(uint32_t width, uint32_t height, bool fullscreen, bool showCursor)
{
    //  Customize window
    glfwSetWindowTitle(mainWindow->getWindow(), windowTitle.c_str());
    glfwSetWindowSize(mainWindow->getWindow(), width, height);
    if (fullscreen)
        glfwSetWindowMonitor(mainWindow->getWindow(), glfwGetPrimaryMonitor(), 0, 0, width, height, 60);
    if (!showCursor)
        glfwSetInputMode(mainWindow->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.1, 0.2, 1.0);

    init();
}

void Core::run()
{
    lastTime = deltaTime = 0.0;
    framesCounter = 0;

    while (!mainWindow->isClosed())
    {
        //  Timing and fps info
        ++framesCounter;
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        framesPerSecond = static_cast<float>(1 / deltaTime);

        //  Update input
        glfwPollEvents();

        std::string windowInfo = windowTitle + ", fps: " + std::to_string(int(framesPerSecond));
        glfwSetWindowTitle(mainWindow->getWindow(), windowInfo.c_str());

        updateInput();
        updateLogic();

        //  Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();

        glfwSwapBuffers(mainWindow->getWindow());
    }

    quit();
}

void Core::init()
{

}

void Core::quit()
{

}

void Core::updateInput()
{
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        mainWindow->close();
}

void Core::updateLogic()
{

}

void Core::draw()
{

}