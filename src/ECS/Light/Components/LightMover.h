//
// Created by redkc on 26/06/2024.
//

#ifndef SCRUB_SQUAD_LIGHTMOVER_H
#define SCRUB_SQUAD_LIGHTMOVER_H


#include "ECS/Component.h"
#include "ECS/Utils/RNG.h"
#include "ECS/Utils/Time.h"

class LightMover : public Component{
public:
    LightMover(glm::vec3 centerPosition);

    void showImGuiDetailsImpl(Camera *camera) override;
    void UpdateImpl() override;

private:
    glm::vec3 endPosition;
    glm::vec3 centerPosition;
    glm::vec3 startPosition;

    float speed;
    float t;
};


#endif //SCRUB_SQUAD_LIGHTMOVER_H
