#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "spdlog/spdlog.h"
#include "glad/glad.h"

using namespace std;

class Texture{
public:
    Texture(string name , string directory,string type) ;
    ~Texture();
    // the texture ID
    GLuint ID{}; // TODO add more than one texture on top of it
    string type;
    string name;
    string directory;
    
    // constructor reads and builds the texture
    void use(GLenum GL_TEXTUREX);
};


#endif 
