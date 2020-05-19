#include "../include/Cylinder.h"

/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

Cylinder::Cylinder(float bR, float tR, float h, int secNum, int staNum) {
	this->setParams(bR, tR, h, secNum, staNum);
}

void Cylinder::setParams(float bR, float tR, float h, int secNum, int staNum) {
	if (bR <= 0 && tR <= 0) {
		std::cout << "Zle promienie" << '\n';
	}
	else if (h <= 0) {
		std::cout << "Zla wysokosc" << '\n';
	}
	else if (secNum < 3) {
		std::cout << "Zla liczba sectorow" << '\n';
	}
	else if (staNum < 1) {
		std::cout << "Zla liczba stackow" << '\n';
	}
	else {
		this->baseRadius = bR;
		this->topRadius = tR;
		this->height = h;
		this->sectorsNum = secNum;
		this->stacksNum = staNum;

		this->clearVectors();

		this->generateCylinder();
	}
}

std::vector<float> Cylinder::getVertices() {
	return this->vertices;
}

std::vector<unsigned int> Cylinder::getIndices() {
	return this->indices;
}

void Cylinder::clearVectors() {
	this->vertices.clear();
	this->indices.clear();
}

void Cylinder::generateCylinder() {
	this->generateVertices();
	this->generateIndices();
}

std::vector<float> Cylinder::generateBaseCircleVertices() {
	float angleStep = 2 * PI / this->sectorsNum;

	std::vector<float> circleVertices;
	circleVertices.push_back(0.0f);
	circleVertices.push_back(0.0f);
	circleVertices.push_back(-this->height / 2.0f);
	if (this->baseRadius > 0) {
		for (int i = 0; i < this->sectorsNum; ++i) {
			circleVertices.push_back(this->baseRadius*cos(i*angleStep));
			circleVertices.push_back(this->baseRadius*sin(i*angleStep));
			circleVertices.push_back(-this->height / 2.0f);
		}
	}
	return circleVertices;
}

std::vector<float> Cylinder::generateTopCircleVertices() {
	float angleStep = 2 * PI / this->sectorsNum;

	std::vector<float> circleVertices;
	circleVertices.push_back(0.0f);
	circleVertices.push_back(0.0f);
	circleVertices.push_back(this->height / 2.0f);
	if (this->topRadius > 0.0f) {
		for (int i = 0; i < this->sectorsNum; ++i) {
			circleVertices.push_back(this->topRadius*cos(i*angleStep));
			circleVertices.push_back(this->topRadius*sin(i*angleStep));
			circleVertices.push_back(this->height / 2.0f);
		}
	}
	return circleVertices;
}

void Cylinder::generateVertices() {
	std::vector<float> topCircleVertices = generateTopCircleVertices();
	std::vector<float> baseCircleVertices = generateBaseCircleVertices();

	// Add top circle vertices
	for (unsigned int i = 0; i < topCircleVertices.size(); ++i) {
		this->vertices.push_back(topCircleVertices[i]);
	}

	// Count steps for each coords.
	std::vector<std::vector<float>> verticesStep;
	if (this->topRadius <= 0.0f) {
		for (int i = 0; i < this->sectorsNum; ++i) {
			verticesStep.push_back(std::vector<float>());
			verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3] - topCircleVertices[0]) / this->stacksNum);
			verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 1] - topCircleVertices[1]) / this->stacksNum);
			verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 2] - topCircleVertices[2]) / this->stacksNum);
		}
	}
	else if (this->baseRadius <= 0.0f) {
		for (int i = 0; i < this->sectorsNum; ++i) {
			verticesStep.push_back(std::vector<float>());
			verticesStep[i].push_back((baseCircleVertices[0] - topCircleVertices[(i + 1) * 3]) / this->stacksNum);
			verticesStep[i].push_back((baseCircleVertices[1] - topCircleVertices[(i + 1) * 3 + 1]) / this->stacksNum);
			verticesStep[i].push_back((baseCircleVertices[2] - topCircleVertices[(i + 1) * 3 + 2]) / this->stacksNum);
		}
	}
	else {
		for (int i = 0; i < this->sectorsNum; ++i) {
			verticesStep.push_back(std::vector<float>());
			verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3] - topCircleVertices[(i + 1) * 3]) / this->stacksNum);
			verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 1] - topCircleVertices[(i + 1) * 3 + 1]) / this->stacksNum);
			verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 2] - topCircleVertices[(i + 1) * 3 + 2]) / this->stacksNum);
		}
	}

	// Add between vertices
	if (this->topRadius <= 0.0f) {
		for (int i = 0; i < this->stacksNum - 1; ++i) {
			for (int j = 0; j < this->sectorsNum; ++j) {
				this->vertices.push_back(topCircleVertices[0] + (i + 1)*verticesStep[j][0]);
				this->vertices.push_back(topCircleVertices[1] + (i + 1)*verticesStep[j][1]);
				this->vertices.push_back(topCircleVertices[2] + (i + 1)*verticesStep[j][2]);
			}
		}
	}
	else if (this->baseRadius <= 0.0f) {
		for (int i = 0; i < this->stacksNum - 2; ++i) {
			for (int j = 0; j < this->sectorsNum; ++j) {
				this->vertices.push_back(topCircleVertices[(j + 1) * 3] + (i + 1)*verticesStep[j][0]);
				this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 1] + (i + 1)*verticesStep[j][1]);
				this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 2] + (i + 1)*verticesStep[j][2]);
			}
		}
	}
	else {
		for (int i = 0; i < this->stacksNum - 1; ++i) {
			for (int j = 0; j < this->sectorsNum; ++j) {
				this->vertices.push_back(topCircleVertices[(j + 1) * 3] + (i + 1)*verticesStep[j][0]);
				this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 1] + (i + 1)*verticesStep[j][1]);
				this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 2] + (i + 1)*verticesStep[j][2]);
			}
		}
	}

	this->vertices.push_back(baseCircleVertices[0]);
	this->vertices.push_back(baseCircleVertices[1]);
	this->vertices.push_back(baseCircleVertices[2]);
}

