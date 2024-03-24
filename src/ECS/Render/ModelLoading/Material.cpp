//
// Created by redkc on 21/03/2024.
//
#include "Model.h"
#include "Material.h"


Color normalColor = {128, 128, 255, 255};  // Normal map neutral
Color metallicColor = {0, 0, 0, 255};  // Black, no metallic
Color roughnessColor = {128, 128, 128, 255};  // 50% gray
Color aoColor = {255, 255, 255, 255};  // White

void replaceAll(string &str, const string &from, const string &to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::shared_ptr<Texture>
Material::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, Model *model) {
    std::shared_ptr<Texture> texture;
    string texturePath;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < model->textureCatalogue.size(); j++) {
            if (std::strcmp(model->textureCatalogue[j]->path.c_str(), str.C_Str()) == 0) {
                texture = model->textureCatalogue[j];
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip) {   // if texture hasn't been loaded already, load it
            model->directory = model->path->substr(0, model->path->find_last_of('/'));
            texturePath = string(model->directory + "\\" + str.C_Str());
            replaceAll(texturePath, "/", "\\");
            texture = std::make_shared<Texture>(texturePath, typeName);
            model->textureCatalogue.push_back(
                    texture);  // store it as texture loaded for entire model, to ensure we won't unnecessarily load duplicate textures.
        }
    }
    return texture;
}

std::shared_ptr<Texture>
Material::forceLoadMaterialTexture(string path, aiTextureType type, string typeName, Model *model) {
    std::shared_ptr<Texture> texture;
    // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    bool skip = false;
    for (unsigned int j = 0; j < model->textureCatalogue.size(); j++) {
        if (std::strcmp(model->textureCatalogue[j]->path.c_str(), path.c_str()) == 0) {
            texture = model->textureCatalogue[j];
            skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
            break;
        }
    }
    if (!skip) {   // if texture hasn't been loaded already, load it
        texture = std::make_shared<Texture>(path, typeName);
        model->textureCatalogue.push_back(
                texture);  // store it as texture loaded for entire model, to ensure we won't unnecessarily load duplicate textures.
    }
    return texture;
}

Material::Material(aiMaterial *material, Model *model) {
    
// 1. albedo maps
    albedoMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_albedo", model);
// 2. normal maps
    if(!albedoMap){
        spdlog::warn("AlbedoMap doesn't exist replacing it with white !");
        albedoMap = make_shared<Texture>();
    }

    normalMap = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal", model);
// 3. metallic maps

    if(!normalMap){
        spdlog::warn("normalMap doesn't exist replacing it with default normal color!");
        normalMap = make_shared<Texture>(normalColor);
    }

    metallicMap = loadMaterialTextures(material, aiTextureType_METALNESS, "texture_metallic", model);
// 4. roughness maps

    if(!metallicMap){
        spdlog::warn("MetallicMap doesn't exist replacing it with default metallic color!");
        metallicMap = make_shared<Texture>(metallicColor);
    }

    roughnessMap = loadMaterialTextures(material, aiTextureType_SHININESS, "texture_roughness", model);

    if(!roughnessMap){
        spdlog::warn("RoughnessMap doesn't exist replacing it with default roughness color!");
        roughnessMap = make_shared<Texture>(roughnessColor);
    }
    
    string albedoPath = albedoMap->path;
    string aoPath = albedoPath.substr(0, albedoPath.find_last_of('_')) + "_ao.png";
    aoMap = forceLoadMaterialTexture(aoPath, aiTextureType_AMBIENT_OCCLUSION, "texture_ao", model);

    if(!aoMap){
        spdlog::warn("AoMap doesn't exist replacing it with default ao color!");
        aoMap = make_shared<Texture>(aoColor);
    }
}

 void Material::loadMaterial(Shader* shader) {
     glActiveTexture(GL_TEXTURE3); // active proper texture unit before binding
     glUniform1i(glGetUniformLocation(shader->ID, "texture_albedo"), 3);
     glBindTexture(GL_TEXTURE_2D, albedoMap->ID);
     
     glActiveTexture(GL_TEXTURE4); // active proper texture unit before binding
     glUniform1i(glGetUniformLocation(shader->ID, "texture_normal"), 4);
     glBindTexture(GL_TEXTURE_2D, normalMap->ID);

     glActiveTexture(GL_TEXTURE5); // active proper texture unit before binding
     glUniform1i(glGetUniformLocation(shader->ID, "texture_metallic"), 5);
     glBindTexture(GL_TEXTURE_2D, metallicMap->ID);
     
     glActiveTexture(GL_TEXTURE6); // active proper texture unit before binding
     glUniform1i(glGetUniformLocation(shader->ID, "texture_height"), 6); //TODO change naming
     glBindTexture(GL_TEXTURE_2D, roughnessMap->ID);

     glActiveTexture(GL_TEXTURE7); // active proper texture unit before binding
     glUniform1i(glGetUniformLocation(shader->ID, "texture_ao"), 7);
     glBindTexture(GL_TEXTURE_2D, aoMap->ID);
 }


Material::Material(GLubyte *color) {
    albedoMap = make_shared<Texture>(*reinterpret_cast<Color*>(color));
    normalMap = make_shared<Texture>(*reinterpret_cast<Color*>(normalColor));
    metallicMap = make_shared<Texture>(*reinterpret_cast<Color*>(metallicColor));
    roughnessMap = make_shared<Texture>(*reinterpret_cast<Color*>(roughnessColor));
    aoMap = make_shared<Texture>(*reinterpret_cast<Color*>(aoColor));
}