//
// Created by seamel on 08.06.2020.
//

#ifndef DZWIG_KRATOWNICOWY_LIGHTSOURCE_H
#define DZWIG_KRATOWNICOWY_LIGHTSOURCE_H

#include <memory>
#include <vector>
#include <cmath>
#include "Object.h"


class LightSource : public Object {

public:
    LightSource(const std::shared_ptr<Model> &mod);

    void draw(cam::Camera &camera, int shaderID) const override;
    glm::vec3 getPosition();
};

#endif //DZWIG_KRATOWNICOWY_LIGHTSOURCE_H
