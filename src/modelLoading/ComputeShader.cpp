//
// Created by redkc on 15/12/2023.
//

#include "ComputeShader.h"

void ComputeShader::init() {
// 1. retrieve the vertex/fragment source code from filePath
    std::string computeCode;
    std::ifstream cShaderFile;
    // ensure ifstream objects can throw exceptions:
    cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        cShaderFile.open(shaderPath);

        std::stringstream cShaderStream;
        // read file's buffer contents into streams
        cShaderStream << cShaderFile.rdbuf();
        // close file handlers
        cShaderFile.close();
        // convert stream into string
        computeCode = cShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* cShaderCode = computeCode.c_str();
    // 2. compile shaders
    unsigned int compute;
    // compute shader
    compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &cShaderCode, NULL);
    glCompileShader(compute);
    checkCompileErrors(compute, "COMPUTE");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, compute);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(compute);
}

void ComputeShader::use() const {
    glUseProgram(ID);
}

void ComputeShader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}
void ComputeShader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void ComputeShader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void ComputeShader::setGLuint(const std::string &name, GLuint value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}
void ComputeShader::setMatrix4(const std::string &name,bool transpose, const GLfloat *value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1, transpose, value);
}

void ComputeShader::setVec3(const std::string &name, float d, float d1, float d2) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()),d, d1, d2);
}

void ComputeShader::setVec3(const std::string &name, glm::vec3 vec3) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()),vec3.x, vec3.y, vec3.z);

}

void ComputeShader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error( "ComputeShader compilation error of type: " + type + infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error( "ComputeShader compilation error of type:  " + type + infoLog);
        }
    }
}


