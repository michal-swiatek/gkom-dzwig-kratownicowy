

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "window.h"
#include <memory>
/*
created by BM Wzorowane na Box.cpp z learnopengl by Micha³ Œwi¹tek
*/


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


void  Object::draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const
{
    glm::mat4 projection = glm::perspective(camera->getZoom(), (float)windowSettings.width / windowSettings.height, 0.1f, 100.0f);

    glm::mat4 view = camera->getViewMatrix();

    shader->use();
    glm::mat4 mv = view * modelMatrix;
    shader->setVector3f("lightPos", glm::vec3(mv * glm::vec4(glm::vec3(10.0f), 1.0f)));
    shader->setMatrix4f("mv", mv);
    shader->setMatrix4f("mvp", projection * mv);
    shader->setMatrix3f("mvInvTrans", glm::mat3(glm::transpose(glm::inverse(view * modelMatrix))));

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

Object::Object(const Transform& transform, const glm::vec4& color) : transform(transform), color(color)
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

Object::Object(const glm::vec3& position, const glm::vec4& color) : transform(Transform(position)), color(color)
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

void Object::updateMatrices(const OptionalMat4& projection)
{
    if (projection)
        projectionMatrix = *projection;
}



void Object::translate(const glm::vec3& offset)
{
    transform.position += offset;

    modelMatrix = glm::translate(modelMatrix, offset);
}

void Object::rotate(float angle, const std::optional<glm::vec3>& axis)
{
    if (axis)
        transform.rotation = *axis;

    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), transform.rotation);
    modelMatrix = glm::translate(modelMatrix, -transform.position);
}

void Object::scale(const glm::vec3& value)
{
    transform.scale *= value;

    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, value);
    modelMatrix = glm::translate(modelMatrix, -transform.position);
}

void Object::setPosition(const glm::vec3& position)
{
    modelMatrix = glm::translate(modelMatrix, -transform.position);
    transform.position = position;
    modelMatrix = glm::translate(modelMatrix, transform.position);
}

void Object::setRotation(float angle, const glm::vec3& axis)
{
    transform.rotation = axis;

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), transform.rotation);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

void Object::setScale(const glm::vec3& scale)
{
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::translate(modelMatrix, -transform.position);

    transform.scale = scale;

    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::translate(modelMatrix, -transform.position);
}

//  Transform
const Transform& Object::getTransform() const
{
    return transform;
}

void Object::setTransform(const Transform& newTransform)
{
    transform = newTransform;

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

const glm::mat4& Object::getModelMatrix() const
{
    return modelMatrix;
}

void Object::setModelMatrix(const glm::mat4& newModelMatrix)
{
    modelMatrix = newModelMatrix;
}

//  Color
const glm::vec4& Object::getColor() const
{
    return color;
}

void Object::setColor(const glm::vec4& newColor)
{
    color = newColor;
}
