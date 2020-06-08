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
#include "Window.h"
#include "IObject.h"
#include "Model.h"

class Object : public IObject
{
protected:

	std::shared_ptr<Model>  model;

	unsigned int textureID;

	Transform transform;

	glm::mat4 modelMatrix;


public:

	Object(std::shared_ptr<Model> mod, unsigned int textureID);


	void rotateLocal(float angle, const std::optional<glm::vec3>& axis);
	void translateLocal(const glm::vec3& offset);
	void scaleLocal(const glm::vec3& offset);

	void rotateWorld(float angle, const std::optional<glm::vec3>& axis);
	void translateWorld(const glm::vec3& offset);
	void scaleWorld(const glm::vec3& offset);


	void draw(cam::Camera &camera, int shaderID) const override;
};
#endif // !OBJECT_H