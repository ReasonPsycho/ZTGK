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


class Model {
public:
    // model data 
    vector<std::shared_ptr<Texture>> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    Model(string const *path, bool gamma = false) : path(path), gammaCorrection(gamma) {};

    void Draw(Shader &shader);

    void loadModel();

    glm::vec3 futhestLenghtsFromCenter;

    void SimpleDraw(Shader &shader);

private:
    string const *path;

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

};


#endif //OPENGLGP_MODEL_H
