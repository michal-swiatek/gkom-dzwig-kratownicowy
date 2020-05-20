/*
 *  Created by michal-swiatek on 19.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include "Core.h"

#include <memory>
#include <iostream>

#include "Shader.h"
#include "Camera.h"

#include "Cylinder.h"

cam::Camera camera;

//  Camera callbacks
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class DisplayCylinder : public Core
{
    using uint = unsigned int;

private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Cylinder> cylinder;

    uint VBO, VAO, EBO;

public:
    DisplayCylinder() : Core("Display cylinder"), VBO(0), VAO(0), EBO(0)
    {
        cylinder = std::make_unique<Cylinder>(1.0f, 0.5f, 2.0, 25, 2);
        shader = std::make_unique<Shader>("shaders/flat.vs.glsl", "shaders/flat.fs.glsl");
    }

    void init() override
    {
        glfwSetScrollCallback(mainWindow->getWindow(), scroll_callback);
        glfwSetCursorPosCallback(mainWindow->getWindow(), mouse_callback);
        camera.getSettings().movementSpeed /= 2;

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, cylinder->getVertices().size() * sizeof(float), cylinder->getVertices().data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinder->getIndices().size() * sizeof(unsigned int), cylinder->getIndices().data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);

        shader->use();

        float color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
        glUniform4fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, color);
    }

    void updateInput() override
    {
        Core::updateInput();

        //  Camera control

        //  Speed
        cam::Speed cameraSpeed = cam::Speed::NORMAL;
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraSpeed = cam::Speed::FAST;
        else if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
            cameraSpeed = cam::Speed::SLOW;

        //  Movement direction
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
            camera.move(cam::Direction::FORWARD, cameraSpeed, deltaTime);
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
            camera.move(cam::Direction::BACKWARD, cameraSpeed, deltaTime);
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
            camera.move(cam::Direction::RIGHT, cameraSpeed, deltaTime);
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
            camera.move(cam::Direction::LEFT, cameraSpeed, deltaTime);
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.move(cam::Direction::UP, cameraSpeed, deltaTime);
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.move(cam::Direction::DOWN, cameraSpeed, deltaTime);
    }

    void draw() override
    {
        shader->setMatrix4f("mvp", camera.getViewProjectionMatrix());

        auto width = mainWindow->getWindowSettings().width;
        auto height = mainWindow->getWindowSettings().height;

        glViewport(0, 0, width / 2, height);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, cylinder->getIndices().size(), GL_UNSIGNED_INT, 0);

        glViewport(width / 2, 0, width / 2, height);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, cylinder->getIndices().size(), GL_UNSIGNED_INT, 0);
    }
};

int main() {
    try {
        initOpenGL();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
        return -1;
    }

    DisplayCylinder app;
    try {
        app.initApp(1280, 720, false, false);
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }

    app.run();

    return 0;
}

//
//  Callbacks
//

void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.zoom(ypos);
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

    camera.rotate(xoffset, yoffset, 0.0);
}
