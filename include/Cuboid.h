/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#ifndef CUBOID_H
#define CUBOID_H

#include <iostream>
#include <cmath>

#include "Model.h"

class Cuboid : public Model {
private:

    void generateIndicies();

public:

    Cuboid(float width = 1.0f, float length = 1.0f, float height = 1.0f);

    Cuboid(const Cuboid& other) = default;

    Cuboid& operator=(const Cuboid& rhs) = default;

    Cuboid(Cuboid&& other) = default;

};

#endif // !CUBOID_H