//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_BOXCOLLIDER_H
#define ZTGK_BOXCOLLIDER_H
#include "ECS/Raycasting/Collider.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Render/Primitives/Primitives.h"

class BoxCollider : public Collider
{
public:
    glm::vec3 center{};
    glm::vec3 size{};

    void showImGuiDetails(Camera* camera) override;
    void drawWire(Shader *shader, Primitives *primitives) override;

    BoxCollider(Entity* entity, glm::vec3 size);

    void update();




};


#endif //ZTGK_BOXCOLLIDER_H
