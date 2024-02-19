//
// Created by redkc on 18/02/2024.
//

#ifndef REASONABLEGL_SCENE_H
#define REASONABLEGL_SCENE_H


#include "Systems/EntitySystem/Enitities/Enitity.h"

class Scene {
public:
    std::vector<std::shared_ptr<Entity>> children;
    void drawScene(Shader &regularShader);
    void drawScene(Shader &regularShader,Shader &instancedShader);
    void updateScene();

    void addChild(std::shared_ptr<Entity> child) {
        children.push_back(child);
    }
    
    Scene() = default;
};


#endif //REASONABLEGL_SCENE_H
