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
    return nullptr;
}

glm::mat4 calcLightSpaceMatrix(glm::vec3 direction)
{
    direction -= 0.5;
    direction *= 2;
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 500;
    lightProjection = glm::ortho(-250.0f, 250.0f, -250.0f, 250.0f, near_plane, far_plane);
    lightView = glm::lookAt({ 1.01*far_plane*direction[0]/2 + 2.0 , 1.02*far_plane*direction[1]/2 - 0.1, 1.03*far_plane*direction[2]/2 + 0.5 }, glm::vec3(far_plane*direction[0]/2 , far_plane*direction[1]/2, far_plane*direction[2]/2), glm::vec3(0.0, 1.0, 0.0));
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
