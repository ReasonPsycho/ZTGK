//
// Created by igork on 16.06.2024.
//
#include "Projectile.h"
#include "ECS/Entity.h"
#include "ECS/Utils/Time.h"
#include "ECS/Unit/UnitAI/StateMachine/States/CombatState.h"
#include "ECS/Unit/Equipment/Projectile/ProjectileSystem.h"

Projectile::Projectile(glm::vec3 startPos, glm::vec3 targetPos,Unit* un, Unit* targ, float dmg) {
    name= "Projectile";
    this->startPosition = startPos;
    this->targetPosition = targetPos;
    curvePoints = generateCurvePoints(10);
    speed = 5 ;
    worldPosition = startPosition;
    this->target = targ;
    this->unit = un;
    this->damage = dmg;
    ztgk::game::scene->systemManager.getSystem<ProjectileSystem>()->addComponent(this);

}

std::vector<glm::vec3> Projectile::generateCurvePoints(int steps) {
    std::vector<glm::vec3> points;
    for (int i = 0; i < steps; i++) {
        float t = (float)i / (float)steps;
        glm::vec3 point = (1 - t) * startPosition + t * targetPosition;
        point.y += sin(t * 3.14f);
        points.push_back(point);
    }
    return points;

}

void Projectile::UpdateImpl() {
    // Define the margin of error for checking the target position
    float epsilon = 0.5f;
    if(target == nullptr || unit == nullptr){
        ztgk::game::scene->systemManager.getSystem<ProjectileSystem>()->removeComponent(this);
        getEntity()->Destroy();
        return;
    }

    // Check if the target position has changed and update the curve points
    if (glm::length(targetPosition - target->worldPosition) > epsilon) {
        startPosition = worldPosition;
        targetPosition = target->worldPosition;
        curvePoints = generateCurvePoints(10);
    }

    // Check if the projectile has reached the target using the margin of error
    if (glm::length(worldPosition - targetPosition) < epsilon || curvePoints.empty()) {
        // Apply damage and remove the projectile
        CombatState::applyDamage(unit, target, damage);
        ztgk::game::scene->systemManager.getSystem<ProjectileSystem>()->removeComponent(this);
        getEntity()->Destroy();
        return;
    }

    // Check if the list of curve points is empty
    if (curvePoints.empty()) {
        spdlog::error("curvePoints vector is empty");
        return;
    }

    // Calculate the direction and displacement of the projectile
    glm::vec3 direction = curvePoints[0] - worldPosition;
    float distance = glm::length(direction);
    double deltaTime = Time::Instance().DeltaTime();

    if (distance < speed * deltaTime) {
        // Move directly to the next curve point and remove it from the list
        worldPosition = curvePoints[0];
        curvePoints.erase(curvePoints.begin());
    } else {
        // Move towards the next curve point
        worldPosition += glm::normalize(direction) * speed * (float)deltaTime;
    }
    // Update the entity's position in the world
    getEntity()->transform.setLocalPosition(worldPosition);
}

