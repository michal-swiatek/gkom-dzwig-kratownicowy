//
// Created by seamel on 30.05.2020.
//

#ifndef DZWIG_KRATOWNICOWY_CUBEMAP_H
#define DZWIG_KRATOWNICOWY_CUBEMAP_H

#endif //DZWIG_KRATOWNICOWY_CUBEMAP_H

#include <vector>
#include <memory>
#include <Camera.h>
#include <Shader.h>

class SkyBox {
private:
    GLuint VAO, VBO;
    glm::vec3 color;
    std::vector<float> vertices;
    GLuint texture;
    std::unique_ptr<Shader>  shader;
    std::vector<std::string> faces;
    GLuint loadCubeMapTexture();
    [[nodiscard]] GLuint generateCubeMapTexture() const;
    [[nodiscard]] GLuint generateColorTexture(const glm::vec3 &color) const;
    virtual void initShader() ;
public:
    void init();
    void draw(cam::Camera &camera);
    explicit SkyBox(glm::vec3 color);
    explicit SkyBox();

    ~SkyBox() = default;
};