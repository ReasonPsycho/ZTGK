// 
// Created by redkc on 21/03/2024. 
// 
 
#ifndef ZTGK_MATERIALPBR_H 
#define ZTGK_MATERIALPBR_H 
 
 
class Model; 
#include "Texture.h" 
#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h> 
using Color = GLubyte[4]; 
 
class MaterialPBR { 
 
public: 
    MaterialPBR(aiMaterial* material, Model* model); 
    MaterialPBR(Color color); 
     
    shared_ptr<Texture> albedoMap; 
    shared_ptr<Texture> normalMap; 
    shared_ptr<Texture> metallicMap; 
    shared_ptr<Texture> roughnessMap; 
    shared_ptr<Texture> aoMap; 
     
   void loadMaterial(Shader* shader); 
     
    std::shared_ptr<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName,Model* model); 
    std::shared_ptr<Texture> forceLoadMaterialTexture(string path, aiTextureType type, string typeName,Model* model); 
}; 
 
 
#endif //ZTGK_MATERIALPBR_H 
