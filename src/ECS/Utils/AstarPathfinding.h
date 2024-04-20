//
// Created by igork on 22.03.2024.
//

#ifndef ZTGK_ASTARPATHFINDING_H
#define ZTGK_ASTARPATHFINDING_H

#include <vector>
#include "VectorUtils.h"
#include "ECS/Grid/Grid.h"
#include <unordered_set>

using namespace std;



class AstarPathfinding {
public:
    std::vector<Vector2Int> path;


    // Constructors
    AstarPathfinding() = default;
    explicit AstarPathfinding(Grid* grid);


    // Destructor
    ~AstarPathfinding() = default;

    // Most important method
    void FindPath(Vector2Int start, Vector2Int target);

private:
    Grid* grid;

    //Helper functions
    Vector2Int GetLowestFScore(std::unordered_set<Vector2Int>& openSet, std::unordered_map<Vector2Int, float>& fScore);
    std::vector<Vector2Int> ReconstructPath(std::unordered_map<Vector2Int, Vector2Int>& cameFrom, Vector2Int current);
    std::vector<Vector2Int> GetNeighbours(Vector2Int current, bool simple = false);
    Vector2Int GetNearestVacantTile(Vector2Int target, Vector2Int origin);

};


//Hash function for Vector2Int
template<> struct std::hash<Vector2Int>{
    std::size_t operator()(const Vector2Int& k) const
    {
        using std::size_t;
        using std::hash;

        return ((hash<int>()(k.x)
                 ^ (hash<int>()(k.z) << 1)) >> 1);
    }

};

#endif //ZTGK_ASTARPATHFINDING_H
