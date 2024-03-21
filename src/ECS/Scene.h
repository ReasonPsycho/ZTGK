//
// Created by redkc on 18/02/2024.
//

#ifndef REASONABLEGL_SCENE_H
#define REASONABLEGL_SCENE_H

#include "ECS/Entity.h"

class Scene {
public:
    Scene() = default;

    Entity *addEntity(std::string name);
    
    Entity *addEntity(Entity *parent, std::string name);
    
    void updateScene();
    
    SystemManager systemManager;

    void showImGuiDetails(Camera *camera);
    
private:
    std::vector<std::unique_ptr<Entity>> children;
};


#endif //REASONABLEGL_SCENE_H
