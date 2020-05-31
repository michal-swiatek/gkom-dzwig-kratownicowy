/*
 *  Created by Boguslaw Malewski, Rafal Uzarowicz
 */

#include "Object.h"

void  Object::draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const
{

	glm::mat4 projection = camera->getProjectionMatrix();

	glm::mat4 view = camera->getViewMatrix();

	glm::mat4 mv = view * translationMatrix * scaleMatrix * rotationMatrix;
	glm::mat4 matrix = projection * mv;

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "mvp"), 1, GL_FALSE, glm::value_ptr(matrix));

	glUniform1i(glGetUniformLocation(shaderID, "ourTexture"), this->textureID);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, model->getIndices().size(), GL_UNSIGNED_INT, 0);
}



Object::Object(unsigned int textureID) : transform(Transform(glm::vec3(0.0f))), color(glm::vec4(1.0f))
{
	rotationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	this->textureID = textureID;
}

void Object::setModel(std::shared_ptr<Model> model) {
	this->model = model;
}


void Object::updateMatrices(const OptionalMat4& projection)
{
	if (projection)
		projectionMatrix = *projection;
}



void Object::translate(const glm::vec3& offset)
{
	transform.position = offset;

	translationMatrix = glm::translate(glm::mat4(1.0f), offset)*translationMatrix;
}

void Object::rotate(float angle, const std::optional<glm::vec3>& axis)
{
	if (axis)
		transform.rotation = *axis;

	rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), transform.rotation)*rotationMatrix;
}

void Object::rotate2(const std::optional<glm::vec3>& axis)
{
	if (axis)
		transform.rotation = *axis;

	rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), transform.rotation)*rotationMatrix;
}

void Object::scale(const glm::vec3& value)
{
	transform.scale = value;

	scaleMatrix = glm::scale(glm::mat4(1.0f), value)*  scaleMatrix;
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
