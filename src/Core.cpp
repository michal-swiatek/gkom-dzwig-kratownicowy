/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "Core.h"

#include <cmath>
#include <stdexcept>
#include "Cylinder.h"
#include "Compound.h"

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
    auto c = std::unique_ptr<Cylinder>(new Cylinder(1.0f, 0.5f, 2.0, 25, 2));
    auto c2 = std::unique_ptr<Cylinder>(new Cylinder(1.2f, 0.3f, 1.0, 5, 1));

    auto c3 = std::unique_ptr<Cylinder>(new Cylinder(1.0f, 0.5f, 2.0, 25, 2));
    auto c4 = std::unique_ptr<Cylinder>(new Cylinder(1.2f, 0.3f, 1.0, 5, 1));

    c2->rotate(180.0f, glm::vec3(1.0, 0.0, 0.0));
    c4->rotate(180.0f, glm::vec3(1.0, 0.0, 0.0));


    c->draw(mainCamera, mainWindow->getWindowSettings(), true);
    c2->draw(mainCamera, mainWindow->getWindowSettings(), false);



    auto comp = std::unique_ptr<Compound>(new Compound());
    comp->addObject(std::move(c));
    comp->addObject(std::move(c2));
    comp->rotate(90.0f, glm::vec3(1.0, 0.0, 0.0));

    auto comp2 = std::unique_ptr<Compound>(new Compound());
    comp2->addObject(std::move(c3));
    comp2->addObject(std::move(c4));
    comp2->rotate(90.0f, glm::vec3(1.0, 0.0, 0.0));

    float a, b;
    a = (float)cos(glfwGetTime()) * 2;
    if (a == 0) {
        a = 0.0001;
    }
    b = (float)sin(glfwGetTime()) * 2;
    if (b == 0) {
        b = 0.0001;
    }

    comp->rotate((float)atan2(b, a) * (180.0 / 3.141592653589793238463), glm::vec3(0.0, 0.0, 1.0));
    comp->translate(glm::vec3(a, 5.0f + b, 0.0f));

    comp->draw(mainCamera, mainWindow->getWindowSettings(), false);

    comp2->translate(glm::vec3(0.0f, 5.0f, 0.0f));

    comp2->draw(mainCamera, mainWindow->getWindowSettings(), false);

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
