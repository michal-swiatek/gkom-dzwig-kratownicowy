

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "window.h"
#include <memory>


void Object::init()
{
    initShader();

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void  Object::draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings) const
{
    glm::mat4 projection = glm::perspective(camera->getZoom(), (float)windowSettings.width / windowSettings.height, 0.1f, 100.0f);

    glm::mat4 view = camera->getViewMatrix();

    shader->use();
    shader->setVector3f("lightPos", glm::vec3(view * glm::vec4(glm::vec3(10.0f), 1.0f)));
    shader->setMatrix4f("mv", view);
    shader->setMatrix4f("mvp", projection * view);
    shader->setMatrix3f("mvInvTrans", glm::mat3(glm::transpose(glm::inverse(view))));

    glBindVertexArray(VAO);

     // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glViewport(0, 0, windowSettings.width, windowSettings.height);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
}

std::vector<float> Object::getVertices() {
	return this->vertices;
}

std::vector<unsigned int> Object::getIndices() {
	return this->indices;
}

