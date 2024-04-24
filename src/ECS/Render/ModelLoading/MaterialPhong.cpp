//
// Created by redkc on 15/04/2024.
//

#include "Model.h"
#include "MaterialPhong.h"

Color normalColorlol = {128, 128, 128, 255};  // Normal map neutral
Color specularColor = {255, 255, 255, 255};  // Black, no metallic
Color shininessColor = {0, 0, 0, 255};  // 50% gray

void replaceAlllol(string &str, const string &from, const string &to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

MaterialPhong::MaterialPhong(aiMaterial *material, Model *model) {

// 1. albedo maps
    diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", model);
// 2. normal maps
    if(!diffuseMap){
        spdlog::warn("AlbedoMap doesn't exist replacing it with white !");
        diffuseMap = make_shared<Texture>();
    }

    specularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", model);
// 3. metallic maps

    if(!specularMap){
        spdlog::warn("normalMap doesn't exist replacing it with default normal color!");
        specularMap = make_shared<Texture>(normalColorlol);
    }

    shininessMap = loadMaterialTextures(material, aiTextureType_SHININESS, "texture_shininess", model);
// 4. roughness maps

    if(!shininessMap){
        spdlog::warn("MetallicMap doesn't exist replacing it with default metallic color!");
        shininessMap = make_shared<Texture>(shininessColor);
    }

    normalMap = loadMaterialTextures(material, aiTextureType_SHININESS, "texture_roughness", model);

    if(!normalMap){
        spdlog::warn("RoughnessMap doesn't exist replacing it with default roughness color!");
        normalMap = make_shared<Texture>(normalColorlol);
    }
}

MaterialPhong::MaterialPhong(GLubyte *color) {
    diffuseMap = make_shared<Texture>(*reinterpret_cast<Color*>(color));
    specularMap = make_shared<Texture>(*reinterpret_cast<Color*>(specularColor));
    shininessMap = make_shared<Texture>(*reinterpret_cast<Color*>(shininessColor));
    normalMap = make_shared<Texture>(*reinterpret_cast<Color*>(normalColorlol));
}

std::shared_ptr<Texture>
MaterialPhong::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, Model *model) {
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
            replaceAlllol(texturePath, "/", "\\");
            texture = std::make_shared<Texture>(texturePath, typeName);
            model->textureCatalogue.push_back(
                    texture);  // store it as texture loaded for entire model, to ensure we won't unnecessarily load duplicate textures.
        }
    }
    return texture;
}

void MaterialPhong::loadMaterial(Shader *shader) {
    shader->use();
    glActiveTexture(GL_TEXTURE3); // active proper texture unit before binding
    glUniform1i(glGetUniformLocation(shader->ID, "material.diffuse"), 3);
    glBindTexture(GL_TEXTURE_2D, diffuseMap->ID);

    glActiveTexture(GL_TEXTURE4); // active proper texture unit before binding
    glUniform1i(glGetUniformLocation(shader->ID, "material.specular"), 4);
    glBindTexture(GL_TEXTURE_2D, specularMap->ID);
    
    glActiveTexture(GL_TEXTURE5); // active proper texture unit before binding
    glUniform1i(glGetUniformLocation(shader->ID, "material.shininess"), 5);
    glBindTexture(GL_TEXTURE_2D, shininessMap->ID);

    glActiveTexture(GL_TEXTURE6); // active proper texture unit before binding
    glUniform1i(glGetUniformLocation(shader->ID, "material.normal"), 6);
    glBindTexture(GL_TEXTURE_2D, normalMap->ID);
}
