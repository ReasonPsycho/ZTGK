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

#include <string>
#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include <direct.h>
#include <iostream>


class Model {
public:
    // model data 
    vector<std::shared_ptr<Texture>> textureCatalogue;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;

    Model(string const *path) : path(path) {};
    Model(unsigned int VAO, Material material,vector<unsigned int> indices);
    
    void Draw(Shader &shader);
    void SimpleDraw(Shader &shader);

    void loadModel();
    
    string const *path;
private:

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};


#endif //OPENGLGP_MODEL_H
