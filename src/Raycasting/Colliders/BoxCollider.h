//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_BOXCOLLIDER_H
#define ZTGK_BOXCOLLIDER_H
#include "../Collider.h"

class BoxCollider : public Collider
{
public:
    glm::vec3 center{};
    glm::vec3 size{};

    BoxCollider(const glm::vec3& center, const glm::vec3& size);

    void showImGuiDetails(Camera* camera) override;

    BoxCollider(Entity* entity, glm::vec3 size);
};


#endif //ZTGK_BOXCOLLIDER_H
