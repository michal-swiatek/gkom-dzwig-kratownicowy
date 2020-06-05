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
//	rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), *axis);

}




void Object::rotateAroundCW(float angle, const std::optional<glm::vec3>& axis)
{

	float s = sin(angle); // angle is in radians
	float c = cos(angle); // angle is in radians

	float xnew = axis->x * c + axis->y * s;
	float ynew = -axis->x * s + axis->y * c;
//	translateBy(glm::vec3(transform.position.x - xnew, transform.position.y - ynew, 0.0f));

}
/*
float a, b, c, d;
d = glfwGetTime();
a = (float)cos(d) * 3;

b = (float)sin(d) * 3;

c = ((float)atan2(b, a) * (180.0 / 3.141592653589793238463));
std::cout << c << std::endl;
//	compound->rotateBy(c, glm::vec3(0.0, 0.0, 1.0));
compound->rotateBy(c, glm::vec3(0.0, 0.0, 1.0));
//	compound->translateBy(glm::vec3(a, 5.0f + b, 0.0f));
//	compound->translateBy(glm::vec3(a, b, 0.0f));
compound->translateBy(glm::vec3(a, b, 0.0));
*/
void Object::rotateAroundCCW(float angle, const std::optional<glm::vec3>& axis)
{

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
