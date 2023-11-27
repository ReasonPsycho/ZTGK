#ifndef TEXTURE_H
#define TEXTURE_H

#include <glbinding/gl/gl.h>
#include "stb_image.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "spdlog/spdlog.h"
using namespace gl;

class Texture{
public:
    Texture(const char* texturePath) :texturePath(texturePath) {}
    ~Texture();
    // the texture ID
    GLuint ID{}; // TODO add more than one texture on top of it
    
    // constructor reads and builds the texture
    void use();
    void init();
    
private:
    const char* texturePath;
};


#endif 
