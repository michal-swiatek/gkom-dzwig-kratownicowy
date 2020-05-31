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

class Object : IObject
{
protected:

	std::shared_ptr<Model>  model;

	unsigned int textureID;

	Transform transform;

	glm::mat4 rotationMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 scaleMatrix;

	glm::mat4 projectionMatrix;
	glm::vec4 color;

	using OptionalMat4 = std::optional<glm::mat4>;


public:

	Object(unsigned int textureID);

	void setModel(std::shared_ptr<Model> model);

	void updateMatrices(const OptionalMat4& projection = {});

	void translate(const glm::vec3& offset) override;
	void rotate(float angle, const std::optional<glm::vec3>& axis) override;
	void scale(const glm::vec3& value) override;

	void rotate2(const std::optional<glm::vec3>& axis) override;

	//  Color
	[[nodiscard]] const glm::vec4& getColor() const;
	void setColor(const glm::vec4& newColor);

	using OptionalMat4 = std::optional<glm::mat4>;

	void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const override;
};
#endif // !OBJECT_H