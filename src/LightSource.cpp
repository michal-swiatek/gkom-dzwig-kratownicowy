//
// Created by seamel on 08.06.2020.
//
#include <GL/glew.h>
#include "LightSource.h"

void LightSource::draw(cam::Camera &camera, int shaderID) const {

model->use();
glm::mat4 projection = camera.getProjectionMatrix();

glm::mat4 view = camera.getViewMatrix();

glm::mat4 mv = view * modelMatrix;
glm::mat4 matrix = projection * mv;
glUniformMatrix4fv(glGetUniformLocation(shaderID, "mvp"), 1, GL_FALSE, glm::value_ptr(matrix));


glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glDrawElements(GL_TRIANGLES, model->getIndices().size(), GL_UNSIGNED_INT, 0);
}

LightSource::LightSource(const std::shared_ptr<Model> &mod) : Object(mod, 0) {}
