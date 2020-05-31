

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OldObject.h"
#include "Shader.h"
#include "Camera.h"
#include "window.h"
#include <memory>
/*
created by BM Wzorowane na Box.cpp z learnopengl by Micha� �wi�tek
*/



void OldObject::init()
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


void  OldObject::draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const
{
    glm::mat4 projection = glm::perspective(camera->getZoom(), (float)windowSettings.width / windowSettings.height, 0.1f, 100.0f);

    glm::mat4 view = camera->getViewMatrix();

    shader->use();
    glm::mat4 mv = view * translationMatrix * scaleMatrix * rotationMatrix;
    shader->setVector3f("lightPos", glm::vec3(view * glm::vec4(glm::vec3(10.0f), 1.0f)));
    shader->setMatrix4f("mv", mv);
    shader->setMatrix4f("mvp", projection * mv);
    shader->setMatrix3f("mvInvTrans", glm::mat3(glm::transpose(glm::inverse(mv))));

    glBindVertexArray(VAO);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glViewport(0, 0, windowSettings.width, windowSettings.height);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

 


std::vector<float> OldObject::getVertices() {
	return this->vertices;
}

std::vector<unsigned int> OldObject::getIndices() {
	return this->indices;
}

OldObject::OldObject(const Transform& transform, const glm::vec4& color) : transform(transform), color(color)
{
    rotationMatrix = glm::mat4(1.0f);
    translationMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
 //   modelMatrix = glm::translate(modelMatrix, transform.position);
  //  modelMatrix = glm::scale(modelMatrix, transform.scale);
}

OldObject::OldObject(const glm::vec3& position, const glm::vec4& color) : transform(Transform(position)), color(color)
{
    rotationMatrix = glm::mat4(1.0f);
    translationMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
  // modelMatrix = glm::translate(modelMatrix, position);
   // modelMatrix = glm::scale(modelMatrix, transform.scale);
}

void OldObject::updateMatrices(const OptionalMat4& projection)
{
    if (projection)
        projectionMatrix = *projection;
}



void OldObject::translate(const glm::vec3& offset)
{
    transform.position = offset;

    translationMatrix = glm::translate(glm::mat4(1.0f), offset)*translationMatrix;
}

void OldObject::rotate(float angle, const std::optional<glm::vec3>& axis)
{
    if (axis)
        transform.rotation = *axis;

    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), transform.rotation)*rotationMatrix;
}

void OldObject::rotate2( const std::optional<glm::vec3>& axis)
{
    if (axis)
        transform.rotation = *axis;

    rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), transform.rotation)*rotationMatrix;
}

void OldObject::scale(const glm::vec3& value)
{
    transform.scale = value;

    scaleMatrix = glm::scale(glm::mat4(1.0f), value)*  scaleMatrix ;
}













//  Color
const glm::vec4& OldObject::getColor() const
{
    return color;
}

void OldObject::setColor(const glm::vec4& newColor)
{
    color = newColor;
}
void OldObject::clearVectors() {
	this->vertices.clear();
	this->indices.clear();
}