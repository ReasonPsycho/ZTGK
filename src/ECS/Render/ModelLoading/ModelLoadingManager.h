//
// Created by redkc on 09/06/2024.
//

#ifndef ZTGK_MODELLOADINGMANAGER_H
#define ZTGK_MODELLOADINGMANAGER_H

#include "ECS/Render/ModelLoading/Animator.h"
#include "ECS/Render/ModelLoading/Model.h"
#include <map>
#include <string>

class ModelLoadingManager  {
    
public:
    Animation *GetAnimation(std::string path, Model *model);
    Model * GetModel (std::string path);
    void Innit();
private:
    bool isInnit = false;
    std::map<std::string, std::shared_ptr<Animation>> animationMap;
    std::map<std::string, std::shared_ptr<Model>> modelMap;
};


#endif //ZTGK_MODELLOADINGMANAGER_H