void Cylinder::generateIndices() {

	// Top
	if (this->topRadius > 0.0f) {
		for (int i = 0; i < this->sectorsNum - 1; ++i) {
			this->indices.push_back(0);
			this->indices.push_back((i + 2));
			this->indices.push_back((i + 1));
		}
		this->indices.push_back(0);
		this->indices.push_back(1);
		this->indices.push_back(this->sectorsNum);
	}

	// Side
	if (this->topRadius <= 0.0f) {
		for (int i = 0; i < this->sectorsNum - 1; ++i) {
			this->indices.push_back(0);
			this->indices.push_back((i + 2));
			this->indices.push_back((i + 1));
		}
		this->indices.push_back(0);
		this->indices.push_back(1);
		this->indices.push_back(this->sectorsNum);
		for (int i = 1; i < this->stacksNum - 1; ++i) {
			for (int j = 0; j < this->sectorsNum - 1; ++j) {
				this->indices.push_back(j + 1 + i * this->sectorsNum);
				this->indices.push_back(j + 2 + i * this->sectorsNum);
				this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
				this->indices.push_back(j + 2 + i * this->sectorsNum);
				this->indices.push_back(j + 2 + (i + 1) * this->sectorsNum);
				this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
			}
			this->indices.push_back((i + 1)*this->sectorsNum);
			this->indices.push_back(1 + i * this->sectorsNum);
			this->indices.push_back((i + 2)*this->sectorsNum);
			this->indices.push_back(1 + i * this->sectorsNum);
			this->indices.push_back(1 + (i + 1) * this->sectorsNum);
			this->indices.push_back((i + 2)*this->sectorsNum);
		}
	}
	else if (this->baseRadius <= 0.0f) {
		for (int i = 0; i < this->stacksNum - 2; ++i) {
			for (int j = 0; j < this->sectorsNum - 1; ++j) {
				this->indices.push_back(j + 1 + i * this->sectorsNum);
				this->indices.push_back(j + 2 + i * this->sectorsNum);
				this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
				this->indices.push_back(j + 2 + i * this->sectorsNum);
				this->indices.push_back(j + 2 + (i + 1) * this->sectorsNum);
				this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
			}
			this->indices.push_back((i + 1)*this->sectorsNum);
			this->indices.push_back(1 + i * this->sectorsNum);
			this->indices.push_back((i + 2)*this->sectorsNum);
			this->indices.push_back(1 + i * this->sectorsNum);
			this->indices.push_back(1 + (i + 1) * this->sectorsNum);
			this->indices.push_back((i + 2)*this->sectorsNum);
		}
		for (int i = 0; i < this->sectorsNum - 1; ++i) {
			this->indices.push_back(this->vertices.size() / 3 - 1);
			this->indices.push_back(this->vertices.size() / 3 - 3 - i);
			this->indices.push_back(this->vertices.size() / 3 - 2 - i);
		}
		this->indices.push_back(this->vertices.size() / 3 - 1);
		this->indices.push_back(this->vertices.size() / 3 - 2);
		this->indices.push_back(this->vertices.size() / 3 - 1 - this->sectorsNum);
	}
	else {
		for (int i = 0; i < this->stacksNum - 1; ++i) {
			for (int j = 0; j < this->sectorsNum - 1; ++j) {
				this->indices.push_back(j + 1 + i * this->sectorsNum);
				this->indices.push_back(j + 2 + i * this->sectorsNum);
				this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
				this->indices.push_back(j + 2 + i * this->sectorsNum);
				this->indices.push_back(j + 2 + (i + 1) * this->sectorsNum);
				this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
			}
			this->indices.push_back((i + 1)*this->sectorsNum);
			this->indices.push_back(1 + i * this->sectorsNum);
			this->indices.push_back((i + 2)*this->sectorsNum);
			this->indices.push_back(1 + i * this->sectorsNum);
			this->indices.push_back(1 + (i + 1) * this->sectorsNum);
			this->indices.push_back((i + 2)*this->sectorsNum);
		}
	}

	// Base
	if (this->baseRadius > 0.0f) {
		for (int i = 0; i < this->sectorsNum - 1; ++i) {
			this->indices.push_back(this->vertices.size() / 3 - 1);
			this->indices.push_back(this->vertices.size() / 3 - 3 - i);
			this->indices.push_back(this->vertices.size() / 3 - 2 - i);
		}
		this->indices.push_back(this->vertices.size() / 3 - 1);
		this->indices.push_back(this->vertices.size() / 3 - 2);
		this->indices.push_back(this->vertices.size() / 3 - 1 - this->sectorsNum);
	}
}