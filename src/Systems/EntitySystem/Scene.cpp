//
// Created by redkc on 18/02/2024.
//

#include "Scene.h"

void Scene::drawScene(Shader &regularShader) {
    for (auto &&child: children) {
        child->drawSelfAndChild(regularShader);
    }
}

void Scene::drawScene(Shader &regularShader,Shader &instancedShader) {
    for (auto &&child: children) {
        child->drawSelfAndChild(regularShader,instancedShader);
    }
}

void Scene::updateScene() {
    for (auto &&child: children) {
        child->updateSelfAndChild();
    }
}
