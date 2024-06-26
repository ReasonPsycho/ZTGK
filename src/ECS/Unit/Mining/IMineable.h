//
// Created by igork on 24.03.2024.
//

#ifndef IMINEABLE_H
#define IMINEABLE_H


#include "ECS/Component.h"
#include "ECS/Utils/VectorUtils.h"
#include "ECS/Grid/Grid.h"

class IMineable : public Component{
public:
    IMineable(IMineable *pMineable);

    float timeToMine;
    Vector2Int gridPosition;
    Grid* grid;
    explicit  IMineable(float timeToMine, Vector2Int gridPosition, Grid* grid);
    ~IMineable();
    void onMine(Unit * unit);
    virtual void onMined(Unit * unit) { /**/ };
    void Mine(Unit * unit);

    void UpdateImpl() override;

    void showImGuiDetailsImpl(Camera *camera) override;

    float getTimeToMineRemaining() const {
        return timeToMineRemaining;
    }
    bool isMined = false;

protected:
    float timeToMineRemaining;
    float particle_cooldown = 0;
};



#endif //IMINEABLE_H
