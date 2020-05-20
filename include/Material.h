/*
 *  Created by michal-swiatek on 20.05.2020, based on Joey de Vries tutorials.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 *  LearnOpenGL tutorial: https://learnopengl.com/Introduction
 */

#ifndef DZWIG_KRATOWNICOWY_MATERIAL_H
#define DZWIG_KRATOWNICOWY_MATERIAL_H

#include <cstdint>

struct Material
{
    //  There are always textures, if color is specified then a 1x1 texture is created
    uint32_t ambient = 0;
    uint32_t diffuse = 0;
    uint32_t specular = 0;

    float shininess = 32;
};

#endif //DZWIG_KRATOWNICOWY_MATERIAL_H
