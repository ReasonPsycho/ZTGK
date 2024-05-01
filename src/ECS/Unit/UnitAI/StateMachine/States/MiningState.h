//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_MININGSTATE_H
#define ZTGK_MININGSTATE_H
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "ECS/Grid/Grid.h"
#include "ECS/Unit/Mining/IMineable.h"
#include <unordered_set>

class MovementState;
class CombatState;
class IdleState;
class MiningState : public State{
public:
    MiningState(Grid* grid);
    State* RunCurrentState() override;
    bool isTargetInRange() override;
    MovementState* moveState;
    CombatState* combatState;
    IdleState* idleState;


    std::vector<IMineable> miningPath;
    std::vector<IMineable> findMiningPath();

    Vector2Int GetNearestFloorTile(Vector2Int target, Vector2Int origin);
    Vector2Int GetLowestFScore(unordered_set<Vector2Int> &openSet, unordered_map<Vector2Int, float> &fScore);

    std::vector<Vector2Int> ReconstructPath(unordered_map<Vector2Int, Vector2Int> &cameFrom, Vector2Int current);
    std::vector<Vector2Int> GetNeighbours(Vector2Int current, bool includeDiagonals = false);




private:
    void Mine();
};


#endif //ZTGK_MININGSTATE_H
