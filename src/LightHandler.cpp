//
// Created by seamel on 07.06.2020.
//

#include "LightHandler.h"

const glm::vec3 &DirectionalLight::getDirection() const {
    return direction;
}

void DirectionalLight::setDirection(const glm::vec3 &direction) {
    DirectionalLight::direction = direction;
}

const glm::vec3 &DirectionalLight::getAmbient() const {
    return ambient;
}

void DirectionalLight::setAmbient(const glm::vec3 &ambient) {
    DirectionalLight::ambient = ambient;
}

const glm::vec3 &DirectionalLight::getDiffuse() const {
    return diffuse;
}

void DirectionalLight::setDiffuse(const glm::vec3 &diffuse) {
    DirectionalLight::diffuse = diffuse;
}

const glm::vec3 &DirectionalLight::getSpecular() const {
    return specular;
}

void DirectionalLight::setSpecular(const glm::vec3 &specular) {
    DirectionalLight::specular = specular;
}
