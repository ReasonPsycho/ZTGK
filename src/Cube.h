//
// Created by redkc on 20/11/2023.
//

#ifndef OPENGLGP_CUBE_H
#define OPENGLGP_CUBE_H



#include "Utilities/Shader.h"
#include "Utilities/Texture.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace gl;

class Cube { // A class to hold cube (to test concept)
public:
    Cube();
    ~Cube();
    
    void init();
    void render(Shader* shaderProgram, Texture* texture);
private:
    GLuint VBO, VAO, EBO;
    glm::mat4 model;

};


#endif //OPENGLGP_CUBE_H
