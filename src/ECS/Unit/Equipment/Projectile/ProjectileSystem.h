//
// Created by igork on 16.06.2024.
//

#ifndef ZTGK_PROJECTILESYSTEM_H
#define ZTGK_PROJECTILESYSTEM_H
#include "ECS/System.h"
#include "Projectile.h"

class ProjectileSystem : public System{
public:
    ProjectileSystem();
    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override;
    int getNumComponentTypes() override {return 1;};

    void UpdateImpl() override;
    void registerComponents() override{};
    void showImGuiDetailsImpl(Camera *camera) override;

    std::vector<Projectile*> projectiles;

private:
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(Projectile))
    };

};


#endif //ZTGK_PROJECTILESYSTEM_H
