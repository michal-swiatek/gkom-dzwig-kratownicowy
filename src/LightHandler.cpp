//
// Created by seamel on 07.06.2020.
//

#include "LightHandler.h"
#include <stdexcept>

void LightHandler::movePointLight(glm::vec3 displacement, uint8_t target) {
    pointLights[target]->translateWorld(displacement);
}

void LightHandler::applyLightToShader(Shader &shader) {
    shader.use();
    shader.setVector3f("dirLight.direction", dirLight->direction);
    shader.setVector3f("dirLight.ambient", dirLight->ambient);
    shader.setVector3f("dirLight.diffuse", dirLight->diffuse);
    shader.setVector3f("dirLight.specular", dirLight->specular);

    for(int i=0; i<size(pointLights);i++) {
        shader.setVector3f("pointLights["+std::to_string(i)+"].position", pointLights[i]->getPosition());
        shader.setVector3f("pointLights["+std::to_string(i)+"].ambient", pointLights[i]->getPointLightInfo().ambient);
        shader.setVector3f("pointLights["+std::to_string(i)+"].diffuse", pointLights[i]->getPointLightInfo().diffuse);
        shader.setVector3f("pointLights["+std::to_string(i)+"].specular", pointLights[i]->getPointLightInfo().specular);
        shader.setFloat("pointLights["+std::to_string(i)+"].constant", pointLights[i]->getPointLightInfo().constant);
        shader.setFloat("pointLights["+std::to_string(i)+"].linear", pointLights[i]->getPointLightInfo().linear);
        shader.setFloat("pointLights["+std::to_string(i)+"].quadratic", pointLights[i]->getPointLightInfo().quadratic);
        shader.setVector3f("pointLights["+std::to_string(i)+"].color", pointLights[i]->getPointLightInfo().color);
    }

}

void LightHandler::addPointLight(std::shared_ptr<PointLight> pointLight) {
    pointLights.push_back(pointLight);
}

void LightHandler::setDirLight(DirectionalLight directionalLight) {
    dirLight->direction = directionalLight.direction;
    dirLight->ambient = directionalLight.ambient;
    dirLight->diffuse = directionalLight.diffuse;
    dirLight->specular = directionalLight.specular;
}

void LightHandler::setPointLightInfo(PointLightInfo info, uint8_t target) {
    pointLights[target]->setPointLightInfo(info);
}

void LightHandler::drawPointLights(cam::Camera &camera) {
    lightSourceShader->use();
    for(auto pointLight:pointLights) {
        lightSourceShader->setFloat("lightIntensity",pointLight->getLightIntensity());
        lightSourceShader->setVector3f("color",pointLight->getPointLightInfo().color);
        pointLight->drawLightSource(camera, lightSourceShader->getProgramID());
    }
}

LightHandler::LightHandler() {
    dirLight = std::make_unique<DirectionalLight>();
    lightSourceShader = std::make_unique<Shader>("../shaders/light_source.vs.glsl", "../shaders/light_source.fs.glsl");
}

void LightHandler::addPointLights(std::vector<std::shared_ptr<PointLight>> pointLights) {
    this->pointLights = pointLights;
}

const std::unique_ptr<DirectionalLight> &LightHandler::getDirLight() const {
    return dirLight;
}

void LightHandler::setDirection(glm::vec3 direction) {
    dirLight->direction = direction;
}

glm::vec3 LightHandler::getDirection() {
    return dirLight->direction;
}


void PointLight::translateWorld(const glm::vec3 &displacement) {
    lightSource->translateWorld(displacement);
}



PointLight::PointLight(const PointLightInfo &pointLightInfo, const std::shared_ptr<LightSource> &lightSource)
        : pointLightInfo(pointLightInfo), lightSource(lightSource) {}

const PointLightInfo &PointLight::getPointLightInfo() const {
    return pointLightInfo;
}

void PointLight::setPointLightInfo(const PointLightInfo &pointLightInfo) {
    PointLight::pointLightInfo = pointLightInfo;
}

void PointLight::drawLightSource(cam::Camera &camera, int shaderID) {

    lightSource->draw(camera,shaderID);
}

const std::shared_ptr<LightSource> &PointLight::getLightSource() const {
    return lightSource;
}

float PointLight::getLightIntensity() {
    auto lightIntensityVec = pointLightInfo.specular+pointLightInfo.specular+pointLightInfo.specular;
    float lightIntensity = lightIntensityVec[0] + lightIntensityVec[1] + lightIntensityVec[2];
    return lightIntensity/3;
}

glm::vec3 PointLight::getPosition() {
    return lightSource->getPosition();
}
