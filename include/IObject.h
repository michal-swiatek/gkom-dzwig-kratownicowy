/*
 *  Created by Boguslaw Malewski, Rafal Uzarowicz
 */

#ifndef IOBJECT_H
#define IOBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Camera.h"
#include "Shader.h"
#include "window.h"

class IObject
{
public:
	virtual void draw(std::unique_ptr<cam::Camera>& camera, int shaderID) const = 0;
	//
	virtual void translateTo(const glm::vec3& offset) = 0;
	virtual void rotateTo(float angle, const std::optional<glm::vec3>& axis) = 0;
	virtual void scaleTo(const glm::vec3& value) = 0;

	virtual void translateBy(const glm::vec3& offset) = 0;
	virtual void rotateBy(float angle, const std::optional<glm::vec3>& axis) = 0;
	virtual void scaleBy(const glm::vec3& value) = 0;

	virtual void rotateBySpecial(float angle, const std::optional<glm::vec3>& axis) = 0;
	virtual void translateBySpecial(const glm::vec3& offset) = 0;
	virtual void translateBySpecial2(const glm::vec3& offset) = 0;


};

#endif // IOBJECT_H