/*
 *  Created by Boguslaw Malewski, Rafal Uzarowicz
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Camera.h"
#include "Shader.h"
#include "window.h"
#include "IObject.h"
#include "Model.h"

class Object : public IObject
{
protected:

	std::shared_ptr<Model>  model;

	unsigned int textureID;

	Transform transform;

	glm::mat4 modelMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;

public:

	Object(std::shared_ptr<Model> mod, unsigned int textureID);

	void updateModel();



	void translateTo(const glm::vec3& offset) override;
	void rotateTo(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleTo(const glm::vec3& value) override;

	void translateBy(const glm::vec3& offset) override;
	void rotateBy(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleBy(const glm::vec3& value) override;

	void translateBy2(const glm::vec3& offset) override;
	void rotateBy2(float angle, const std::optional<glm::vec3>& axis) override;
	void scaleBy2(const glm::vec3& value) override;

	void rotateBySpecial(float angle, const std::optional<glm::vec3>& axis);
	void translateBySpecial(const glm::vec3& offset);
	void scaleBySpecial(const glm::vec3& offset);

	void rotateBySpecial2(float angle, const std::optional<glm::vec3>& axis);
	void translateBySpecial2(const glm::vec3& offset);
	void scaleBySpecial2(const glm::vec3& offset);


	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const override;
};
#endif // !OBJECT_H