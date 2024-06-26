//
// Created by redkc on 26/06/2024.
//

#include "ECS/Entity.h"
#include "LightMover.h"

LightMover::LightMover(glm::vec3 centerPosition):centerPosition(centerPosition) {
    name = "LightMover";
    startPosition = glm::vec3( centerPosition.x + RNG::RandomFloat(-4,4), centerPosition.y + RNG::RandomFloat(-0.5,0.5), centerPosition.z + RNG::RandomFloat(-4,4));
    endPosition = glm::vec3( centerPosition.x + RNG::RandomFloat(-4,4), centerPosition.y + RNG::RandomFloat(-0.5,0.5), centerPosition.z + RNG::RandomFloat(-4,4));
    speed = RNG::RandomFloat(0.1,0.2);
    t = 0;
}

void LightMover::showImGuiDetailsImpl(Camera *camera) {
    Component::showImGuiDetailsImpl(camera);
}

glm::vec3 lerp(const glm::vec3& a, const glm::vec3& b, float t) {
    return (1.0f - t) * a + t * b;
}

void LightMover::UpdateImpl() {
    if (t >= 1){
        startPosition = endPosition;
        endPosition = glm::vec3( centerPosition.x + RNG::RandomFloat(-4,4), centerPosition.y + RNG::RandomFloat(-0.5,0.5), centerPosition.z + RNG::RandomFloat(-4,4));
        speed = RNG::RandomFloat(0.1,0.2);
        t = 0;
    }
    t += Time::Instance().DeltaTime() * speed;
    getEntity()->transform.setLocalPosition(lerp(startPosition,endPosition,t));
    getEntity()->getComponent<PointLight>()->setIsDirty(true);
}
