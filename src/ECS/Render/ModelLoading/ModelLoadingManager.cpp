//
// Created by redkc on 09/06/2024.
//

#include "ModelLoadingManager.h"

Animation * ModelLoadingManager::GetAnimation(std::string path, Model *model) {
    auto it = animationMap.find(path);

    if (it != animationMap.end())
    {
        // Found the key in the map, check if it has non-null pointer
        if(it->second != nullptr)
        {
            // The map contains the pointer
            return it->second.get();
        }
        else
        {
            animationMap[path] = make_shared<Animation>(path,model);
            return animationMap[path].get();
        }
    }
    return nullptr;
}

Model * ModelLoadingManager::GetModel(std::string path) {
    auto it = modelMap.find(path);

    if (it != modelMap.end())
    {
        // Found the key in the map, check if it has non-null pointer
        if(it->second != nullptr)
        {
            // The map contains the pointer
            return it->second.get();
        }
        else
        {
            modelMap[path]= std::make_shared<Model>(&path);
            if(isInnit){
                modelMap[path]->loadModel();
            }
            return modelMap[path].get();
            // The map does not contain the pointer
        }
    }
    return nullptr;
}

void ModelLoadingManager::Innit() {
    isInnit = true;
    for (auto model: modelMap) {
        model.second->loadModel();
    }
}
