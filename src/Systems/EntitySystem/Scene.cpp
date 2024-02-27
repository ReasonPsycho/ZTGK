//
// Created by redkc on 18/02/2024.
//

#include "Scene.h"

void Scene::updateScene() {
    for (auto &&child: children) {
        child->updateSelfAndChild();
    }
}

Entity * Scene::addGameObject(string name) {
    children.push_back(make_unique<Entity>(&systemManager,name));
    return children.back().get();
}

Entity * Scene::addGameObject(Entity *parent, string name) {
    return parent->addChild(make_unique<Entity>(&systemManager,name));
}

void Scene::showImGuiDetails(Camera *camera) {
    ImGui::Begin("Scene");
    if (ImGui::TreeNode("Entities")) {
        for (auto &child: children) {
            child->showImGuiDetails(camera);
        }
        ImGui::TreePop();
    }
    ImGui::End();
}
