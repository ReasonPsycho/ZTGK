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

struct BoxColliderData{
    glm::mat4x4 matrix;
    glm::vec4 color;

    BoxColliderData(const glm::mat4x4 &matrixInput, glm::vec4 color) : matrix(matrixInput),color(color) {}

};

class BoxCollider : public Collider
{
public:

    glm::vec3 center{};
    glm::vec3 size{};
    BoxColliderData boxColliderData = BoxColliderData(glm::mat4x4(1.0f), glm::vec4(1));
    // Constructors
    BoxCollider(Entity* entity, glm::vec3 size, CollisionSystem* collisionSystem);

    // Debug methods

    // ImGui methods
    void showImGuiDetailsImpl(Camera* camera) override;

    // Other methods
    void update();

    bool intersects(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);

};


#endif //ZTGK_BOXCOLLIDER_H
