//
// Created by igork on 03.04.2024.
//

#ifndef ZTGK_COLLIDER_H
#define ZTGK_COLLIDER_H
#include "ECS/Component.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Render/Primitives/Primitives.h"

class Ray;

enum ColliderType{
    BOX,
    SPHERE
};

class Collider : public Component{
public:
    ColliderType type;

    // Constructors
    Collider() : Component() { this -> name = "Collider"; }

    // Destructor
    virtual ~Collider() = default;

    // ImGui methods
    void showImGuiDetails(Camera *camera) override;

};


#endif //ZTGK_COLLIDER_H
