/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#include "Collection.h"

void Collection::draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const {
	model->use();
	for (auto& object : objects) {
		object->draw(camera, shaderID);
	}
}

void Collection::translateTo(const glm::vec3& offset) {

}
void Collection::rotateTo(float angle, const std::optional<glm::vec3>& axis) {

}
void Collection::scaleTo(const glm::vec3& value) {

}

void Collection::translateBy(const glm::vec3& offset) {
	for (auto& object : objects) {
		object->translateBy(offset);
	}
}
void Collection::rotateBy(float angle, const std::optional<glm::vec3>& axis) {
	for (auto& object : objects) {
		object->rotateBy(angle, axis);
	}
}
void Collection::scaleBy(const glm::vec3& value) {
	for (auto& object : objects) {
		object->scaleBy(value);
	}
}

void Collection::rotateAroundCW(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& object : objects) {
		object->rotateAroundCW(angle, axis);
	}

}

void Collection::rotateAroundCCW(float angle, const std::optional<glm::vec3>& axis)
{

}