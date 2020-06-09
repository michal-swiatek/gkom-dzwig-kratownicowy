/*
 *  Created by Boguslaw Malewski, Rafal Uzarowicz
 */

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "Window.h"

class Model
{
protected:
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	GLuint VBO, VAO, EBO;

	Transform transform;

	static const unsigned int paramNum = 8;

	void init();

	void del();

	void clearVectors();

public:
	Model() : VBO(0), VAO(0), EBO(0) {
		this->init();
	}
	~Model() {
		this->del();
	}

	void use();

	std::vector<float> getVertices();
	std::vector<unsigned int> getIndices();

	GLuint getVBO() { return this->VBO; }
	GLuint getVAO() { return this->VAO; }
	GLuint getEBO() { return this->EBO; }

};
#endif // !MODEL_H