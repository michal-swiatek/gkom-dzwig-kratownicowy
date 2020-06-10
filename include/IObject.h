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
#include "Window.h"

class IObject
{
public:
	virtual void draw(cam::Camera &camera, int shaderID) const = 0;

	virtual void rotateLocal(float angle, const std::optional<glm::vec3>& axis) = 0;
	virtual void translateLocal(const glm::vec3& offset) = 0;
	virtual void scaleLocal(const glm::vec3& offset) = 0;

	virtual void rotateWorld(float angle, const std::optional<glm::vec3>& axis) = 0;
	virtual void translateWorld(const glm::vec3& offset) = 0;
	virtual void scaleWorld(const glm::vec3& offset) = 0;
};

#endif // IOBJECT_H