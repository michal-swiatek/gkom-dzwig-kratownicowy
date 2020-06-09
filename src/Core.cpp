/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#define GLEW_STATIC 
#include <GL/glew.h>

#include "Core.h"
#include <stdexcept>

std::unique_ptr<Window> Core::mainWindow = nullptr;
std::unique_ptr<cam::Camera> Core::mainCamera = nullptr;

//  Default main camera callbacks
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

//
//  Initialize OpenGL before the application starts
//
void initOpenGL()
{
    //  Initialize GLAD and GLFW, initApp has to be called before any OpenGL call as GLAD must be initialized
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("Failed to initialize GLFW!\n");

    Core::mainWindow = std::make_unique<Window>(WindowSettings());
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Failed to initialize GLEW!\n");

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
    mainWindow->updateWindowSettings(WindowSettings(width, height, windowTitle.c_str(), fullscreen, showCursor));

    //  Initialize main camera
    mainCamera = std::make_unique<cam::Camera>();
    glfwSetScrollCallback(mainWindow->getWindow(), scroll_callback);
    glfwSetCursorPosCallback(mainWindow->getWindow(), mouse_callback);

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

    //  Camera control

    //  Speed
    cam::Speed cameraSpeed = cam::Speed::NORMAL;
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed = cam::Speed::FAST;
    else if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        cameraSpeed = cam::Speed::SLOW;

    //  Movement direction
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        mainCamera->move(cam::Direction::FORWARD, cameraSpeed, deltaTime);
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        mainCamera->move(cam::Direction::BACKWARD, cameraSpeed, deltaTime);
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        mainCamera->move(cam::Direction::RIGHT, cameraSpeed, deltaTime);
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        mainCamera->move(cam::Direction::LEFT, cameraSpeed, deltaTime);
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        mainCamera->move(cam::Direction::UP, cameraSpeed, deltaTime);
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        mainCamera->move(cam::Direction::DOWN, cameraSpeed, deltaTime);
}

void Core::updateLogic()
{

}

void Core::draw()
{

}

//
//  Default main camera callbacks
//

void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
    Core::mainCamera->zoom(ypos);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;

    static double lastX = 1280 / 2;
    static double lastY = 720 / 2;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;

        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;   //  Reversed because y-coordinates range from bottom to top

    lastX = xpos;
    lastY = ypos;

    Core::mainCamera->rotate(xoffset, yoffset, 0.0);
}
