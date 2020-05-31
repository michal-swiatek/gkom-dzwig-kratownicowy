/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef COLLECTION_H
#define COLLECTION_H

#include "Object.h"
#include "IObject.h"
#include "Shader.h"

#include <vector>

class Collection : IObject
{
	std::shared_ptr<Model> model;
	std::vector<std::unique_ptr<Object>> objects;
public:
	Collection(std::shared_ptr<Model> model) {
		this->model = model;
	}
	void addObject(std::unique_ptr<Object> object) {
		object->setModel(this->model);
		objects.push_back(std::move(object));
	}
	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const override;
	void translate(const glm::vec3& offset) override;
	void rotate(float angle, const std::optional<glm::vec3>& axis) override;
	void scale(const glm::vec3& value) override;
	void rotate2(const std::optional<glm::vec3>& axis) override;
};
#endif // !COLLECTION_H