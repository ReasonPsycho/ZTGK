//
// Created by igork on 16.06.2024.
//

#ifndef ZTGK_PROJECTILE_H
#define ZTGK_PROJECTILE_H
#include "ECS/Component.h"
#include "ECS/Unit/Unit.h"

class Projectile : public Component{
public:
    Projectile(glm::vec3 startPos, glm::vec3 targetPos,Unit* un, Unit* targ, Item * source, float dmg);
    ~Projectile() = default;
    void UpdateImpl() override;
    glm::vec3 worldPosition{};
    Unit* unit;
    Item * sourceItem;
    Unit* target;
    float damage;

    // return damaged units!
    std::function<std::vector<Unit *>()> onHit;

private:
    glm::vec3 startPosition{};
    glm::vec3 targetPosition{};
    std::vector<glm::vec3> curvePoints;
    std::vector<glm::vec3> generateCurvePoints(int steps);
    float speed;

};
#endif //ZTGK_PROJECTILE_H
