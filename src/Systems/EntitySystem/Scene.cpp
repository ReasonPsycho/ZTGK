//
// Created by redkc on 18/02/2024.
//

#include "Scene.h"

void Scene::updateScene() {
    for (auto &&child: children) {
        child->updateSelfAndChild();
    }
}

Entity* Scene::addGameObject() {
    children.push_back(make_unique<Entity>(&systemManager));
    return children.back().get();
}

Entity* Scene::addGameObject(Entity* parent) {
    return parent->addChild(make_unique<Entity>(&systemManager));
}
