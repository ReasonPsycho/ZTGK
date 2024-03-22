//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_ASTARPATHFINDING_H
#define ZTGK_ASTARPATHFINDING_H

#include <vector>
#include "VectorUtils.h"
#include "ECS/Grid/Grid.h"
#include <unordered_set>

template<> struct hash<Vector2Int>{
    std::size_t operator()(const Vector2Int& k) const
    {
        using std::size_t;
        using std::hash;

        return ((hash<int>()(k.x)
                 ^ (hash<int>()(k.z) << 1)) >> 1);
    }

};


class AstarPathfinding {
public:
    std::vector<Vector2Int> path;


    AstarPathfinding() = default;
    explicit AstarPathfinding(Grid* grid);


    ~AstarPathfinding() = default;

    //VIP function
    void FindPath(Vector2Int start, Vector2Int target);

private:
    Grid* grid;

    //Helper functions
    Vector2Int GetLowestFScore(std::unordered_set<Vector2Int>& openSet, std::unordered_map<Vector2Int, float>& fScore);
    std::vector<Vector2Int> ReconstructPath(std::unordered_map<Vector2Int, Vector2Int>& cameFrom, Vector2Int current);
    std::vector<Vector2Int> GetNeighbours(Vector2Int current, bool simple = false);
};


#endif //ZTGK_ASTARPATHFINDING_H
