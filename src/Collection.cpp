/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#include "Collection.h"

void Collection::draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const {
	for (auto& object : objects) {
		object->draw(camera, shaderID);
	}
}

void Collection::rotateLocal(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& object : objects) {
		object->rotateLocal( angle, *axis);
	}
}
void Collection::translateLocal(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->translateLocal(offset);
	}
}
void Collection::scaleLocal(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->scaleLocal(offset);
	}
}


void Collection::rotateWorld(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& object : objects) {
		object->rotateWorld(angle, *axis);
	}
}
void Collection::translateWorld(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->translateWorld(offset);
	}
}
void Collection::scaleWorld(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->scaleWorld(offset);
	}
}