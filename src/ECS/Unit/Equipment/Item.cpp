//
// Created by igork on 25.03.2024.
//

#include "Item.h"
#include "ECS/Utils/Util.h"

const s_item_types Item::item_types{};

Item::Item(std::string name, std::string desctiption, bool offensive, ItemStats stats, bool takesTwoSlots)
    : uniqueID(ztgk::id<ztgk::ID_POOL_ITEM>()), name(name), description(desctiption), offensive(offensive), stats(stats), takesTwoSlots(takesTwoSlots) {
}
