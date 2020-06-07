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

LightHandler::LightHandler(const cam::Camera &camera) {
    this->camera = camera;
    dirLight = std::make_unique<DirectionalLight>(DirectionalLight());
}

void LightHandler::movePointLight(glm::vec3 displacement, uint8_t target) {
    pointLights[target]->move(displacement);
}

void LightHandler::applyLightToShader(std::shared_ptr<Shader> shader) {
    shader->use();
    shader->setVector3f("eyePos", camera.getTransform().position);
    shader->setVector3f("dirLight.direction", dirLight->getDirection());
    shader->setVector3f("dirLight.ambient", dirLight->getAmbient() + 0.15f );
    shader->setVector3f("dirLight.diffuse", dirLight->getDiffuse());
    shader->setVector3f("dirLight.specular", dirLight->getSpecular());

    for(auto pointLight:pointLights) {
        shader->use();
        shader->setVector3f("pointLight.position", pointLight->getPosition());
        shader->setVector3f("pointLight.ambient", pointLight->getAmbient());
        shader->setVector3f("pointLight.diffuse", pointLight->getDiffuse());
        shader->setVector3f("pointLight.specular", pointLight->getSpecular());
        shader->setFloat("pointLight.constant", pointLight->getConstant());
        shader->setFloat("pointLight.linear", pointLight->getLinear());
        shader->setFloat("pointLight.quadratic", pointLight->getQuadratic());
        lightSourceShader->use();
        pointLight->drawLightSource();
    }

}

void LightHandler::setDirLight(glm::vec3 direction, glm::vec3 ambient,
        glm::vec3 diffuse,glm::vec3 specular) {
    dirLight->setDirection(direction);
    dirLight->setAmbient(ambient);
    dirLight->setDiffuse(diffuse);
    dirLight->setSpecular(specular);
}

const glm::vec3 &PointLight::getPosition() const {
    return position;
}

void PointLight::setPosition(const glm::vec3 &position) {
    PointLight::position = position;
}

const glm::vec3 &PointLight::getAmbient() const {
    return ambient;
}

void PointLight::setAmbient(const glm::vec3 &ambient) {
    PointLight::ambient = ambient;
}

const glm::vec3 &PointLight::getDiffuse() const {
    return diffuse;
}

void PointLight::setDiffuse(const glm::vec3 &diffuse) {
    PointLight::diffuse = diffuse;
}

const glm::vec3 &PointLight::getSpecular() const {
    return specular;
}

void PointLight::setSpecular(const glm::vec3 &specular) {
    PointLight::specular = specular;
}

GLfloat PointLight::getConstant() const {
    return constant;
}

void PointLight::setConstant(GLfloat constant) {
    PointLight::constant = constant;
}

GLfloat PointLight::getLinear() const {
    return linear;
}

void PointLight::setLinear(GLfloat linear) {
    PointLight::linear = linear;
}

GLfloat PointLight::getQuadratic() const {
    return quadratic;
}

void PointLight::setQuadratic(GLfloat quadratic) {
    PointLight::quadratic = quadratic;
}
