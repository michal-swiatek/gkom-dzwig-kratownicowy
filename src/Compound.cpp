/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#include "Compound.h"

void Compound::draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const {
	for (auto& collection : collections) {
		collection->draw(camera, shaderID);
	}
}
void Compound::translate(const glm::vec3& offset) {
	for (auto& collection : collections) {
		collection->translate(offset);
	}
}
void Compound::rotate(float angle, const std::optional<glm::vec3>& axis) {
	for (auto& collection : collections) {
		collection->rotate(angle, axis);
	}
}
void Compound::scale(const glm::vec3& value) {
	for (auto& collection : collections) {
		collection->scale(value);
	}
}
void Compound::rotate2(const std::optional<glm::vec3>& axis) {
	for (auto& collection : collections) {
		collection->rotate2(axis);
	}
}