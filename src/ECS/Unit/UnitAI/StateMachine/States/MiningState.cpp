//
// Created by igork on 22.03.2024.
//

#include "MiningState.h"

#include "ECS/Unit/Unit.h"
#include "ECS/Unit/UnitAI/StateMachine/State.h"
#include "MovementState.h"
#include "CombatState.h"
#include "IdleState.h"


State *MiningState::RunCurrentState() {
    isTargetInRange();

    //from Mining to Idle
    if(!unit->hasMovementTarget && !unit->hasCombatTarget && !unit->hasMiningTarget){
        idleState = new IdleState(grid);
        idleState->unit = unit;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.5, 5.0);
        double random_number = dis(gen);

        idleState->randomTime = random_number;

        return idleState;
    }

    //from Mining to Movement
    if(unit->hasMovementTarget){
        moveState = new MovementState(grid);
        moveState->unit = unit;

        return moveState;
    }

    //from Mining to Combat
    if(unit->hasCombatTarget){
        combatState = new CombatState(grid);
        combatState->unit = unit;

        if(combatState->isTargetInRange())
            return combatState;
        else
        {
            unit->hasMovementTarget = true;
            unit->movementTarget = unit->combatTarget->gridPosition;
            moveState = new MovementState(grid);
            moveState->unit = unit;
            return moveState;
        }
    }
    if(isTargetInRange())
        Mine();
    else{
        moveState = new MovementState(grid);
        moveState->unit = unit;
        unit->hasMovementTarget = true;
        unit->movementTarget = unit->pathfinding.GetNearestVacantTile(unit->currentMiningTarget->gridPosition, unit->gridPosition);
        return moveState;
    }
    return this;
}

bool MiningState::isTargetInRange() {
    IMineable* current = unit->currentMiningTarget;
    if(current == nullptr){
        spdlog::error("IN MiningState::isTargetInRange(): no current mining target");
        unit->hasMiningTarget = false;
        unit->isTargetInRange = false;
        return false;
    }

     if(VectorUtils::Distance(VectorUtils::GlmVec3ToVector3(unit->worldPosition), VectorUtils::GlmVec3ToVector3(grid->GridToWorldPosition(current->gridPosition))) <=/*todo this is the old range value ??*/ 3){
         unit->isTargetInRange = true;
         return true;
     }
     return false;
}

void MiningState::Mine() {
    std::vector<IMineable*> miningTargets = unit->miningTargets;

    if(miningTargets.empty()){
        spdlog::error("In MiningState::Mine(): Mining targets are empty");
        unit->hasMiningTarget = false;
        return;
    }


    if(unit->currentMiningTarget->getTimeToMineRemaining() <= 0 && miningTargets.size() == 1){
        unit->hasMiningTarget = false;
        miningTargets.clear();
        unit->miningTargets.clear();
        return;
    }

    if(isTargetInRange()){
        if(unit->currentMiningTarget->getTimeToMineRemaining() == unit->currentMiningTarget->timeToMine){
            ztgk::game::audioManager->playRandomSoundFromGroup("mining");
        }
        unit->currentMiningTarget->Mine(unit);

        if(unit->currentMiningTarget->getTimeToMineRemaining() <= 0){
            miningTargets.erase(miningTargets.begin());
            if(miningTargets.empty()){
                unit->hasMiningTarget = false;
                unit->currentMiningTarget = nullptr;
                return;
            }
            unit->sortMiningTargetsByDistance();
            unit->currentMiningTarget = miningTargets.front();
        }
    }
//    else{
//        auto miningPat= findMiningPath();
//        if(miningPat.size() == 0){
//            spdlog::error("In MiningState::Mine(): Mining path is empty");
//            return;
//        }
//        for(auto &tile : findMiningPath()) {
//            tilesToMine.push_back(tile);
//            unit->miningPath.push_back(tile);
//        }
//
//
//    }
}

std::vector<IMineable> MiningState::findMiningPath() {
    if(!unit->hasMiningTarget) return {}; //empty vector
    std::vector<IMineable> path = {};
    IMineable* currentUnitTarget = unit->currentMiningTarget;
    if(currentUnitTarget == nullptr){
        spdlog::error("In MiningState::findMiningPath(): Mining target is nullptr");
        return {};
    }

    //A* pathfinding of mining path through walls to the target

    std::unordered_set<Vector2Int> openSet;
    std::unordered_set<Vector2Int> closedSet;
    std::unordered_map<Vector2Int, Vector2Int> cameFrom;
    std::unordered_map<Vector2Int, float> gScore;
    std::unordered_map<Vector2Int, float> fScore;

    Vector2Int start = currentUnitTarget->gridPosition;

    Vector2Int target = GetNearestFloorTile(unit->gridPosition, start);
    std::vector<Vector2Int> neighbours = GetNeighbours(target, true);
    for(auto &neigh : neighbours){
        if(grid->getTileAt(neigh)->state != FLOOR){
            target = neigh;
            break;
        }
    }


    openSet.insert(start);
    gScore[start] = 0;
    fScore[start] = VectorUtils::Distance(start, target);

    while(!openSet.empty()){
        Vector2Int current = GetLowestFScore(openSet, fScore);

        if(current == target){
            std::vector<IMineable> miningP = {};
            std::vector<Vector2Int> path = ReconstructPath(cameFrom, current);
            for(auto &tile : path){
                IMineable* mineable = grid->getTileAt(tile)->getEntity()->getComponent<IMineable>();
                if(mineable != nullptr){
                    miningP.push_back(*mineable);
                }
                else{
                    spdlog::error("In MiningState::findMiningPath(): Mineable is nullptr");
                }
            }
            return miningP;
        }

        openSet.erase(current);
        closedSet.insert(current);

        for(auto neigh: GetNeighbours(current, true)){
            if(closedSet.contains(neigh) || grid->getTileAt(neigh)->state == FLOOR){
                continue;
            }

            float tentativeGScore = gScore[current] + VectorUtils::Distance(current, neigh);
            if(!openSet.contains(neigh) || tentativeGScore < gScore[neigh]){
                cameFrom[neigh] = current;
                gScore[neigh] = tentativeGScore;
                fScore[neigh] = gScore[neigh] + VectorUtils::Distance(neigh, target);
                if(!openSet.contains(neigh)){
                    openSet.insert(neigh);
                }
            }
        }


    }
    return {};

}
std::vector<Vector2Int>
MiningState::ReconstructPath(unordered_map<Vector2Int, Vector2Int> &cameFrom, Vector2Int current) {
    std::vector<Vector2Int> totalPath;
    totalPath.push_back(current);

    while(cameFrom.find(current) != cameFrom.end()){
        current = cameFrom[current];
        totalPath.push_back(current);
    }

    //std::reverse(totalPath.begin(), totalPath.end());

    return totalPath;
}


