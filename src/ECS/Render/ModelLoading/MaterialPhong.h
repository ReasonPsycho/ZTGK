//
// Created by redkc on 15/04/2024.
//

#ifndef ZTGK_MATERIALPHONG_H
#define ZTGK_MATERIALPHONG_H

class Model;

#include "Texture.h"
#include "TextureArray.h"
#include "assimp/material.h"
#include "Shader.h"
using Color = GLubyte[4];

class MaterialPhong {
public:
    MaterialPhong(aiMaterial* material, Model* model);
    MaterialPhong(Color color);
    MaterialPhong();

    std::vector<shared_ptr<Texture>> diffuseTextures;
    std::vector<shared_ptr<Texture>>  specularTextures;
    std::vector<shared_ptr<Texture>>  normalTextures;
    std::vector<shared_ptr<Texture>>  depthTextures;
    
    shared_ptr<TextureArray> diffuseTextureArray; //Just so cmake won't go for my throath for making local variable
    shared_ptr<TextureArray> specularTextureArray;
    shared_ptr<TextureArray> normalTextureArray;
    shared_ptr<TextureArray> depthTextureArray;
    
    void loadMaterial(Shader* shader);
    void loadInstancedMaterial(Shader* shader);
    void loadReapetedInstancedMaterial(Shader* shader);
    void mapTextureArrays();
    std::shared_ptr<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName,Model* model);
};


#endif //ZTGK_MATERIALPHONG_H
