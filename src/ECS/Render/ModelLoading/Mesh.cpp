// 
// Created by redkc on 02/12/2023. 
// 
 
#include "Mesh.h" 
 
#ifndef MESH_H 
#define MESH_H 
 
 
using namespace std; 
 
 
// constructor 
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, MaterialPhong material) : vertices( 
        vertices), indices(indices), material(material) { 
    // now that we have all the required data, set the vertex buffers and its attribute pointers. 
    setupMesh(); 
} 
 
 
// render the mesh 
void Mesh::Draw(Shader &shader) { 
     
    material.loadMaterial(&shader); 
 
    // draw mesh 
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0); 
    glBindVertexArray(0); 
 
    // always good practice to set everything back to defaults once configured. 
    glActiveTexture(GL_TEXTURE0); 
} 
void Mesh::SimpleDraw(Shader &shader) { 
     
    // draw mesh 
    glBindVertexArray(VAO); 
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0); 
    glBindVertexArray(0); 
 
    // always good practice to set everything back to defaults once configured. 
    glActiveTexture(GL_TEXTURE0); 
} 
 
// initializes all the buffer objects/arrays 
void Mesh::setupMesh() { 
    // create buffers/arrays 
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO); 
 
    glBindVertexArray(VAO); 
    // load data into vertex buffers 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    // A great thing about structs is that their memory layout is sequential for all its items. 
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which 
    // again translates to 3/2 floats which translates to a byte array. 
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); 
 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); 
 
    // set the vertex attribute pointers 
    // vertex Positions 
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0); 
    // vertex normals  
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal)); 
    // vertex texture coords 
    glEnableVertexAttribArray(2); 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords)); 
    // vertex tangent 
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Tangent)); 
    // vertex bitangent 
    glEnableVertexAttribArray(4); 
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Bitangent)); 
    // ids 
    glEnableVertexAttribArray(5); 
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void *) offsetof(Vertex, m_BoneIDs)); 
    // weights 
    glEnableVertexAttribArray(6); 
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, m_Weights)); 
    glBindVertexArray(0); 
} 
 
Mesh::Mesh(unsigned int VAO, MaterialPhong material, vector<unsigned int> indices): VAO(VAO), material(material), indices(indices) { 
 
} 
 
 
#endif 
