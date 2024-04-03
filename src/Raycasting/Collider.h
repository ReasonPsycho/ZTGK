//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_COLLIDER_H
#define ZTGK_COLLIDER_H
#include "../ECS/Component.h"
class Ray;

enum ColliderType{
    BOX,
    SPHERE
};
//TODO: Add more collider types
//TODO: Update collider position based on the entity position (?)

class Collider : public Component{
public:
    Collider() =default;
    virtual ~Collider() = default;
    ColliderType type;
};


#endif //ZTGK_COLLIDER_H
