/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */

#include "../include/Cuboid.h"

Cuboid::Cuboid(float width, float length, float height) {
    this->generateCuboid(width, length, height);
    this->init();
}

void Cuboid::generateCuboid(float width, float length, float height) {
    if (width <= 0.0f) {
        std::cout << "Zla szerokosc." << '\n';
    }
    else if (length <= 0.0f) {
        std::cout << "Zla dlugosc." << '\n';
    }
    else if (height <= 0.0f) {
        std::cout << "Zla wysokosc." << '\n';
    }
    else if (width == 1.0f && length == 1.0f && height == 1.0f) {
        this->clearVectors();
        this->vertices = std::move(std::vector<float>({
                                                              // 1
                                                              0.5f,  0.5f,  -0.5f,		 0.0f,  0.0f,  1.0f,	0.5f,  0.0f,
                                                              -0.5f,  0.5f,  -0.5f,		 0.0f,  0.0f,  1.0f,	0.25f,  0.0f,
                                                              -0.5f, -0.5f,  -0.5f,		 0.0f,  0.0f,  1.0f,	0.25f,  0.25f,
                                                              0.5f, -0.5f,  -0.5f,		 0.0f,  0.0f,  1.0f,	0.5f,  0.25f,
                                                              // 2
                                                              -0.5f, -0.5f,   0.5f,		 0.0f,  0.0f, -1.0f,	0.25f,  0.5f,
                                                              -0.5f,  0.5f,   0.5f,		 0.0f,  0.0f, -1.0f,	0.25f,  0.75f,
                                                              0.5f,  0.5f,   0.5f,		 0.0f,  0.0f, -1.0f,	0.5f,  0.75f,
                                                              0.5f, -0.5f,   0.5f,		 0.0f,  0.0f, -1.0f,	0.5f,  0.5f,
                                                              // 3
                                                              -0.5f, -0.5f,  -0.5f,		 0.0f,  1.0f,  0.0f,	0.25f,  0.25f,
                                                              -0.5f, -0.5f,   0.5f,		 0.0f,  1.0f,  0.0f,	0.25f,  0.5f,
                                                              0.5f, -0.5f,   0.5f,		 0.0f,  1.0f,  0.0f,	0.5f,  0.5f,
                                                              0.5f, -0.5f,  -0.5f,		 0.0f,  1.0f,  0.0f,	0.5f,  0.25f,
                                                              // 4
                                                              -0.5f,  0.5f,   0.5f,		 0.0f, -1.0f,  0.0f,	0.25f,  0.75f,
                                                              -0.5f,  0.5f,  -0.5f,		 0.0f, -1.0f,  0.0f,	0.25f,  1.0f,
                                                              0.5f,  0.5f,  -0.5f,		 0.0f, -1.0f,  0.0f,	0.5f,  1.0f,
                                                              0.5f,  0.5f,   0.5f,		 0.0f, -1.0f,  0.0f,	0.5f,  0.75f,
                                                              // 5
                                                              -0.5f, -0.5f,  -0.5f,		 1.0f,  0.0f,  0.0f,	0.0f,  0.5f,
                                                              -0.5f,  0.5f,  -0.5f,		 1.0f,  0.0f,  0.0f,	0.0f,  0.75f,
                                                              -0.5f,  0.5f,   0.5f,		 1.0f,  0.0f,  0.0f,	0.25f,  0.75f,
                                                              -0.5f, -0.5f,   0.5f,		 1.0f,  0.0f,  0.0f,	0.25f,  0.5f,
                                                              // 6
                                                              0.5f, -0.5f,  -0.5f,		-1.0f,  0.0f,  0.0f,	0.75f,  0.5f,
                                                              0.5f, -0.5f,   0.5f,		-1.0f,  0.0f,  0.0f,	0.5f,  0.5f,
                                                              0.5f,  0.5f,   0.5f,		-1.0f,  0.0f,  0.0f,	0.5f,  0.75f,
                                                              0.5f,  0.5f,  -0.5f,		-1.0f,  0.0f,  0.0f,	0.75f,  0.75f
                                                      }));
        this->generateIndicies();
    }
    else {
        this->clearVectors();
        float halfLength = length / 2.0f;
        float halfHeight = height / 2.0f;
        float halfWidth = width / 2.0f;
        this->vertices = std::move(std::vector<float>({
                                                              // 1
                                                              halfLength,  halfHeight,  -halfWidth,		 0.0f,  0.0f,  1.0f,	0.5f,  0.0f,
                                                              -halfLength,  halfHeight,  -halfWidth,		 0.0f,  0.0f,  1.0f,	0.25f,  0.0f,
                                                              -halfLength, -halfHeight,  -halfWidth,		 0.0f,  0.0f,  1.0f,	0.25f,  0.25f,
                                                              halfLength, -halfHeight,  -halfWidth,		 0.0f,  0.0f,  1.0f,	0.5f,  0.25f,
                                                              // 2
                                                              -halfLength, -halfHeight,   halfWidth,		 0.0f,  0.0f, -1.0f,	0.25f,  0.5f,
                                                              -halfLength,  halfHeight,	halfWidth,		 0.0f,  0.0f, -1.0f,	0.25f,  0.75f,
                                                              halfLength,  halfHeight,   halfWidth,		 0.0f,  0.0f, -1.0f,	0.5f,  0.75f,
                                                              halfLength, -halfHeight,   halfWidth,		 0.0f,  0.0f, -1.0f,	0.5f,  0.5f,
                                                              // 3
                                                              -halfLength, -halfHeight,  -halfWidth,		 0.0f,  1.0f,  0.0f,	0.25f,  0.25f,
                                                              -halfLength, -halfHeight,   halfWidth,		 0.0f,  1.0f,  0.0f,	0.25f,  0.5f,
                                                              halfLength, -halfHeight,   halfWidth,		 0.0f,  1.0f,  0.0f,	0.5f,  0.5f,
                                                              halfLength, -halfHeight,  -halfWidth,		 0.0f,  1.0f,  0.0f,	0.5f,  0.25f,
                                                              // 4
                                                              -halfLength,  halfHeight,   halfWidth,		 0.0f, -1.0f,  0.0f,	0.25f,  0.75f,
                                                              -halfLength,  halfHeight,  -halfWidth,		 0.0f, -1.0f,  0.0f,	0.25f,  1.0f,
                                                              halfLength,  halfHeight,  -halfWidth,		 0.0f, -1.0f,  0.0f,	0.5f,  1.0f,
                                                              halfLength,  halfHeight,   halfWidth,		 0.0f, -1.0f,  0.0f,	0.5f,  0.75f,
                                                              // 5
                                                              -halfLength, -halfHeight,  -halfWidth,		 1.0f,  0.0f,  0.0f,	0.0f,  0.5f,
                                                              -halfLength,  halfHeight,  -halfWidth,		 1.0f,  0.0f,  0.0f,	0.0f,  0.75f,
                                                              -halfLength,  halfHeight,   halfWidth,		 1.0f,  0.0f,  0.0f,	0.25f,  0.75f,
                                                              -halfLength, -halfHeight,   halfWidth,		 1.0f,  0.0f,  0.0f,	0.25f,  0.5f,
                                                              // 6
                                                              halfLength, -halfHeight,  -halfWidth,		-1.0f,  0.0f,  0.0f,	0.75f,  0.5f,
                                                              halfLength, -halfHeight,   halfWidth,		-1.0f,  0.0f,  0.0f,	0.5f,  0.5f,
                                                              halfLength,  halfHeight,   halfWidth,		-1.0f,  0.0f,  0.0f,	0.5f,  0.75f,
                                                              halfLength,  halfHeight,  -halfWidth,		-1.0f,  0.0f,  0.0f,	0.75f,  0.75f
                                                      }));
        this->generateIndicies();
    }
}

void Cuboid::generateIndicies() {
    this->indices = std::move(std::vector<unsigned int>({
                                                                0,1,2,
                                                                0,2,3,
                                                                4,5,6,
                                                                4,6,7,
                                                                8,9,10,
                                                                8,10,11,
                                                                12,13,14,
                                                                12,14,15,
                                                                16,17,18,
                                                                16,18,19,
                                                                20,21,22,
                                                                20,22,23
                                                        }));
}

void Cuboid::initShader()
{
    shader = std::make_unique<Shader>("../shaders/phong_view.vs.glsl", "../shaders/phong_view.fs.glsl");

    shader->use();
    shader->setVector3f("lightColor", glm::vec3(1.0f));
    shader->setVector3f("ambientColor", glm::vec3(0.5f));
    shader->setVector3f("diffuseColor", glm::vec3(1.0f));
    shader->setVector3f("specularColor", glm::vec3(0.6f));
}