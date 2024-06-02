#include "ItemTypes.h"
#include "ECS/Utils/Util.h"
#include "ECS/Unit/Equipment/Item.h"
#include "ECS/Unit/Equipment/ConcreteItems/Hands.h"
#include "ECS/Unit/Equipment/ConcreteItems/Mop.h"
#include "ECS/Unit/Equipment/ConcreteItems/WaterGun.h"
#include "ECS/Unit/Equipment/ConcreteItems/TestBuffItem.h"
#include "ECS/Unit/Equipment/ConcreteItems/PraniumOre.h"

using namespace ztgk;
#define quote(x) #x

s_item_types::s_item_types() {
    hands = 0;
    mop = id<ID_POOL_ITEM_TYPE>();
    water_gun = id<ID_POOL_ITEM_TYPE>();
    test_buff_item = id<ID_POOL_ITEM_TYPE>();
    pranium_ore = id<ID_POOL_ITEM_TYPE>();

    map = {};
    map.emplace(hands, quote(hands));
    map.emplace(mop, quote(mop));
    map.emplace(water_gun, quote(water_gun));
    map.emplace(test_buff_item, quote(test_buff_item));
    map.emplace(pranium_ore, quote(pranium_ore));
}

unsigned s_item_types::id_of(Item *item) const {
    auto type = std::type_index(typeid(*item));

    if (type == std::type_index(typeid(Hands)))
        return hands;
    if (type == std::type_index(typeid(Mop)))
        return mop;
    if (type == std::type_index(typeid(WaterGun)))
        return water_gun;
    if (type == std::type_index(typeid(TestBuffItem)))
        return water_gun;
    if (type == std::type_index(typeid(PraniumOre)))
        return pranium_ore;
}

std::string s_item_types::types_string() const {
    std::string ret;
    for (auto [id, name] : map) {
        ret += name + " - " + std::to_string(id) + '\n';
    }
    return ret;
}
