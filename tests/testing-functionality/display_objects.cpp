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
#include "Cuboid.h"

class DisplayCylinder : public Core
{
    using uint = unsigned int;

private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Cylinder> cylinder;
	std::unique_ptr<Cuboid> cuboid;

    uint VBO, VAO, EBO;

public:
    DisplayCylinder() : Core("Display cylinder"), VBO(0), VAO(0), EBO(0)
    {
        cylinder = std::make_unique<Cylinder>(1.0f, 0.5f, 2.0, 25, 2);
		//cuboid = std::make_unique<Cuboid>(1.0f, 1.0f, 1.0f);
        shader = std::make_unique<Shader>("shaders/flat.vs.glsl", "shaders/flat.fs.glsl");
    }

    void init() override
    {
        mainCamera->getSettings().movementSpeed /= 2;

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, cylinder->getVertices().size() * sizeof(float), cylinder->getVertices().data(), GL_STATIC_DRAW);
        //glBufferData(GL_ARRAY_BUFFER, cuboid->getVertices().size() * sizeof(float), cuboid->getVertices().data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinder->getIndices().size() * sizeof(unsigned int), cylinder->getIndices().data(), GL_STATIC_DRAW);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, cuboid->getIndices().size() * sizeof(unsigned int), cuboid->getIndices().data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);

        shader->use();

        float color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
        glUniform4fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, color);
    }
    void draw() override
    {
        shader->setMatrix4f("mvp", mainCamera->getViewProjectionMatrix());

        auto width = mainWindow->getWindowSettings().width;
        auto height = mainWindow->getWindowSettings().height;

        glViewport(0, 0, width / 2, height);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, cylinder->getIndices().size(), GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, cuboid->getIndices().size(), GL_UNSIGNED_INT, 0);

        glViewport(width / 2, 0, width / 2, height);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, cylinder->getIndices().size(), GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, cuboid->getIndices().size(), GL_UNSIGNED_INT, 0);

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
