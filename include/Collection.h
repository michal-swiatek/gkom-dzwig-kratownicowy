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
	std::vector<std::unique_ptr<IObject>> objects;


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

	void translateBy2(const glm::vec3& offset) override;
	void rotateBy2(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleBy2(const glm::vec3& value) override;

	void rotateBySpecial(float angle, const std::optional<glm::vec3>& axis) override;
	void translateBySpecial(const glm::vec3& offset) override;
	void scaleBySpecial(const glm::vec3& offset)override;

	void rotateBySpecial2(float angle, const std::optional<glm::vec3>& axis) override;
	void translateBySpecial2(const glm::vec3& offset) override;
	void scaleBySpecial2(const glm::vec3& offset)override;

	void updateModel() override;
};
#endif // !COLLECTION_H