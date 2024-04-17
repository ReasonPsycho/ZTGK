//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_BOXCOLLIDER_H
#define ZTGK_BOXCOLLIDER_H
#include "ECS/Raycasting/Collider.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Render/Primitives/Primitives.h"

class CollisionSystem;

class BoxCollider : public Collider
{
public:

    glm::vec3 center{};
    glm::vec3 size{};

    // Constructors
    BoxCollider(Entity* entity, glm::vec3 size, CollisionSystem* collisionSystem);

    // Debug methods
    void drawWire(Shader *shader, Primitives *primitives) override;

    // ImGui methods
    void showImGuiDetails(Camera* camera) override;

    // Other methods
    void update();

};


#endif //ZTGK_BOXCOLLIDER_H
