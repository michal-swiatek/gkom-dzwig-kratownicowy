/*
    Created by michal-swiatek on 20.05.2020.
    Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy
*/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    explicit Transform(const glm::vec3& position = glm::vec3(0.0f),
                       const glm::vec3& rotation = glm::vec3(0.0f),
                       const glm::vec3& scale = glm::vec3(1.0f)) :
                            position(position), rotation(rotation), scale(scale) { }
};

#endif //TRANSFORM_H
