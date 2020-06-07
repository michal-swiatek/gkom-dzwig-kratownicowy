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

class DirectionalLight {
private:
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
public:
    DirectionalLight();

    [[nodiscard]] const glm::vec3 &getDirection() const;
    [[nodiscard]] const glm::vec3 &getAmbient() const;
    [[nodiscard]] const glm::vec3 &getDiffuse() const;
    [[nodiscard]] const glm::vec3 &getSpecular() const;

    void setDirection(const glm::vec3 &direction);
    void setAmbient(const glm::vec3 &ambient);
    void setDiffuse(const glm::vec3 &diffuse);
    void setSpecular(const glm::vec3 &specular);
};

class PointLight {
private:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
    std::shared_ptr<Object> lightSource;

public:
    PointLight(const glm::vec3& position,const glm::vec3& ambient,
               const glm::vec3& diffuse,const glm::vec3& specular,
               const GLfloat& constant,const GLfloat& linear,
               const GLfloat& quadratic, std::shared_ptr<Object> lightSource):
               position(position),ambient(ambient),diffuse(diffuse),specular(specular),
               constant(constant),linear(linear),quadratic(quadratic),lightSource(lightSource)
    {}

    void move(const glm::vec3& displacement);
    void drawLightSource();

    [[nodiscard]] const glm::vec3 &getPosition() const;
    [[nodiscard]] const glm::vec3 &getAmbient() const;
    [[nodiscard]] const glm::vec3 &getDiffuse() const;
    [[nodiscard]] const glm::vec3 &getSpecular() const;
    [[nodiscard]] GLfloat getConstant() const;
    [[nodiscard]] GLfloat getLinear() const;
    [[nodiscard]] GLfloat getQuadratic() const;

    void setPosition(const glm::vec3 &position);
    void setAmbient(const glm::vec3 &ambient);
    void setDiffuse(const glm::vec3 &diffuse);
    void setSpecular(const glm::vec3 &specular);
    void setConstant(GLfloat constant);
    void setLinear(GLfloat linear);
    void setQuadratic(GLfloat quadratic);
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
    void applyLightToShader(std::shared_ptr<Shader> shader);
    void setDirLight(glm::vec3 direction, glm::vec3 ambient,
                     glm::vec3 diffuse,glm::vec3 specular);
    void addPointLight(std::shared_ptr<PointLight> pointLight);
};

#endif //DZWIG_KRATOWNICOWY_LIGHTHANDLER_H
