//
// Created by cheily on 13.05.2024.
//

#pragma once


#include "ECS/Component.h"
#include "ECS/Utils/VectorUtils.h"

class Item;

class PickupubleItem : public Component {
public:
    explicit PickupubleItem(Item *item, Vector2Int gridPosition);
    Vector2Int gridPosition;

    Item * item;

protected:
    void showImGuiDetailsImpl(Camera *camera) override;
};
