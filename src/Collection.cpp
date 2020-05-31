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
void Collection::translate(const glm::vec3& offset) {
	for (auto& object : objects) {
		object->translate(offset);
	}
}
void Collection::rotate(float angle, const std::optional<glm::vec3>& axis) {
	for (auto& object : objects) {
		object->rotate(angle, axis);
	}
}
void Collection::scale(const glm::vec3& value) {
	for (auto& object : objects) {
		object->scale(value);
	}
}
void Collection::rotate2(const std::optional<glm::vec3>& axis) {
	for (auto& object : objects) {
		object->rotate2(axis);
	}
}