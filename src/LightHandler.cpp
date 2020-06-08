//
// Created by seamel on 07.06.2020.
//

#include "LightHandler.h"
#include <stdexcept>

void LightHandler::movePointLight(glm::vec3 displacement, uint8_t target) {
    pointLights[target]->move(displacement);
}

void LightHandler::applyLightToShader(Shader &shader) {
    shader.use();
    shader.setVector3f("dirLight.direction", dirLight->direction);
    shader.setVector3f("dirLight.ambient", dirLight->ambient + 0.15f );
    shader.setVector3f("dirLight.diffuse", dirLight->diffuse);
    shader.setVector3f("dirLight.specular", dirLight->specular);

    for(auto pointLight:pointLights) {
        shader.setVector3f("pointLight.position", pointLight->getPointLightInfo().position);
        shader.setVector3f("pointLight.ambient", pointLight->getPointLightInfo().ambient);
        shader.setVector3f("pointLight.diffuse", pointLight->getPointLightInfo().diffuse);
        shader.setVector3f("pointLight.specular", pointLight->getPointLightInfo().specular);
        shader.setFloat("pointLight.constant", pointLight->getPointLightInfo().constant);
        shader.setFloat("pointLight.linear", pointLight->getPointLightInfo().linear);
        shader.setFloat("pointLight.quadratic", pointLight->getPointLightInfo().quadratic);
    }

}

void LightHandler::addPointLight(std::shared_ptr<PointLight> pointLight) {
    if(pointLights.size() >= MAX_POINT_LIGHTS)
        throw std::runtime_error("Próba przekroczenia maksymalnej liczby świateł punktowych");
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
    for(auto pointLight:pointLights) {
        pointLight->drawLightSource(camera, lightSourceShader->getProgramID());
    }
}

LightHandler::LightHandler() {
    dirLight = std::make_unique<DirectionalLight>(DirectionalLight());
    lightSourceShader = std::make_unique<Shader>("shaders/light_source.vs.glsl", "shaders/light_source.fs.glsl");
}



void PointLight::move(const glm::vec3 &displacement) {
    lightSource->translateWorld(displacement);
}



PointLight::PointLight(const PointLightInfo &pointLightInfo, const std::shared_ptr<Object> &lightSource)
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
