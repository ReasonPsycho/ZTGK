//
// Created by redkc on 21/03/2024.
//

#ifndef ZTGK_PRIMITIVES_H
#define ZTGK_PRIMITIVES_H

#include "ECS/Render/Camera/Camera.h"

class Primitives {
public:
    GLuint cubeVAO, cubeVBO, cubeEBO;
    GLuint quadVAO, quadVBO, quadEBO;
    
     GLfloat cubeVertices[24];
     GLuint cubeIndices[36];

     GLfloat quadVertices[20];
     GLuint quadIndices[6];


    Primitives();
    void Init();
    void renderCube();
    void renderQuad();
};


#endif //ZTGK_PRIMITIVES_H
