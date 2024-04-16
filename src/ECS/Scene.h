//
// Created by redkc on 18/02/2024.
//

#ifndef REASONABLEGL_SCENE_H
#define REASONABLEGL_SCENE_H

#include "SystemManager.h"
class Collider;

class Scene {
public:
    Scene() = default;

    Entity *addEntity(std::string name);
    
    Entity *addEntity(Entity *parent, std::string name);

    void removeChild(Entity *child);
    
    void updateScene();
    
    int selectedEntityNumber = -1;
    
    SystemManager systemManager;

    void showImGuiDetails(Camera *camera);
    
    bool stopRenderingImgui = false;

    std::vector<std::unique_ptr<Entity>>& getChildren();
    
    
private:
    std::vector<std::unique_ptr<Entity>> children;
};


#endif //REASONABLEGL_SCENE_H
