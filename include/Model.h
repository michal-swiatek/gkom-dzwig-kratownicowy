/*
Stworzone przez BM
*/

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Camera.h"
#include "Shader.h"
#include "window.h"



class Model
{
public:
    virtual void draw(std::unique_ptr<cam::Camera>& camera, WindowSettings windowSettings, bool use_color) const = 0;
    virtual void translate(const glm::vec3& offset) = 0;
    virtual void rotate(float angle, const std::optional<glm::vec3>& axis) = 0;
    virtual void scale(const glm::vec3& value) = 0;
    virtual void rotate2(const std::optional<glm::vec3>& axis) = 0;//to jest tu chwilowo
};

#endif // MODEL_H