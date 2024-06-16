//
// Created by igork on 16.06.2024.
//

#include "ProjectileSystem.h"

ProjectileSystem::ProjectileSystem() {
    name = "ProjectileSystem";

}

void ProjectileSystem::addComponent(void *component) {
    projectiles.push_back((Projectile*)component);
}

void ProjectileSystem::removeComponent(void *component) {
    projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), component), projectiles.end());
}

const std::type_index *ProjectileSystem::getComponentTypes() {
    return componentTypes.data();
}

void ProjectileSystem::UpdateImpl() {

    for (auto &projectile : projectiles) {
        if(find(projectiles.begin(), projectiles.end(), projectile) != projectiles.end())
            projectile->UpdateImpl();
    }
}

void ProjectileSystem::showImGuiDetailsImpl(Camera *camera) {
    for (auto &projectile : projectiles) {
        projectile->showImGuiDetails(camera);
    }
}


