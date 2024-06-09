//
// Created by cheily on 13.05.2024.
//

#pragma once


#include "IMineable.h"

class MineableChest : public IMineable {
public:
    unsigned item_type_id = 0;

    MineableChest(const Vector2Int &gridPosition, Grid *grid, unsigned int itemTypeId);
    ~MineableChest() override;

    void onMined(Unit *unit) override;

    void UpdateImpl() override;

    void showImGuiDetailsImpl(Camera *camera) override;
};
