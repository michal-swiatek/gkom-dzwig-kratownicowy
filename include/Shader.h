/*
 *  Created by michal-swiatek on 19.05.2020.
 *  http://gitlab.ii.pw.edu.pl/gkom.20l/dzwig-kratownicowy
 */

#ifndef DZWIG_KRATOWNICOWY_SHADER_H
#define DZWIG_KRATOWNICOWY_SHADER_H

#include <cstdint>
#include <string>

#include <../external-libraries/include/GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader
{
public:
    // Builds shader program
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    Shader(Shader&& other) noexcept;

    void use() const; // Activate shader program
    void destroyProgram();

    [[nodiscard]] GLuint getProgramID() const;

    //
    //  Setting uniforms
    //

    //  Scalars
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    //  Vectors
    void setVector2f(const std::string& name, const glm::vec2& vector) const;
    void setVector3f(const std::string& name, const glm::vec3& vector) const;
    void setVector4f(const std::string& name, const glm::vec4& vector) const;

    //  Matrices
    void setMatrix2f(const std::string& name, const glm::mat2& matrix) const;
    void setMatrix3f(const std::string& name, const glm::mat3& matrix) const;
    void setMatrix4f(const std::string& name, const glm::mat4& matrix) const;

private:
    GLuint programID;
    bool destroyed;

    std::string readShaderSource(const char* shaderPath) const;
    GLuint compileShader(GLuint type, const char* shaderCode) const;
    [[nodiscard]] GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) const;
};

#endif //DZWIG_KRATOWNICOWY_SHADER_H
