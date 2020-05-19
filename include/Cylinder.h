/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef CYLINDER_H_UZAROWICZ
#define CYLINDER_H_UZAROWICZ

#include <cmath>
#include <vector>
#include <iostream>

class Cylinder
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	float baseRadius;
	float topRadius;
	float height;
	int sectorsNum;
	int stacksNum;

	const float PI = (float)acos(-1);
	unsigned int paramNum = 3;

public:

	Cylinder(float bR = 1.0f, float tR = 1.0f, float h = 2.0f, int secNum = 4, int staNum = 3);

	void setParams(float bR, float tR, float h, int secNum, int staNum);

	std::vector<float> getVertices();

	std::vector<unsigned int> getIndices();

	void clearVectors();

	void generateCylinder();

	std::vector<float> generateBaseCircleVertices();

	std::vector<float> generateTopCircleVertices();

	void generateVertices();

	void generateIndices();
	
};

#endif //CYLINDER_H_UZAROWICZ