// 
// Created by redkc on 02/12/2023. 
// 
 
#ifndef OPENGLGP_MODEL_H 
#define OPENGLGP_MODEL_H 
 
 
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h> 
 
using namespace std; 
 
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include "map" 
#include <string> 
#include <vector> 
#include "AssimpGLMHelpers.h" 
 
#include "Shader.h" 
#include "Texture.h" 
#include "Mesh.h" 
#include <direct.h> 
#include <iostream> 
 
struct BoneInfo 
{ 
    /*id is index in finalBoneMatrices*/ 
    int id; 
 
    /*offset matrix transforms vertex from model space to bone space*/ 
    glm::mat4 offset; 
 
}; 
 
class Model { 
public: 
    // model data  
    vector<std::shared_ptr<Texture>> textureCatalogue;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once. 
    vector<Mesh> meshes; 
    string directory; 
 
    std::map<string, BoneInfo> m_BoneInfoMap; // 
    int m_BoneCounter = 0; 
 
    auto& GetBoneInfoMap() { return m_BoneInfoMap; } 
    int& GetBoneCount() { return m_BoneCounter; } 
    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene); 
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight); 
 
    void SetVertexBoneDataToDefault(Vertex& vertex); 
 
 
    Model(){}; 
    Model(string const *path) : path(path) {}; 
    Model(unsigned int VAO, MaterialPhong material, vector<unsigned int> indices); 
     
     
    void Draw(Shader &shader); 
    void SimpleDraw(Shader &shader); 
     
    void loadModel(); 
     
    string const *path; 
private: 
 
    void processNode(aiNode *node, const aiScene *scene); 
 
    Mesh processMesh(aiMesh *mesh, const aiScene *scene); 
}; 
 
 
#endif //OPENGLGP_MODEL_H 
