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
void Compound::translateTo(const glm::vec3& offset) {

}
void Compound::rotateTo(float angle, const std::optional<glm::vec3>& axis) {

}
void Compound::scaleTo(const glm::vec3& value) {

}

void Compound::translateBy(const glm::vec3& offset) {
	for (auto& collection : collections) {
		collection->translateBy(offset);
	}
}
void Compound::rotateBy(float angle, const std::optional<glm::vec3>& axis) {
	for (auto& collection : collections) {
		collection->rotateBy(angle, axis);
	}
}
void Compound::scaleBy(const glm::vec3& value) {
	for (auto& collection : collections) {
		collection->scaleBy(value);
	}
}

void Compound::rotateAroundCW(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& collection : collections) {
		collection->rotateAroundCW(angle, axis);
	}
}

void Compound::rotateAroundCCW(float angle, const std::optional<glm::vec3>& axis)
{
	for (auto& collection : collections) {
		collection->rotateAroundCCW(angle, axis);
	}
}