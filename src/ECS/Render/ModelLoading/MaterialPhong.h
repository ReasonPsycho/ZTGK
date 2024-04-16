//
// Created by redkc on 15/04/2024.
//

#ifndef ZTGK_MATERIALPHONG_H
#define ZTGK_MATERIALPHONG_H

class Model;

#include "Texture.h"
#include "assimp/material.h"
#include "Shader.h"
using Color = GLubyte[4];

class MaterialPhong {
public:
    MaterialPhong(aiMaterial* material, Model* model);
    explicit MaterialPhong(Color color);

    shared_ptr<Texture> diffuseMap;
    shared_ptr<Texture> specularMap;
    shared_ptr<Texture> normalMap;
    shared_ptr<Texture> shininessMap;

    void loadMaterial(Shader* shader);

    std::shared_ptr<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName,Model* model);
};


#endif //ZTGK_MATERIALPHONG_H
