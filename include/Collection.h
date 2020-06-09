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

class Collection : public IObject
{
public:
	Collection(){}

	std::vector<std::shared_ptr<IObject>> objects;


	void addObject(std::shared_ptr<IObject> object)
	{
		objects.push_back(object);
	}

	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const override;

	void rotateLocal(float angle, const std::optional<glm::vec3>& axis) override;
	void translateLocal(const glm::vec3& offset) override;
	void scaleLocal(const glm::vec3& offset)override;

	void rotateWorld(float angle, const std::optional<glm::vec3>& axis) override;
	void translateWorld(const glm::vec3& offset) override;
	void scaleWorld(const glm::vec3& offset)override;
};
#endif // !COLLECTION_H