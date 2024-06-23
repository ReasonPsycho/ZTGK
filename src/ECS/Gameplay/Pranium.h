//
// Created by igork on 23.05.2024.
//

#ifndef ZTGK_PRANIUM_H
#define ZTGK_PRANIUM_H

#include "ECS/Unit/Mining/IMineable.h"


class Pranium : public IMineable{
public:
    Pranium(float timeToMine, Vector2Int gridPosition, Grid* grid);
    ~Pranium() override;

    void onMine(Unit * unit) override;
    void onMined(Unit * unit) override;

    void generatePranium(Model * model);

    void UpdateImpl() override;

private:
    void tryToSendEmote();
    float bubbleCooldown = 0;
};


#endif //ZTGK_PRANIUM_H
