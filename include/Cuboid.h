#ifndef CUBOID_H
#define CUBOID_H

#include <iostream>
#include <cmath>

#include "Object.h"

class Cuboid : public Object {
private:

	void generateIndicies();

public:

	void initShader() override;

	Cuboid(float width = 1.0f, float length = 1.0f, float height = 1.0f);
	
	void generateCuboid(float width = 1.0f, float length = 1.0f, float height = 1.0f);

	Cuboid(const Cuboid& other) = default;

	Cuboid& operator=(const Cuboid& rhs) = default;

	Cuboid(Cuboid&& other) = default;

};

#endif // !CUBOID_H