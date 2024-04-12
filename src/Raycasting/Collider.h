//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_COLLIDER_H
#define ZTGK_COLLIDER_H
#include "../ECS/Component.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/Primitives/Primitives.h"

class Ray;

enum ColliderType{
    BOX,
    SPHERE
};
//TODO: Add more collider types
//TODO: Update collider position based on the entity position (?)

class Collider : public Component{
public:
    Collider() : Component() { this -> name = "Collider"; }
    virtual ~Collider() = default;
    ColliderType type;
    virtual void drawWire(Shader *shader, Primitives *primitives) = 0;
    void showImGuiDetails(Camera *camera) override;

};


#endif //ZTGK_COLLIDER_H
