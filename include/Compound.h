/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef COMPOUND_H
#define COMPOUND_H

#include "Collection.h"
#include "IObject.h"

class Compound : IObject
{
	std::vector<std::unique_ptr<Collection>> collections;

public:
	Compound() {

	}
	void addCollection(std::unique_ptr<Collection> collection) {
		collections.push_back(std::move(collection));
	}
	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const override;

	void translateTo(const glm::vec3& offset) override;
	void rotateTo(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleTo(const glm::vec3& value) override;

	void translateBy(const glm::vec3& offset) override;
	void rotateBy(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleBy(const glm::vec3& value) override;

	void rotateAroundCW(float angle, const std::optional<glm::vec3>& axis);
	void rotateAroundCCW(float angle, const std::optional<glm::vec3>& axis);
};
#endif // !COMPOUND_H