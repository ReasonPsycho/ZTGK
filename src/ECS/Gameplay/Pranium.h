//
// Created by igork on 23.05.2024.
//

#ifndef ZTGK_PRANIUM_H
#define ZTGK_PRANIUM_H

#include "ECS/Unit/Mining/IMineable.h"


class Pranium : public IMineable{
public:
    Pranium(float timeToMine, Vector2Int gridPosition, Grid* grid);
    ~Pranium() override = default;

    void onMine(Unit * unit) override;
    void onMined(Unit * unit) override;


};


#endif //ZTGK_PRANIUM_H
