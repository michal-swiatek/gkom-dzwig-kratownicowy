#include "../include/Cylinder.h"

/*
 *  Created by Rafal Uzarowicz
 *  github: https://github.com/RafalUzarowicz
 */


void Cylinder::initShader()
{
    shader = std::make_unique<Shader>("../shaders/phong_view.vs.glsl", "../shaders/phong_view.fs.glsl");

    shader->use();
    shader->setVector3f("lightColor", glm::vec3(1.0f));
    shader->setVector3f("ambientColor", glm::vec3(0.5f));
    shader->setVector3f("diffuseColor", glm::vec3(1.0f));
    shader->setVector3f("specularColor", glm::vec3(0.6f));
}

Cylinder::Cylinder(float bR, float tR, float h, int secNum, int staNum) {
    this->setParams(bR, tR, h, secNum, staNum);
    init();
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

void Cylinder::generateCylinder() {
    this->generateVertices();
    this->generateIndices();
}

float Cylinder::vectorLength(std::vector<float> vec) {
    float squaresSum = 0.0f;
    for (int i = 0; i < vec.size(); ++i) {
        squaresSum += vec[i] * vec[i];
    }
    return sqrt(squaresSum);
}

std::vector<float> Cylinder::generateBaseCircleVertices() {
    float angleStep = 2 * PI / this->sectorsNum;

    std::vector<float> circleVertices;
    // Coords
    circleVertices.push_back(0.0f);
    circleVertices.push_back(-this->height / 2.0f);
    circleVertices.push_back(0.0f);
    // N vec coords
    circleVertices.push_back(0.0f);
    circleVertices.push_back(-1.0f);
    circleVertices.push_back(0.0f);
    // UV
    circleVertices.push_back(0.75f);
    circleVertices.push_back(0.25f);
    if (this->baseRadius > 0.0f) {
        for (int i = 0; i < this->sectorsNum; ++i) {
            // Coords
            circleVertices.push_back(this->baseRadius*cos(i*angleStep));
            circleVertices.push_back(-this->height / 2.0f);
            circleVertices.push_back(this->baseRadius*sin(i*angleStep));
            // N vec coords
            //std::vector<float> nVec = { this->baseRadius*cos(i*angleStep), 0.0f, this->baseRadius*sin(i*angleStep) };
            std::vector<float> nVec = { 0.0f, -1.0f, 0.0f };
            float nVecLen = vectorLength(nVec);
            for (int i = 0; i < nVec.size(); ++i) {
                nVec[i] /= nVecLen;
            }

            circleVertices.push_back(nVec[0]);
            circleVertices.push_back(nVec[1]);
            circleVertices.push_back(nVec[2]);
            // UV
            circleVertices.push_back(cos(i*angleStep)/4.0f+0.75f);
            circleVertices.push_back(sin(i*angleStep)/4.0f+0.25f);
        }
        // Coords
        circleVertices.push_back(this->baseRadius);
        circleVertices.push_back(-this->height / 2.0f);
        circleVertices.push_back(0.0f);
        // N vec coords
        //std::vector<float> nVec = { this->baseRadius*cos(i*angleStep), 0.0f, this->baseRadius*sin(i*angleStep) };
        std::vector<float> nVec = { 0.0f, -1.0f, 0.0f };
        float nVecLen = vectorLength(nVec);
        for (int i = 0; i < nVec.size(); ++i) {
            nVec[i] /= nVecLen;
        }

        circleVertices.push_back(nVec[0]);
        circleVertices.push_back(nVec[1]);
        circleVertices.push_back(nVec[2]);
        // UV
        circleVertices.push_back(1.0f);
        circleVertices.push_back(0.25f);
    }
    return circleVertices;
}

std::vector<float> Cylinder::generateTopCircleVertices() {
    float angleStep = 2 * PI / this->sectorsNum;

    std::vector<float> circleVertices;
    // Coords
    circleVertices.push_back(0.0f);
    circleVertices.push_back(this->height / 2.0f);
    circleVertices.push_back(0.0f);
    // N vec coords
    circleVertices.push_back(0.0f);
    circleVertices.push_back(1.0f);
    circleVertices.push_back(0.0f);
    // UV
    circleVertices.push_back(0.75f);
    circleVertices.push_back(0.75f);
    if (this->topRadius > 0.0f) {
        for (int i = 0; i < this->sectorsNum; ++i) {
            // Coords
            circleVertices.push_back(this->topRadius*cos(i*angleStep));
            circleVertices.push_back(this->height / 2.0f);
            circleVertices.push_back(this->topRadius*sin(i*angleStep));
            // N vec coords
            //std::vector<float> nVec = { this->topRadius*cos(i*angleStep), 0.0f, this->topRadius*sin(i*angleStep) };
            std::vector<float> nVec = { 0.0f, 1.0f, 0.0f };
            float nVecLen = vectorLength(nVec);
            for (int i = 0; i < nVec.size(); ++i) {
                nVec[i] /= nVecLen;
            }
            circleVertices.push_back(nVec[0]);
            circleVertices.push_back(nVec[1]);
            circleVertices.push_back(nVec[2]);
            // UV
            circleVertices.push_back(cos(i*angleStep) / 4.0f + 0.75f);
            circleVertices.push_back(sin(i*angleStep) / 4.0f + 0.75f);
        }
        // Coords
        circleVertices.push_back(this->topRadius);
        circleVertices.push_back(this->height / 2.0f);
        circleVertices.push_back(0.0f);
        // N vec coords
        //std::vector<float> nVec = { this->topRadius*cos(i*angleStep), 0.0f, this->topRadius*sin(i*angleStep) };
        std::vector<float> nVec = { 0.0f, 1.0f, 0.0f };
        float nVecLen = vectorLength(nVec);
        for (int i = 0; i < nVec.size(); ++i) {
            nVec[i] /= nVecLen;
        }
        circleVertices.push_back(nVec[0]);
        circleVertices.push_back(nVec[1]);
        circleVertices.push_back(nVec[2]);
        // UV
        circleVertices.push_back(1.0f);
        circleVertices.push_back(0.75f);
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
        for (int i = 0; i <= this->sectorsNum; ++i) {
            verticesStep.push_back(std::vector<float>());
            verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum] - topCircleVertices[0]) / this->stacksNum);
            verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 1] - topCircleVertices[1]) / this->stacksNum);
            verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 2] - topCircleVertices[2]) / this->stacksNum);
        }
    }
    else if (this->baseRadius <= 0.0f) {
        for (int i = 0; i <= this->sectorsNum; ++i) {
            verticesStep.push_back(std::vector<float>());
            verticesStep[i].push_back((baseCircleVertices[0] - topCircleVertices[(i + 1) * paramNum]) / this->stacksNum);
            verticesStep[i].push_back((baseCircleVertices[1] - topCircleVertices[(i + 1) * paramNum + 1]) / this->stacksNum);
            verticesStep[i].push_back((baseCircleVertices[2] - topCircleVertices[(i + 1) * paramNum + 2]) / this->stacksNum);
        }
    }
    else {
        for (int i = 0; i <= this->sectorsNum; ++i) {
            verticesStep.push_back(std::vector<float>());
            verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum] - topCircleVertices[(i + 1) * paramNum]) / this->stacksNum);
            verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 1] - topCircleVertices[(i + 1) * paramNum + 1]) / this->stacksNum);
            verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 2] - topCircleVertices[(i + 1) * paramNum + 2]) / this->stacksNum);
        }
    }

    // Add between vertices
    if (this->topRadius <= 0.0f) {
        for (int i = 0; i <= this->stacksNum; ++i) {
            for (int j = 0; j <= this->sectorsNum; ++j) {
                // Coords
                this->vertices.push_back(topCircleVertices[0] + (i)*verticesStep[j][0]);
                this->vertices.push_back(topCircleVertices[1] + (i)*verticesStep[j][1]);
                this->vertices.push_back(topCircleVertices[2] + (i)*verticesStep[j][2]);
                // N vec coords
                std::vector<float> nVec = { topCircleVertices[0] + (i)*verticesStep[j][0], 0.0f, topCircleVertices[2] + (i)*verticesStep[j][2] };
                float nVecLen = vectorLength(nVec);
                for (int i = 0; i < nVec.size(); ++i) {
                    nVec[i] /= nVecLen;
                }
                this->vertices.push_back(nVec[0]);
                this->vertices.push_back(nVec[1]);
                this->vertices.push_back(nVec[2]);
                // UV
                this->vertices.push_back((float)j / this->sectorsNum / 2.0f);
                this->vertices.push_back((float)i / this->stacksNum);
            }
        }
    }
    else if (this->baseRadius <= 0.0f) {
        for (int i = 0; i <= this->stacksNum; ++i) {
            for (int j = 0; j <= this->sectorsNum; ++j) {
                // Coords
                this->vertices.push_back(topCircleVertices[(j + 1) * paramNum] + (i)*verticesStep[j][0]);
                this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 1] + (i)*verticesStep[j][1]);
                this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 2] + (i)*verticesStep[j][2]);
                // N vec coords
                std::vector<float> nVec = { topCircleVertices[(j + 1) * paramNum] + (i)*verticesStep[j][0], 0.0f, topCircleVertices[(j + 1) * paramNum + 2] + (i)*verticesStep[j][2] };
                float nVecLen = vectorLength(nVec);
                for (int i = 0; i < nVec.size(); ++i) {
                    nVec[i] /= nVecLen;
                }
                this->vertices.push_back(nVec[0]);
                this->vertices.push_back(nVec[1]);
                this->vertices.push_back(nVec[2]);
                // UV
                this->vertices.push_back((float)j / this->sectorsNum / 2.0f);
                this->vertices.push_back((float)i / this->stacksNum);
            }
        }
    }
    else {
        for (int i = 0; i <= this->stacksNum; ++i) {
            for (int j = 0; j <= this->sectorsNum; ++j) {
                // Coords
                this->vertices.push_back(topCircleVertices[(j + 1) * paramNum] + (i)*verticesStep[j][0]);
                this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 1] + (i)*verticesStep[j][1]);
                this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 2] + (i)*verticesStep[j][2]);
                // N vec coords
                std::vector<float> nVec = { topCircleVertices[(j + 1) * paramNum] + (i)*verticesStep[j][0], 0.0f, topCircleVertices[(j + 1) * paramNum + 2] + (i)*verticesStep[j][2] };
                float nVecLen = vectorLength(nVec);
                for (int i = 0; i < nVec.size(); ++i) {
                    nVec[i] /= nVecLen;
                }
                this->vertices.push_back(nVec[0]);
                this->vertices.push_back(nVec[1]);
                this->vertices.push_back(nVec[2]);
                // UV
                this->vertices.push_back((float)j/this->sectorsNum/2.0f);
                this->vertices.push_back((float)i/this->stacksNum);
            }
        }
    }

    // Add base vertices
    for (unsigned int i = 0; i < baseCircleVertices.size(); ++i) {
        this->vertices.push_back(baseCircleVertices[i]);
    }
}

