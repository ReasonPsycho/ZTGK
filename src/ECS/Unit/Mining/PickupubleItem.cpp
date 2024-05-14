//
// Created by cheily on 13.05.2024.
//

#include "PickupubleItem.h"
#include "ECS/Unit/Equipment/Item.h"

void PickupubleItem::showImGuiDetailsImpl(Camera *camera) {
    item->imgui_preview();
    Component::showImGuiDetailsImpl(camera);
}

PickupubleItem::PickupubleItem(Item *item) : item(item) {
    name = "Pickupuble item - " + item->name + " id " + std::to_string(item->uniqueID);
}

