//
// Created by redkc on 02/12/2023.
//

#ifndef OPENGLGP_MESH_H
#define OPENGLGP_MESH_H

using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Material.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

class Mesh {
public:
    // mesh Data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Material material;
    unsigned int VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material material);
    Mesh(unsigned int VAO, Material material,vector<unsigned int> indices);

    void setupMesh();

    void Draw(Shader &shader);

private:
    // render data 
    unsigned int VBO, EBO;

};


#endif //OPENGLGP_MESH_H
