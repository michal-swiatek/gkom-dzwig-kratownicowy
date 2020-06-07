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
    const glm::vec3 &getDirection() const;

    void setDirection(const glm::vec3 &direction);

    const glm::vec3 &getAmbient() const;

    void setAmbient(const glm::vec3 &ambient);

    const glm::vec3 &getDiffuse() const;

    void setDiffuse(const glm::vec3 &diffuse);

    const glm::vec3 &getSpecular() const;

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
    std::unique_ptr<LightSource> lightSource;

public:
    PointLight(const glm::vec3& position,const glm::vec3& ambient,
               const glm::vec3& diffuse,const glm::vec3& specular,
               const GLfloat& constant,const GLfloat& linear,
               const GLfloat& quadratic): position(position),
                                          ambient(ambient),diffuse(diffuse),specular(specular),
                                          constant(constant),linear(linear),quadratic(quadratic),
                                          lightsrc(std::make_unique<LightSource>(position, 0.5f))
    {}

    void move(const glm::vec3& displacement);
    void drawLightSrc(std::shared_ptr<Shader> shader);
};

class LightManager {
private:
    const static int MAX_POINT_LIGHTS = 10;
    std::shared_ptr<Shader> lightSrcShader;
    std::unique_ptr<DirectionalLight> dirLight;
    std::vector<std::shared_ptr<PointLight>> pointLight;

    cam::Camera camera;

public:
    LightManager(const cam::Camera& camera)
    {
        this->camera = camera;
        dirLight = std::make_unique<DirectionalLight>(DirectionalLight());
    }
    void movePointLight(glm::vec3 displacement);
    void applyLightToShader(std::shared_ptr<Shader> shader);
};

#endif //DZWIG_KRATOWNICOWY_LIGHTHANDLER_H
