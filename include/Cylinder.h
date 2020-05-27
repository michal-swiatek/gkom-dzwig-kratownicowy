/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 *  modified 27.05.20 BM
 */

#ifndef CYLINDER_H_UZAROWICZ
#define CYLINDER_H_UZAROWICZ

#include <vector>
#include <iostream>
#include <cmath>

#include "Object.h"

class Cylinder : public Object
{
private:
	float baseRadius;
	float topRadius;
	float height;
	int sectorsNum;
	int stacksNum;

	const float PI = (float)acos(-1);
	const unsigned int paramNum = 8;

public:
	void initShader() override;

	Cylinder(float bR = 1.0f, float tR = 1.0f, float h = 2.0f, int secNum = 4, int staNum = 3);

	Cylinder(const Cylinder& other) = default;

	Cylinder& operator=(const Cylinder& rhs) = default;

	Cylinder(Cylinder&& other) = default;

	void setParams(float bR, float tR, float h, int secNum, int staNum);

	void clearVectors();

	void generateCylinder();

	float vectorLength(std::vector<float> vec);

	std::vector<float> generateBaseCircleVertices();

	std::vector<float> generateTopCircleVertices();

	void generateVertices();

	void generateIndices();

};

#endif //CYLINDER_H_UZAROWICZ