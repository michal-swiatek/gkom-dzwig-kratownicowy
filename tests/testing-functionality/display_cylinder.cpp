/*
 *  Created by michal-swiatek on 19.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 */

#include "Core.h"

#include <memory>
#include <iostream>

#include "Shader.h"
#include "Cylinder.h"

class DisplayCylinder : public Core
{
    using uint = unsigned int;

private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Cylinder> cylinder;

    uint VBO, VAO, EBO;

public:
    DisplayCylinder() : Core("Display cylinder")
    {
        cylinder = std::make_unique<Cylinder>(0.5f, 0.0f, 0.5, 4, 3);
        shader = std::make_unique<Shader>("shaders/flat.vs.glsl", "shaders/flat.fs.glsl");
    }

    void init() override
    {
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

    void draw() override
    {
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
        app.initApp();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }

    app.run();

    return 0;
}