Vector2Int
MiningState::GetLowestFScore(unordered_set<Vector2Int> &openSet, unordered_map<Vector2Int, float> &fScore) {
    Vector2Int lowest = Vector2Int(0,0);
    float lowestFScore = std::numeric_limits<float>::max();

    for(auto &node : openSet){
        if(fScore[node] < lowestFScore){
            lowestFScore = fScore[node];
            lowest = node;
        }
    }
    return lowest;
}

Vector2Int MiningState::GetNearestFloorTile(Vector2Int target, Vector2Int origin) {
    Vector2Int directions[] = {Vector2Int(1, 0), Vector2Int(-1, 0), Vector2Int(0, 1), Vector2Int(0, -1)};
    std::vector<Vector2Int> list;
    list.push_back(target);
    std::unordered_set<Vector2Int> visited;
    visited.insert(target);

    while (list.size() > 0) {
        Vector2Int current = list[0];
        list.erase(list.begin());
        if (grid->getTileAt(current)->state == FLOOR || current == origin) {
            return current;
        }

        for (Vector2Int dir: directions) {
            Vector2Int next = current + dir;
            if (grid->getTileAt(next) != nullptr && !visited.contains(next)) {
                list.push_back(next);
                visited.insert(next);
            }
        }
        std::sort(list.begin(), list.end(), [origin](Vector2Int a, Vector2Int b) {
            return VectorUtils::Distance(a, origin) < VectorUtils::Distance(b, origin);
        });
    }
    return target;

}
MiningState::MiningState(Grid *grid) {
    this->grid = grid;
    this->name = "Mining";
}

std::vector<Vector2Int> MiningState::GetNeighbours(Vector2Int current, bool includeDiagonals) {
    std::vector<Vector2Int> neighbours;

    Vector2Int right = current + Vector2Int(1, 0);
    Vector2Int left = current + Vector2Int(-1, 0);
    Vector2Int up = current + Vector2Int(0, 1);
    Vector2Int down = current + Vector2Int(0, -1);


    //right
    if(right.x >= 0 && right.z >=0 &&grid->getTileAt(right) != nullptr && grid->getTileAt(right)->state !=FLOOR){
        neighbours.push_back(right);
    }

    //left
    if(left.x >= 0 && left.z >=0 &&  grid->getTileAt(left) != nullptr && grid->getTileAt(left)->state !=FLOOR){
        neighbours.push_back(left);
    }

    //up
    if(up.x >= 0 && up.z >=0 &&grid->getTileAt(up) != nullptr && grid->getTileAt(up)->state !=FLOOR){
        neighbours.push_back(up);
    }

    //down
    if(down.x >= 0 && down.z >=0 &&grid->getTileAt(down) != nullptr && grid->getTileAt(down)->state !=FLOOR){
        neighbours.push_back(down);
    }

    if(!includeDiagonals)   return neighbours;

    //UpRight
    if((up.x >= 0 && up.z >=0 &&right.x >= 0 && right.z >=0 &&grid->getTileAt(right) != nullptr)){
        Vector2Int upRight = current + Vector2Int(1, 1);
        if(upRight.x >= 0 && upRight.z >=0 && grid->getTileAt(upRight) != nullptr && grid->getTileAt(upRight)->state !=FLOOR){
            neighbours.push_back(upRight);
        }
    }

    //DownRight
    if((down.x >= 0 && down.z >=0 &&right.x >= 0 && right.z >=0 &&grid->getTileAt(right) != nullptr)){
        Vector2Int downRight = current + Vector2Int(1, -1);
        if(downRight.x >= 0 && downRight.z >=0 &&grid->getTileAt(downRight) != nullptr && grid->getTileAt(downRight)->state !=FLOOR){
            neighbours.push_back(downRight);
        }
    }

    //UpLeft
    if((up.x >= 0 && up.z >=0 &&left.x >= 0 && left.z >=0 && grid->getTileAt(left) != nullptr )){
        Vector2Int upLeft = current + Vector2Int(-1, 1);
        if(upLeft.x >= 0 && upLeft.z >=0 &&grid->getTileAt(upLeft) != nullptr && grid->getTileAt(upLeft)->state !=FLOOR){
            neighbours.push_back(upLeft);
        }
    }

    //DownLeft
    if((down.x >= 0 && down.z >=0 &&left.x >= 0 && left.z >=0 && grid->getTileAt(left) != nullptr )){
        Vector2Int downLeft = current + Vector2Int(-1, -1);
        if(downLeft.x >= 0 && downLeft.z >=0 &&grid->getTileAt(downLeft) != nullptr && grid->getTileAt(downLeft)->state !=FLOOR){
            neighbours.push_back(downLeft);
        }
    }

    return neighbours;

}
