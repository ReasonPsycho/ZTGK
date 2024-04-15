#ifndef SHADER_H
#define SHADER_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include "spdlog/spdlog.h"
#include "glm/detail/type_vec3.hpp"
#include "glm/vec3.hpp"
#include "glad/glad.h"
#include "glm/vec4.hpp"
#include "glm/vec2.hpp"


class Shader {
public:
    // the program ID
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath)
            : vertexPath(vertexPath), fragmentPath(fragmentPath) {}


    Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
            : vertexPath(vertexPath), fragmentPath(fragmentPath), geometryPath(geometryPath) {}

    // use/activate the shader
    void use() const;

    void init();

    void initWithGeometry();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setGLuint(const std::string &name, GLuint value) const;

    void setMatrix4(const std::string &name, bool transpose, const GLfloat *value) const;

    void setVec2(const std::string &name, glm::vec2 vec2);

    void setVec3(const std::string &name, float d, float d1, float d2);

    void setVec3(const std::string &name, glm::vec3 vec3);

    void setVec4(const std::string &name, glm::vec4 vec4);

private:
    const char *vertexPath{};
    const char *fragmentPath{};
    const char *geometryPath{};

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);

};

#endif
