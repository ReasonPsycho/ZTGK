//
// Created by igork on 22.03.2024.
//

#include "AstarPathfinding.h"
#include <tracy/Tracy.hpp >
#include <GLFW/glfw3.h>
#include "ECS/Unit/Unit.h"
/**
 * @brief AstarPathfinding constructor
 * @param grid
 */
AstarPathfinding::AstarPathfinding(Grid *grid, Unit* unit) {
    this->grid = grid;
    this->unit = unit;
}

/**
 * @brief Uses A* algorithm to find the shortest path
 * from start tile to target tile. \n
 * Stores the path in the \b path member variable
 * @param start
 * @param target
 */
std::vector<Vector2Int> AstarPathfinding::FindPath(Vector2Int start, Vector2Int target, std::vector<Vector2Int> forbiddenTiles, bool debug) {
    ZoneScopedN("Astar::FindPath");
    double start_time = glfwGetTime();

    if (grid->getTileAt(target) == nullptr){
        spdlog::error("PATHFINDING: Target tile is nullptr");
    }
    if (grid->getTileAt(start) == nullptr){
        spdlog::error("PATHFINDING: Start tile is nullptr");
    }

    if(grid->getTileAt(target)->vacant()){
        target = GetNearestVacantTile(target, start);
    }

    std::unordered_set<Vector2Int> openSet;
    std::unordered_set<Vector2Int> closedSet;
    std::unordered_map<Vector2Int, Vector2Int> cameFrom;
    std::unordered_map<Vector2Int, float> gScore;
    std::unordered_map<Vector2Int, float> fScore;

    openSet.insert(start);
    gScore[start] = 0;
    fScore[start] = VectorUtils::Distance(start, target);

    while(!openSet.empty()){

        Vector2Int current = GetLowestFScore(openSet, fScore);
        if (current == target){
            path = ReconstructPath(cameFrom, current);
            return path;
        }

        openSet.erase(current);
        closedSet.insert(current);

        for(auto neigh : GetNeighbours(current)){
            // Skip if the neighbor is a forbidden tile
            if(std::find(forbiddenTiles.begin(), forbiddenTiles.end(), neigh) != forbiddenTiles.end()){
                continue;
            }

            if(closedSet.contains(neigh) || !grid->getTileAt(neigh)->vacant()){
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
    if(debug)spdlog::error("PATHFINDING: No path found for unit {}", unit->name);
    path.clear();
    return path;
}
//________________________________________________HELPER FUNCTIONS_____________________________________________________
/**
 * @brief Returns the node with the lowest fScore
 * @param openSet
 * @param fScore
 * @return Vector2Int
 */
Vector2Int
AstarPathfinding::GetLowestFScore(unordered_set<Vector2Int> &openSet, unordered_map<Vector2Int, float> &fScore) {
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

/**
 * @brief Reconstructs the path from the cameFrom map and returns it
 * @param cameFrom
 * @param current
 * @return std::vector<Vector2Int>
 */
std::vector<Vector2Int>
AstarPathfinding::ReconstructPath(unordered_map<Vector2Int, Vector2Int> &cameFrom, Vector2Int current) {
    std::vector<Vector2Int> totalPath;
    totalPath.push_back(current);

    while(cameFrom.find(current) != cameFrom.end()){
        current = cameFrom[current];
        totalPath.push_back(current);
    }

    std::reverse(totalPath.begin(), totalPath.end());

    return totalPath;
}


/**
 * @brief Returns the neighbours of the current node \n
 *
 * @param current - the current node
 * @param simple - default \b false -> searches for diagonal neighbours too \n
 *                      \b true -> only searches for up, down, left, right neighbours
 *
 * @return std::vector<Vector2Int>
 */
std::vector<Vector2Int> AstarPathfinding::GetNeighbours(Vector2Int current, bool simple) {
    std::vector<Vector2Int> neighbours;

    Vector2Int right = current + Vector2Int(1, 0);
    Vector2Int left = current + Vector2Int(-1, 0);
    Vector2Int up = current + Vector2Int(0, 1);
    Vector2Int down = current + Vector2Int(0, -1);


    //right
    if(right.x >= 0 && right.z >=0 &&grid->getTileAt(right) != nullptr && grid->getTileAt(right)->vacant()){
        neighbours.push_back(right);
    }

    //left
    if(left.x >= 0 && left.z >=0 &&  grid->getTileAt(left) != nullptr && grid->getTileAt(left)->vacant()){
        neighbours.push_back(left);
    }

    //up
    if(up.x >= 0 && up.z >=0 &&grid->getTileAt(up) != nullptr && grid->getTileAt(up)->vacant()){
        neighbours.push_back(up);
    }

    //down
    if(down.x >= 0 && down.z >=0 &&grid->getTileAt(down) != nullptr && grid->getTileAt(down)->vacant()){
        neighbours.push_back(down);
    }

    if(simple){
        return neighbours;
    }
    //UpRight
    if((up.x >= 0 && up.z >=0 &&right.x >= 0 && right.z >=0 &&grid->getTileAt(right) != nullptr && grid->getTileAt(right)->vacant()) && (grid->getTileAt(up) != nullptr && grid->getTileAt(up)->vacant())){
        Vector2Int upRight = current + Vector2Int(1, 1);
        if(upRight.x >= 0 && upRight.z >=0 && grid->getTileAt(upRight) != nullptr && grid->getTileAt(upRight)->vacant()){
            neighbours.push_back(upRight);
        }
    }

    //DownRight
    if((down.x >= 0 && down.z >=0 &&right.x >= 0 && right.z >=0 &&grid->getTileAt(right) != nullptr && grid->getTileAt(right)->vacant()) && (grid->getTileAt(down) != nullptr && grid->getTileAt(down)->vacant())){
        Vector2Int downRight = current + Vector2Int(1, -1);
        if(downRight.x >= 0 && downRight.z >=0 &&grid->getTileAt(downRight) != nullptr && grid->getTileAt(downRight)->vacant()){
            neighbours.push_back(downRight);
        }
    }

    //UpLeft
    if((up.x >= 0 && up.z >=0 &&left.x >= 0 && left.z >=0 && grid->getTileAt(left) != nullptr && grid->getTileAt(left)->vacant()) && (grid->getTileAt(up) != nullptr && grid->getTileAt(up)->vacant())){
        Vector2Int upLeft = current + Vector2Int(-1, 1);
        if(upLeft.x >= 0 && upLeft.z >=0 &&grid->getTileAt(upLeft) != nullptr && grid->getTileAt(upLeft)->vacant()){
            neighbours.push_back(upLeft);
        }
    }

    //DownLeft
    if((down.x >= 0 && down.z >=0 &&left.x >= 0 && left.z >=0 && grid->getTileAt(left) != nullptr && grid->getTileAt(left)->vacant()) && (grid->getTileAt(down) != nullptr && grid->getTileAt(down)->vacant())){
        Vector2Int downLeft = current + Vector2Int(-1, -1);
        if(downLeft.x >= 0 && downLeft.z >=0 &&grid->getTileAt(downLeft) != nullptr && grid->getTileAt(downLeft)->vacant()){
            neighbours.push_back(downLeft);
        }
    }

    return neighbours;
}

Vector2Int AstarPathfinding::GetNearestVacantTile(Vector2Int target, Vector2Int origin) {
    ZoneScopedN("GetNearestVacantTile");
    Vector2Int directions[] = {Vector2Int(1, 0), Vector2Int(-1, 0), Vector2Int(0, 1), Vector2Int(0, -1)};
    std::vector<Vector2Int> list;
    list.push_back(target);
    std::unordered_set<Vector2Int> visited;
    visited.insert(target);

    while(list.size() > 0){
        Vector2Int current = list[0];
        list.erase(list.begin());
        if(grid->getTileAt(current)->vacant() || current == origin){
            return current;
        }

        for(Vector2Int dir : directions){
            Vector2Int next = current + dir;
            if(grid->getTileAt(next)!= nullptr && !visited.contains(next)){
                list.push_back(next);
                visited.insert(next);
            }
        }
        std::sort(list.begin(), list.end(), [origin](Vector2Int a, Vector2Int b){
            return VectorUtils::Distance(a, origin) < VectorUtils::Distance(b, origin);
        });
    }
    return target;


}

Vector2Int AstarPathfinding::GetNearestVacantTileAround(Vector2Int origin, std::vector<Vector2Int> forbiddenTiles) {
    ZoneScopedN("GetNearestVacantTileAround");
    Vector2Int directions[] = {Vector2Int(1, 0), Vector2Int(-1, 0), Vector2Int(0, 1), Vector2Int(0, -1)};
    std::vector<Vector2Int> list;
    list.push_back(origin);
    std::unordered_set<Vector2Int> visited;
    visited.insert(origin);

    while(list.size() > 0){
        Vector2Int current = list[0];
        list.erase(list.begin());
        if(grid->getTileAt(current)->vacant() && std::find(forbiddenTiles.begin(), forbiddenTiles.end(), current) == forbiddenTiles.end()){
            return current;
        }

        for(Vector2Int dir : directions){
            Vector2Int next = current + dir;
            if(grid->getTileAt(next)!= nullptr && !visited.contains(next)){
                list.push_back(next);
                visited.insert(next);
            }
        }
    }
    return origin;
}

std::vector<Vector2Int> AstarPathfinding::FindPath(Vector2Int start, Vector2Int target, int max_iterations) {
    if (grid->getTileAt(target) == nullptr) {
        spdlog::error("PATHFINDING: Target tile is nullptr");
    }
    if (grid->getTileAt(start) == nullptr) {
        spdlog::error("PATHFINDING: Start tile is nullptr");
    }

    if (grid->getTileAt(target)->vacant()) {
        target = GetNearestVacantTile(target, start);
    }

    std::unordered_set<Vector2Int> openSet;
    std::unordered_set<Vector2Int> closedSet;
    std::unordered_map<Vector2Int, Vector2Int> cameFrom;
    std::unordered_map<Vector2Int, float> gScore;
    std::unordered_map<Vector2Int, float> fScore;

    openSet.insert(start);
    gScore[start] = 0;
    fScore[start] = VectorUtils::Distance(start, target);

    int iterationCount = 0; // Counter for iterations

    while (!openSet.empty()) {
        // Check if the maximum iteration limit has been reached
        if (iterationCount >= max_iterations) {
            spdlog::warn("PATHFINDING: Maximum iterations reached. Path may be incomplete.");
            break; // Exit the loop
        }

        Vector2Int current = GetLowestFScore(openSet, fScore);
        if (current == target) {
            path = ReconstructPath(cameFrom, current);
            return path;
        }

        openSet.erase(current);
        closedSet.insert(current);

        for (auto neigh : GetNeighbours(current)) {
            if (closedSet.contains(neigh) || !grid->getTileAt(neigh)->vacant()) {
                continue;
            }

            float tentativeGScore = gScore[current] + VectorUtils::Distance(current, neigh);
            if (!openSet.contains(neigh) || tentativeGScore < gScore[neigh]) {
                cameFrom[neigh] = current;
                gScore[neigh] = tentativeGScore;
                fScore[neigh] = gScore[neigh] + VectorUtils::Distance(neigh, target);
                if (!openSet.contains(neigh)) {
                    openSet.insert(neigh);
                }
            }
        }

        iterationCount++; // Increment the iteration counter
    }

    spdlog::error("PATHFINDING: No path found");
    path.clear();
    return path;
}


Vector2Int AstarPathfinding::GetNearestVacantTileInRange(Vector2Int target, Vector2Int origin, int range) {
    // Base case: If range is 1, call GetNearestVacantTile
    if (range <= 1) {
        return GetNearestVacantTile(target, origin);
    }

    std::vector<Vector2Int> candidateTiles;
    // Generate all candidate positions in a circle around the target within the specified range
    for (int dx = -range; dx <= range; ++dx) {
        for (int dz = -range; dz <= range; ++dz) {
            if (std::sqrt(dx * dx + dz * dz) <= range) {
                Vector2Int candidateTile = target + Vector2Int(dx, dz);
                candidateTiles.push_back(candidateTile);
            }
        }
    }

    // Sort candidate tiles by distance to the origin
    std::sort(candidateTiles.begin(), candidateTiles.end(), [origin](Vector2Int a, Vector2Int b) {
        return VectorUtils::Distance(a, origin) < VectorUtils::Distance(b, origin);
    });

    // Check each candidate position
    for (const auto& candidateTile : candidateTiles) {
        // Check if the candidate tile is within grid bounds
        if (grid->getTileAt(candidateTile) != nullptr) {
            // Check if the candidate tile is vacant
            if (grid->getTileAt(candidateTile)->vacant()) {
                // Check if a path can be found to this tile
                std::vector<Vector2Int> path = FindPath(origin, candidateTile);
                if (!path.empty()) {
                    return candidateTile;
                }
            }
        }
    }

    // If no suitable tile is found, decrease the range and try again
    return GetNearestVacantTileInRange(target, origin, range - 1);
}


