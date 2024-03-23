//
// Created by redkc on 21/03/2024.
//

#ifndef ZTGK_PBRPRIMITIVES_H
#define ZTGK_PBRPRIMITIVES_H

#include "ECS/Render/Camera/Camera.h"

class PBRPrimitives {
public:
    GLuint cubeVAO, cubeVBO, cubeEBO;
    GLuint quadVAO, quadVBO, quadEBO;

     GLfloat cubeVertices[8*8];
     GLuint cubeIndices[36];

     GLfloat quadVertices[8*4];
     GLuint quadIndices[6];


    PBRPrimitives();
    void Init();
    void renderCube();
    void renderQuad();
};


#endif //ZTGK_PBRPRIMITIVES_H
