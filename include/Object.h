

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
{/*
created by BM Wzorowane na Box.cpp z learnopengl by Micha³ Œwi¹tek
*/

public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

	Object() = default;

	const unsigned int paramNum = 8;

    std::unique_ptr<Shader>  shader;

    GLuint VBO, VAO, EBO;

	std::vector<float> getVertices();

	std::vector<unsigned int> getIndices();



    Transform transform;
    glm::mat4 modelMatrix;

    glm::mat4 projectionMatrix;

    glm::vec4 color;
    using OptionalMat4 = std::optional<glm::mat4>;

    explicit Object(const Transform& transform, const glm::vec4& color = glm::vec4(1.0f));
    explicit Object(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& color = glm::vec4(1.0f));

    void updateMatrices(const OptionalMat4& projection = {});

    void translate(const glm::vec3& offset);
    void rotate(float angle, const std::optional<glm::vec3>& axis);
    void scale(const glm::vec3& value);

    void setPosition(const glm::vec3& position);
    void setRotation(float angle, const glm::vec3& axis);
    void setScale(const glm::vec3& scale);

    //  Transform
    [[nodiscard]] const Transform& getTransform() const;
    void setTransform(const Transform& newTransform);

    [[nodiscard]] const glm::mat4& getModelMatrix() const;
    void setModelMatrix(const glm::mat4& newModelMatrix);

    //  Color
    [[nodiscard]] const glm::vec4& getColor() const;
    void setColor(const glm::vec4& newColor);

	void clearVectors();

    void init();
    using OptionalMat4 = std::optional<glm::mat4>;

   
    void draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const;

    virtual void initShader() = 0;




};

#endif //OBJECT_H
