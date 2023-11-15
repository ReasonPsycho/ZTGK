#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // the program ID
    unsigned int ID{};

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath)
            : vertexPath(vertexPath), fragmentPath(fragmentPath){}

    // use/activate the shader
    void use() const;
    void init();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    const char* vertexPath{};
    const char* fragmentPath{};
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    static void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
