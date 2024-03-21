//
// Created by redkc on 21/03/2024.
//
#include "Model.h"
#include "Material.h"

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
    
    if(!texture){
        spdlog::warn(texturePath + "Texture dosn't exist replacing it with black pixel");
        texture = make_shared<Texture>();
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
    
    if(!texture){
        spdlog::warn(path + " Texture doesn't exist replacing it with black pixel");
        texture = make_shared<Texture>();
    }
    
    return texture;
}

Material::Material(aiMaterial *material, Model *model) {
    
// 1. albedo maps
    albedoMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_albedo", model);
// 2. normal maps
    normalMap = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal", model);
// 3. metallic maps
    metallicMap = loadMaterialTextures(material, aiTextureType_METALNESS, "texture_metallic", model);
// 4. roughness maps
    roughnessMap = loadMaterialTextures(material, aiTextureType_SHININESS, "texture_roughness", model);

    string albedoPath = albedoMap->path;
    string aoPath = albedoPath.substr(0, albedoPath.find_last_of('_')) + "_ao.png";
    aoMap = forceLoadMaterialTexture(aoPath, aiTextureType_AMBIENT_OCCLUSION, "texture_ao", model);
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
    Color defaultColor = {255, 255, 255, 255};
    Color& colorToUse = color ? (*reinterpret_cast<Color*>(color)) : defaultColor;
    albedoMap = make_shared<Texture>(colorToUse);
    normalMap = make_shared<Texture>();
    metallicMap = make_shared<Texture>();
    roughnessMap = make_shared<Texture>();
    aoMap = make_shared<Texture>();
}