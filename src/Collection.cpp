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

void Collection::translateTo(const glm::vec3& offset) {

}
void Collection::rotateTo(float angle, const std::optional<glm::vec3>& axis) {

}
void Collection::scaleTo(const glm::vec3& value) {
	for (auto& object : objects) {
		object->scaleTo(value);
	}
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


void Collection::translateBy2(const glm::vec3& offset) {
	for (auto& object : objects) {
		object->translateBy2(offset);
	}
}
void Collection::rotateBy2(float angle, const std::optional<glm::vec3>& axis) {
	for (auto& object : objects) {
		object->rotateBy2(angle, axis);
	}
}
void Collection::scaleBy2(const glm::vec3& value) {
	for (auto& object : objects) {
		object->scaleBy2(value);
	}
}



void Collection::rotateBySpecial(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& object : objects) {
		object->rotateBySpecial( angle, *axis);
	}
}
void Collection::translateBySpecial(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->translateBySpecial(offset);
	}
}
void Collection::scaleBySpecial(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->scaleBySpecial(offset);
	}
}


void Collection::rotateBySpecial2(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& object : objects) {
		object->rotateBySpecial2(angle, *axis);
	}
}
void Collection::translateBySpecial2(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->translateBySpecial2(offset);
	}
}
void Collection::scaleBySpecial2(const glm::vec3& offset)
{
	for (auto& object : objects) {
		object->scaleBySpecial2(offset);
	}
}



void Collection::updateModel()
{
	for (auto& object : objects) {
		object->updateModel();
	}
}