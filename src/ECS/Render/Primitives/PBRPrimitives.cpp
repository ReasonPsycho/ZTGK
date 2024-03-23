//
// Created by redkc on 21/03/2024.
//

#include "PBRPrimitives.h"

void PBRPrimitives::renderCube() {

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void PBRPrimitives::renderQuad() {
    glBindVertexArray(quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

PBRPrimitives::PBRPrimitives() {
  
}

void PBRPrimitives::Init() {
    float cubeVertices[] = {
            // positions      // normals        // texture coords
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    };

    unsigned int cubeIndices[] = {
            0, 1, 2, 2, 3, 0,   // back face
            4, 5, 6, 6, 7, 4,   // front face
            3, 2, 6, 6, 7, 3,   // top face
            0, 1, 5, 5, 4, 0,   // bottom face
            0, 3, 7, 7, 4, 0,   // left face
            1, 2, 6, 6, 5, 1    // right face
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture Coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float quadVertices[] = {
            // positions      // normals        // texture coords
            -1.0f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -1.0f, -1.0f, 0.0f,   0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            1.0f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            1.0f, -1.0f, 0.0f,   0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    };

    unsigned int quadIndices[] = {
            0, 1, 2,   // First Triangle
            1, 2, 3    // Second Triangle
    };


    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &quadEBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture Coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
