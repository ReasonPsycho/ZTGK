//
// Created by redkc on 18/02/2024.
//

#ifndef REASONABLEGL_SCENE_H
#define REASONABLEGL_SCENE_H

#include "../SystemManager.h"
#include "modelLoading/Shader.h"
#include "ECS/Entity.h"

class Scene {
public:
    Scene() = default;

    Entity* addGameObject();
    Entity* addGameObject(Entity* parent);
    
    void updateScene();
    
    SystemManager systemManager;
    
private:
    std::vector<std::unique_ptr<Entity>> children;
};


#endif //REASONABLEGL_SCENE_H