void Cylinder::generateIndices() {

    // Top
    if (this->topRadius > 0.0f) {
        for (int i = 0; i < this->sectorsNum; ++i) {
            this->indices.push_back(0);
            this->indices.push_back((i + 2));
            this->indices.push_back((i + 1));
        }
    }

    // Side
    if (this->topRadius <= 0.0f) {
        for (int i = 0; i < this->sectorsNum; ++i) {
            this->indices.push_back(i+2);
            this->indices.push_back((i + this->sectorsNum + 3));
            this->indices.push_back((i + this->sectorsNum + 2));
        }

        for (int i = 0; i < this->stacksNum-1; ++i) {
            for (int j = 0; j < this->sectorsNum; ++j) {
                this->indices.push_back(j + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
                this->indices.push_back(j + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
            }
        }
    }
    else if (this->baseRadius <= 0.0f) {
        for (int i = 0; i < this->stacksNum-1; ++i) {
            for (int j = 0; j < this->sectorsNum; ++j) {
                this->indices.push_back(j + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
                this->indices.push_back(j + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
            }
        }
        for (int i = 0; i < this->sectorsNum; ++i) {
            this->indices.push_back(this->vertices.size() / paramNum - 3 - i);
            this->indices.push_back(this->vertices.size() / paramNum - this->sectorsNum - 4 - i);
            this->indices.push_back(this->vertices.size() / paramNum - this->sectorsNum - 3 - i);
        }
    }
    else {
        for (int i = 0; i < this->stacksNum; ++i) {
            for (int j = 0; j < this->sectorsNum; ++j) {
                this->indices.push_back(j + this->sectorsNum + 2 + i*(this->sectorsNum+1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + this->sectorsNum + 2 + (i+1) * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + i * (this->sectorsNum + 1));
                this->indices.push_back(j + 1 + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
                this->indices.push_back(j + this->sectorsNum + 2 + (i + 1) * (this->sectorsNum + 1));
            }
        }
    }

    // Base
    if (this->baseRadius > 0.0f) {
        for (int i = 0; i < this->sectorsNum; ++i) {
            this->indices.push_back(this->vertices.size() / paramNum - 2 - this->sectorsNum);
            this->indices.push_back(this->vertices.size() / paramNum - 2 - i);
            this->indices.push_back(this->vertices.size() / paramNum - 1 - i);
        }
    }
}