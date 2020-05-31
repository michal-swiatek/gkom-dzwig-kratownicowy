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
	void translate(const glm::vec3& offset) override;
	void rotate(float angle, const std::optional<glm::vec3>& axis) override;
	void scale(const glm::vec3& value) override;
	void rotate2(const std::optional<glm::vec3>& axis) override;
};
#endif // !COMPOUND_H