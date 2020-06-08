//
// Created by seamel on 08.06.2020.
//

#ifndef DZWIG_KRATOWNICOWY_SHADOWS_H
#define DZWIG_KRATOWNICOWY_SHADOWS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"

const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
unsigned int depthMapFBO;
unsigned int depthMap;

std::shared_ptr<Shader> prepareShadows()
{
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return nullptr;//ShaderProvider::instance().getShader("shShadowMap.vert", "shShadowMap.frag");
}

glm::mat4 calcLightSpaceMatrix()
{
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 400;
    lightProjection = glm::ortho(-150.0f, 150.0f, -150.0f, 150.0f, near_plane, far_plane);
    lightView = glm::lookAt({ -251.0f, 0.62f, -0.175f }, glm::vec3(-250.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;
    return lightSpaceMatrix;
}

void applyLightViewToShaders(std::vector<Shader*> shaders, const glm::mat4& lightSpaceMatrix)
{
    for (const auto& shader : shaders)
    {
        shader->use();
        shader->setMatrix4f("lightSpaceMatrix", lightSpaceMatrix);
    }
}

#endif //DZWIG_KRATOWNICOWY_SHADOWS_H
