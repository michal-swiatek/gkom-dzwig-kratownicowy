//
// Created by seamel on 07.06.2020.
//

#ifndef DZWIG_KRATOWNICOWY_LIGHTHANDLER_H
#define DZWIG_KRATOWNICOWY_LIGHTHANDLER_H

#include <vector>
#include <memory>
#include "Shader.h"
#include "Camera.h"
#include "Object.h"
#include "LightSource.h"

struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLightInfo {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
    glm::vec3 color;
};

class PointLight {
private:
    PointLightInfo pointLightInfo;
    std::shared_ptr<LightSource> lightSource;

public:
    PointLight(const PointLightInfo &pointLightInfo, const std::shared_ptr<LightSource> &lightSource);

    void translateLocal(const glm::vec3& displacement);
    void translateWorld(const glm::vec3& displacement);

    void drawLightSource(cam::Camera &camera, int shaderID);

    [[nodiscard]] const PointLightInfo &getPointLightInfo() const;

    [[nodiscard]] const std::shared_ptr<LightSource> &getLightSource() const;
    float getLightIntensity();
    glm::vec3 getPosition();
    void setPointLightInfo(const PointLightInfo &pointLightInfo);
};

class LightHandler {
private:
    std::unique_ptr<Shader> lightSourceShader;
    std::unique_ptr<DirectionalLight> dirLight;
    std::vector<std::shared_ptr<PointLight>> pointLights;

public:
    explicit LightHandler();
    void movePointLight(glm::vec3 displacement, uint8_t target);
    void setPointLightInfo(PointLightInfo info, uint8_t target);
    void applyLightToShader(Shader &shader);
    void drawPointLights(cam::Camera &camera);
    void setDirLight(DirectionalLight directionalLight);
    void addPointLight(std::shared_ptr<PointLight> pointLight);
    void addPointLights(std::vector<std::shared_ptr<PointLight>> pointLights);
    void setDirection(glm::vec3 direction);
    glm::vec3 getDirection();
    DirectionalLight& getDirLight();
};

#endif //DZWIG_KRATOWNICOWY_LIGHTHANDLER_H
