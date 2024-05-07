#include "ItemTypes.h"
#include "ECS/Utils/Util.h"
#include "ECS/Unit/Equipment/Item.h"
#include "ECS/Unit/Equipment/ConcreteItems/Hands.h"
#include "ECS/Unit/Equipment/ConcreteItems/Mop.h"
#include "ECS/Unit/Equipment/ConcreteItems/WaterGun.h"

using namespace ztgk;

s_item_types::s_item_types() {
    hands = 0;
    mop = id<ID_POOL_ITEM_TYPE>();
    water_gun = id<ID_POOL_ITEM_TYPE>();
}

unsigned s_item_types::id_of(Item *item) const {
    auto type = std::type_index(typeid(*item));

    if (type == std::type_index(typeid(Hands)))
        return hands;
    if (type == std::type_index(typeid(Mop)))
        return mop;
    if (type == std::type_index(typeid(WaterGun)))
        return water_gun;
}
