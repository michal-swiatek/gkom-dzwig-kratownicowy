

#ifndef OBJECT_H
#define OBJECT_H




#include "Model.h"

class Object : public Model
{/*
created by BM Wzorowane na Box.cpp z learnopengl by Micha� �wi�tek
*/

protected:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    std::unique_ptr<Shader>  shader;
    GLuint VBO, VAO, EBO;

    Transform transform;

    glm::mat4 rotationMatrix;
    glm::mat4 translationMatrix;
    glm::mat4 scaleMatrix;


    glm::mat4 projectionMatrix;
    glm::vec4 color;

    const unsigned int paramNum = 8;

    using OptionalMat4 = std::optional<glm::mat4>;

public:
    explicit Object(const Transform& transform, const glm::vec4& color = glm::vec4(1.0f));
    explicit Object(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& color = glm::vec4(1.0f));

    std::vector<float> getVertices();
    std::vector<unsigned int> getIndices();

    void updateMatrices(const OptionalMat4& projection = {});

    void translate(const glm::vec3& offset) override;
    void rotate(float angle, const std::optional<glm::vec3>& axis) override;
    void scale(const glm::vec3& value) override;

    void rotate2( const std::optional<glm::vec3>& axis);

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
