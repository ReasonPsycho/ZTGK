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

using Color = GLubyte[4];


class Texture {
public:
    Texture(string path, string type); //TODO change this to enum
    Texture( const Color& color = {0, 0, 0, 0}); 

    ~Texture();

    // the texture ID
    GLuint ID{};
    string path;
    string type; //TODO remove this shit
    string name;
    GLenum format;
    int width, height, nrChannels;
    // constructor reads and builds the texture
    void use(GLenum GL_TEXTUREX);
};


#endif 
