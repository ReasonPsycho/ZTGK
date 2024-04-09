//
// Created by redkc on 15/12/2023.
//

#include "ComputeShader.h"


ComputeShader::ComputeShader(const char *shaderPath) : computeShaderPath(shaderPath) {
    std::ifstream cShaderFile;
    // ensure ifstream objects can throw exceptions:
    cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        cShaderFile.open(shaderPath);

        std::stringstream cShaderStream;
        // read file's buffer contents into streams
        cShaderStream << cShaderFile.rdbuf();
        // close file handlers
        cShaderFile.close();
        // convert stream into string
        shaderCode = cShaderStream.str();
    }
    catch (std::ifstream::failure &e) {
        spdlog::error("FILE_NOT_SUCCESSFULLY_READ:", e.what());
    }
}

void ComputeShader::setLayout(int localSizeX, int localSizeY, int localSizeZ) {
    std::string toBeReplaced = "//HERE SHOULD BE LAYOUT";
    std::size_t foundPos = shaderCode.find(toBeReplaced);
    if (foundPos == std::string::npos) return;
    std::string newLayout =
            " layout (local_size_x = " + std::to_string(localSizeX) + ", local_size_y = " + std::to_string(localSizeY) +
            ", local_size_z = " + std::to_string(localSizeZ) + ") in;";
    shaderCode.replace(foundPos, toBeReplaced.size(), newLayout);
}

void ComputeShader::init() {
// 1. retrieve the vertex/fragment source code from filePath
    if (shaderCode.empty()) return; // No code no init

    std::string toBeReplaced = "//HERE SHOULD BE LAYOUT"; // set defouglt layout if it doesn't work
    if (shaderCode.find(toBeReplaced) != std::string::npos) {
        setLayout(1, 1, 1);
    }

    const char *cShaderCode = shaderCode.c_str();
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

void ComputeShader::setMatrix4(const std::string &name, bool transpose, const GLfloat *value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, transpose, value);
}

void ComputeShader::setVec3(const std::string &name, float d, float d1, float d2) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), d, d1, d2);
}

void ComputeShader::setVec3(const std::string &name, glm::vec3 vec3) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec3.x, vec3.y, vec3.z);

}

void ComputeShader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error("Shader in editor_path: " + computeShaderPath + " has compilation error of type: " + type + infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::error("Shader in editor_path: " + computeShaderPath + " has compilation error of type: " + type + infoLog);
        }
    }
}




