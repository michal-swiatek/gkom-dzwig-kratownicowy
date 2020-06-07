/*
 *  Created by michal-swiatek on 19.05.2020.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 *
 *  TODO: fix strange specular highlights in phong_model shader
 */

#include <GL/glew.h>

#include "Core.h"
#include <memory>
#include <iostream>
#include <glfw3.h>

#include "Shader.h"

#include "Cylinder.h"
#include "SkyBox.h"
#include "PhongMaterial.h"

class DisplayCylinder : public Core
{
    using uint = unsigned int;

private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Cylinder> cylinder;
    std::unique_ptr<SkyBox> skyBox;
    std::unique_ptr<PhongMaterial> material;

    uint VBO, VAO, EBO;

public:
    DisplayCylinder() : Core("Display cylinder"), VBO(0), VAO(0), EBO(0)
    {
        cylinder = std::make_unique<Cylinder>(1.0f, 0.5f, 2.0, 25, 2);
        shader = std::make_unique<Shader>("shaders/phong_model.vs.glsl", "shaders/phong_model.fs.glsl");
        skyBox = std::make_unique<SkyBox>(glm::vec4(0.5,0.5,0.5,1.0));
        material = std::make_unique<PhongMaterial>(glm::vec4(1.0f, 0.5f, 0.3f, 1.0f), glm::vec4(0.5f, 0.5, 0.5, 1.0f));
    }

    void init() override
    {
        int a = 23343453455724;
        skyBox->init();
        mainCamera->getSettings().movementSpeed /= 2;
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

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        shader->use();

        shader->setVector3f("dirLight.direction", glm::vec3(5.0f, 5.0f, 5.0f));
        shader->setVector3f("dirLight.ambient", glm::vec3(0.1f));
        shader->setVector3f("dirLight.diffuse", glm::vec3(1.0f));
        shader->setVector3f("dirLight.specular", glm::vec3(0.5f));

        shader->setVector3f("pointLights[0].direction", glm::vec3(7.0f, 5.0f, 5.0f));
        shader->setVector3f("pointLights[0].ambient", glm::vec3(0.1f));
        shader->setVector3f("pointLights[0].diffuse", glm::vec3(1.0f));
        shader->setVector3f("pointLights[0].specular", glm::vec3(0.5f));
        shader->setFloat("pointLights[0].constant", 1.0);
        shader->setFloat("pointLights[0].linear", 0.14);
        shader->setFloat("pointLights[0].quadratic", 0.07);

        shader->setMatrix4f("model", glm::mat4(1.0f));
        shader->setMatrix3f("modelInvTrans", glm::mat3(glm::transpose(glm::inverse(glm::mat4(1.0f)))));


        material->applyMaterial(*shader);


//        float color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
//        glUniform4fv(glGetUniformLocation(shader->getProgramID(), "color"), 1, color);
    }

    void draw() override
    {
        glBindVertexArray(VAO);
        shader->use();

        shader->setVector3f("eyePos", mainCamera->getTransform().position);
        shader->setMatrix4f("mvp", mainCamera->getViewProjectionMatrix());

        auto width = mainWindow->getWindowSettings().width;
        auto height = mainWindow->getWindowSettings().height;

        glViewport(0, 0, width, height);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, cylinder->getIndices().size(), GL_UNSIGNED_INT, 0);

        skyBox->draw(mainCamera);
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