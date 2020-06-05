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

void Object::updateModel() {
	modelMatrix = rotationMatrix * translationMatrix * scaleMatrix;
}

Object::Object(std::shared_ptr<Model> mod,unsigned int textureID) : transform(Transform(glm::vec3(0.0f))), color(glm::vec4(1.0f))
{
	model = mod;
	modelMatrix = glm::mat4(1.0f);
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
Transform Object::getTransform() {
	return transform;
}


void Object::translateTo(const glm::vec3& offset)
{
	transform.position = offset;

	translationMatrix = glm::translate(glm::mat4(1.0f), offset);
}

void Object::rotateTo(float angle, const std::optional<glm::vec3>& axis)
{
	if (axis)
		transform.rotation = *axis;

	rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), transform.rotation);
}

void Object::scaleTo(const glm::vec3& value)
{
	transform.scale = value;

	scaleMatrix = glm::scale(glm::mat4(1.0f), value);
}

void Object::scaleBy(const glm::vec3& value)
{
	transform.scale *= value;

	scaleMatrix = glm::scale(scaleMatrix, value);
}

void Object::translateBy(const glm::vec3& offset)
{
	transform.position += offset;

	translationMatrix = glm::translate(translationMatrix,  offset);

}


void Object::rotateBy(float angle, const std::optional<glm::vec3>& axis)
{
	if (axis)
		transform.rotation += *axis;

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), *axis);
}


void Object::rotateBySpecial(float angle, const std::optional<glm::vec3>& axis)
{
//	if (axis)
//		transform.rotation += *axis;

	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), *axis);
}

void Object::translateBySpecial(const glm::vec3& offset)
{
//	transform.position += offset;

	modelMatrix = glm::translate(modelMatrix,  offset);

}
void Object::translateBySpecial2(const glm::vec3& offset)
{
	//	transform.position += offset;

	modelMatrix = glm::translate(modelMatrix, offset);

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
