/*
 *  Created by Boguslaw Malewski, Rafal Uzarowicz
 */
#include <GL/glew.h>
#include "Model.h"

void Model::init()
{
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Model::del() {
	if (this->VAO > 0) {
		glDeleteVertexArrays(1, &VAO);
	}
	if (this->VBO > 0) {
		glDeleteBuffers(1, &VBO);
	}
	if (this->EBO > 0) {
		glDeleteBuffers(1, &EBO);
	}
}

void Model::use() {
	glBindVertexArray(this->VAO);
}

std::vector<float> Model::getVertices() {
	return this->vertices;
}

std::vector<unsigned int> Model::getIndices() {
	return this->indices;
}

void Model::clearVectors() {
	this->indices.clear();
	this->vertices.clear();
}