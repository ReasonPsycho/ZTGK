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
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0); // Position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float))); // Texture Coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float quadVertices[] = {
            // positions      // normals        // texture coords
            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0); // Position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float))); // Texture Coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    for (int i = 0; i < numberOfDetails; ++i) {
        unsigned int tmp = 1;
        glGenVertexArrays(1, &tmp);
        subdividedPlaneVAO.push_back(tmp);

        glGenBuffers(1, &tmp);
        subdividedPlaneVBO.push_back(tmp);

        glGenBuffers(1, &tmp);
        subdividedPlaneEBO.push_back(tmp);

        createSubdividedPlane(i + 1);

        glBindVertexArray(subdividedPlaneVAO.back());

        glBindBuffer(GL_ARRAY_BUFFER, subdividedPlaneVBO.back());
        glBufferData(GL_ARRAY_BUFFER, subdividedPlanesVertices.back().size() * sizeof(GLfloat), subdividedPlanesVertices.back().data(), GL_STATIC_DRAW);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subdividedPlaneEBO.back());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, subdividedPlanesIndices.back().size() * sizeof(GLfloat), subdividedPlanesIndices.back().data(), GL_STATIC_DRAW);


        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *) 0); // Position
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *) (3 * sizeof(float))); // Normals
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *) (6 * sizeof(float))); // Texture Coords
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *) (8 * sizeof(float))); // Tangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void *) (11 * sizeof(float))); //Bittangent
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

PBRPrimitives::~PBRPrimitives() {

}

void PBRPrimitives::createSubdividedPlane(int subdivisions) {

    std::vector<GLfloat> tmpVertices;
    std::vector<GLfloat> tmpTangentVertices;
    std::vector<unsigned int> tmpIndices;
    std::vector<unsigned int> tmpTangentIndices;
    for (int i = 0; i <= subdivisions; ++i) {
        for (int j = 0; j <= subdivisions; ++j) {
            float xT = (float) i / (float) subdivisions;
            float yT = (float) j / (float) subdivisions;
            float x = glm::mix(-1.0, 1.0, xT);
            float y = glm::mix(-1.0, 1.0, yT);

            //Plane was sideways orginaly didn't notice that ups...

            tmpVertices.push_back(x);
            tmpVertices.push_back(y);
            tmpVertices.push_back(0);

            tmpVertices.push_back(0);
            tmpVertices.push_back(0);
            tmpVertices.push_back(1);

            tmpVertices.push_back(xT); // Textures
            tmpVertices.push_back(yT);
        }
    }

    // Create indices
    for (int i = 0; i < subdivisions; ++i) {
        for (int j = 0; j < subdivisions; ++j) {
            int row1 = i * (subdivisions + 1);
            int row2 = (i + 1) * (subdivisions + 1);

            // Each square is divided into two triangles
            tmpIndices.push_back(row1 + j);
            tmpIndices.push_back(row1 + j + 1);
            tmpIndices.push_back(row2 + j);

            tmpIndices.push_back(row2 + j);
            tmpIndices.push_back(row1 + j + 1);
            tmpIndices.push_back(row2 + j + 1);
        }
    }

    // For each triangle
    for (int i = 0; i < subdivisions * subdivisions * 2; i++) {

        // Get indices for triangle
        unsigned int i0 = tmpIndices[i * 3 + 0];
        unsigned int i1 = tmpIndices[i * 3 + 1];
        unsigned int i2 = tmpIndices[i * 3 + 2];

        glm::vec3 v0(tmpVertices[i0 * 8 + 0], tmpVertices[i0 * 8 + 1], tmpVertices[i0 * 8 + 2]);
        glm::vec3 v1(tmpVertices[i1 * 8 + 0], tmpVertices[i1 * 8 + 1], tmpVertices[i1 * 8 + 2]);
        glm::vec3 v2(tmpVertices[i2 * 8 + 0], tmpVertices[i2 * 8 + 1], tmpVertices[i2 * 8 + 2]);

        glm::vec2 uv0(tmpVertices[i0 * 8 + 6], tmpVertices[i0 * 8 + 7]);
        glm::vec2 uv1(tmpVertices[i1 * 8 + 6], tmpVertices[i1 * 8 + 7]);
        glm::vec2 uv2(tmpVertices[i2 * 8 + 6], tmpVertices[i2 * 8 + 7]);

        glm::vec3 deltaPos1 = v1 - v0;
        glm::vec3 deltaPos2 = v2 - v0;

        glm::vec2 deltaUV1 = uv1 - uv0;
        glm::vec2 deltaUV2 = uv2 - uv0;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);


        glm::vec3 tangent = glm::vec3(
                f * (deltaUV2.y * deltaPos1.x - deltaUV1.y * deltaPos2.x),
                f * (deltaUV2.y * deltaPos1.y - deltaUV1.y * deltaPos2.y),
                f * (deltaUV2.y * deltaPos1.z - deltaUV1.y * deltaPos2.z)
        );
        tangent = glm::normalize(tangent);
        glm::vec3 bitangent = glm::vec3(
                f * (-deltaUV2.x * deltaPos1.x + deltaUV1.x * deltaPos2.x),
                f * (-deltaUV2.x * deltaPos1.y + deltaUV1.x * deltaPos2.y),
                f * (-deltaUV2.x * deltaPos1.z + deltaUV1.x * deltaPos2.z)
        );
        bitangent = glm::normalize(bitangent);


        for (int j = 0; j < 3; j++) {
            int index = tmpIndices[i * 3 + j];
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 0]);
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 1]);
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 2]);
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 3]);
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 4]);
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 5]);
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 6]);
            tmpTangentVertices.push_back(tmpVertices[index * 8 + 7]);
            tmpTangentVertices.push_back(tangent.x);
            tmpTangentVertices.push_back(tangent.y);
            tmpTangentVertices.push_back(tangent.z);
            tmpTangentVertices.push_back(bitangent.x);
            tmpTangentVertices.push_back(bitangent.y);
            tmpTangentVertices.push_back(bitangent.z);
            tmpTangentIndices.push_back(i * 3 + j);
        }
    }

    subdividedPlanesVertices.push_back(tmpTangentVertices);
    subdividedPlanesIndices.push_back(tmpTangentIndices);
}
