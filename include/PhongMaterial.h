/*
 *  Created by michal-swiatek on 20.05.2020, based on Joey de Vries tutorials.
 *  Gitlab: http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy/
 *  LearnOpenGL tutorial: https://learnopengl.com/Introduction
 */

#ifndef DZWIG_KRATOWNICOWY_PHONG_MATERIAL_H
#define DZWIG_KRATOWNICOWY_PHONG_MATERIAL_H

#include <glm/glm.hpp>

#include "Material.h"
#include "Shader.h"

class PhongMaterial
{
public:
    using Color = glm::vec4;

public:
    explicit PhongMaterial(Color diffuse = Color(1.0f), Color specular = Color(0.5f, 0.5f, 0.5f, 1.0f), float shininess = 0.25);
    explicit PhongMaterial(const char* diffuseMap, const char* specularMap, float shininess = 0.25);

    //  Setup shader
    void applyMaterial(const Shader& shader);

    //
    //  Modify material
    //

    //  Set by color
    void setAmbient(const Color& color = Color(1.0f));
    void setDiffuse(const Color& color = Color(1.0f));
    void setSpecular(const Color& color = Color(0.5f, 0.5f, 0.5f, 1.0f));

    //  Set by texture map
    void setAmbient(const char* ambientMap);
    void setDiffuse(const char* diffuseMap);
    void setSpecular(const char* specularMap);

    void setShininess(float value = 32);

    //  Access underlying material struct
    [[nodiscard]] const Material& getMaterial() const;

private:
    Material material;

    [[nodiscard]] uint32_t generateGLTexture() const;   //  Generates and prepares texture id
    [[nodiscard]] uint32_t loadTexture(const char* path) const;
    [[nodiscard]] uint32_t generateColorTexture(const Color& color) const;
};

#endif //DZWIG_KRATOWNICOWY_PHONG_MATERIAL_H
