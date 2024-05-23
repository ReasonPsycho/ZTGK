//
// Created by igork on 23.05.2024.
//

#ifndef ZTGK_WASHINGMACHINETILE_H
#define ZTGK_WASHINGMACHINETILE_H

#include "ECS/Component.h"
#include "ECS/Utils/VectorUtils.h"
#include "ECS/Grid/Grid.h"

class WashingMachine;


class WashingMachineTile : public Component{

    WashingMachineTile(WashingMachine* washingMachine, Vector2Int gridPosition, Grid* grid);
    ~WashingMachineTile() override = default;

    WashingMachine* washingMachine;
    Vector2Int gridPosition;
    Grid* grid;

};


#endif //ZTGK_WASHINGMACHINETILE_H
