//
// Created by cheily on 13.05.2024.
//

#pragma once


#include "IMineable.h"

class MineableChest : public IMineable {
public:
    unsigned item_type_id = 0;

    MineableChest(const Vector2Int &gridPosition, Grid *grid, unsigned int itemTypeId)
    : IMineable(2, gridPosition, grid), item_type_id(itemTypeId) {}

    void onMined(Unit *unit) override;

    void showImGuiDetailsImpl(Camera *camera) override;
};
