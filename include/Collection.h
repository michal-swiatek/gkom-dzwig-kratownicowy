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
	std::vector<std::unique_ptr<IObject>> objects;
public:

	void addObject(std::unique_ptr<IObject> object) 
	{
		objects.push_back(std::move(object));

	}

	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const override;

	void translateTo(const glm::vec3& offset) override;
	void rotateTo(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleTo(const glm::vec3& value) override;

	void translateBy(const glm::vec3& offset) override;
	void rotateBy(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleBy(const glm::vec3& value) override;

	void rotateAroundCW(float angle, const std::optional<glm::vec3>& axis) override;
	void rotateAroundCCW(float angle, const std::optional<glm::vec3>& axis) override;
};
#endif // !COLLECTION_H