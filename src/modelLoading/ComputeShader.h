//
// Created by redkc on 15/12/2023.
//

#ifndef OPENGLGP_COMPUTESHADER_H
#define OPENGLGP_COMPUTESHADER_H

#include <glbinding/gl/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "spdlog/spdlog.h"
#include "glm/detail/type_vec3.hpp"
#include "glm/vec3.hpp"

using namespace gl;

class ComputeShader {
public:
    // the program ID
    GLuint ID{};

    // constructor reads and builds the shader
    ComputeShader(const char* shaderPath);

    // use/activate the shader
    void use() const;
    void init();
    void setLayout(int localSizeX,int localSizeY,int localSizeZ);
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setGLuint(const std::string &name, GLuint value) const;
    void setMatrix4(const std::string &name, bool transpose, const GLfloat *value) const;

    void setVec3(const std::string &name, float d, float d1, float d2);
    void setVec3(const std::string &name, glm::vec3 vec3);
private:
    std::string shaderCode;
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    static void checkCompileErrors(unsigned int shader, std::string type);
};


#endif //OPENGLGP_COMPUTESHADER_H
