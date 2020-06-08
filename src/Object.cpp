/*
 *  Created by Boguslaw Malewski, Rafal Uzarowicz
 */

#include "Object.h"

void  Object::draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const
{
	model->use();
	glm::mat4 projection = camera->getProjectionMatrix();

	glm::mat4 view = camera->getViewMatrix();

	glm::mat4 mv = view * modelMatrix;
	glm::mat4 matrix = projection * mv;

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "mvp"), 1, GL_FALSE, glm::value_ptr(matrix));

	glUniform1i(glGetUniformLocation(shaderID, "ourTexture"), this->textureID);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, model->getIndices().size(), GL_UNSIGNED_INT, 0);
}



Object::Object(std::shared_ptr<Model> mod,unsigned int textureID) : transform(Transform(glm::vec3(0.0f)))
{
	model = mod;
	modelMatrix = glm::mat4(1.0f);
	this->textureID = textureID;
}



void Object::translateLocal(const glm::vec3& offset)
{
	modelMatrix = glm::translate(modelMatrix, offset);
}
void Object::rotateLocal(float angle, const std::optional<glm::vec3>& axis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), *axis);
}
void Object::scaleLocal(const glm::vec3& offset)
{
	modelMatrix = glm::scale(modelMatrix, offset);
}

void Object::translateWorld(const glm::vec3& offset)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), offset) * modelMatrix;
}
void Object::rotateWorld(float angle, const std::optional<glm::vec3>& axis)
{
	modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), *axis) * modelMatrix;
}
void Object::scaleWorld(const glm::vec3& offset)
{
	modelMatrix = glm::scale(glm::mat4(1.0f), offset) * modelMatrix;
}