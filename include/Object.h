

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Camera.h"
#include "Shader.h"
#include "window.h"

class Object
{

public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

	Object() = default;

	const unsigned int paramNum = 8;

    std::unique_ptr<Shader>  shader;

    GLuint VBO, VAO, EBO;

	std::vector<float> getVertices();

	std::vector<unsigned int> getIndices();

	void clearVectors();

    void init();


   
    void draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings) const;

    virtual void initShader() = 0;




};

#endif //OBJECT_H
