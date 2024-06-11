//
// Created by cheily on 13.05.2024.
//

#pragma once


#include "ECS/Component.h"
class Item;

class PickupubleItem : public Component {
public:
    explicit PickupubleItem(Item *item);

    Item * item;
    bool isPickedUp = false;

protected:
    void showImGuiDetailsImpl(Camera *camera) override;
};
