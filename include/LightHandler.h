//
// Created by seamel on 07.06.2020.
//

#ifndef DZWIG_KRATOWNICOWY_LIGHTHANDLER_H
#define DZWIG_KRATOWNICOWY_LIGHTHANDLER_H

#include <vector>
#include <memory>
#include "Shader.h"
#include "Camera.h"
#include "Cylinder.h"

struct DirectionalLight {
    glm::vec3 direction = glm::vec3(0.5);
    glm::vec3 ambient = glm::vec3(0.5);
    glm::vec3 diffuse = glm::vec3(0.5);
    glm::vec3 specular = glm::vec3(0.5);
};

struct PointLightInfo {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
};

class PointLight {
private:
    PointLightInfo pointLightInfo;
    std::shared_ptr<Object> lightSource;

public:
    PointLight(const PointLightInfo &pointLightInfo, const std::shared_ptr<Object> &lightSource);

    void move(const glm::vec3& displacement);
    void drawLightSource();

    [[nodiscard]] const PointLightInfo &getPointLightInfo() const;

    void setPointLightInfo(const PointLightInfo &pointLightInfo);
};

class LightHandler {
private:
    const static int MAX_POINT_LIGHTS = 10;
    std::unique_ptr<Shader> lightSourceShader;
    std::unique_ptr<DirectionalLight> dirLight;
    std::vector<std::shared_ptr<PointLight>> pointLights;

    cam::Camera camera;

public:
    explicit LightHandler(const cam::Camera& camera);
    void movePointLight(glm::vec3 displacement, uint8_t target);
    void setPointLightInfo(PointLightInfo info, uint8_t target);
    void applyLightToShader(std::shared_ptr<Shader> shader);
    void setDirLight(DirectionalLight directionalLight);
    void addPointLight(std::shared_ptr<PointLight> pointLight);
};

#endif //DZWIG_KRATOWNICOWY_LIGHTHANDLER_H
