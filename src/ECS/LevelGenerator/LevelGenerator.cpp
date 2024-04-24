//
// Created by Seren on 24.04.2024.
//

#include "LevelGenerator.h"
#include <iomanip>
#include <map>
#include <numbers>

std::ostream& operator<<(std::ostream& os, const LevelLayout& level) {
	using TileType = LevelLayout::Tile::Type;
	std::map<TileType, char> chars {
		{TileType::wall, 'O'},
		{TileType::floor, ' '},
		{TileType::chest, '*'},
		{TileType::ore, '^'},
		{TileType::core, 'c'},
		{TileType::unit, '+'},
		{TileType::enemy, 'x'},
	};
	os << "# ---LAYOUT START---";
	for (std::size_t i = 0; i < level.grid.size(); i++) {
		if (i % level.size.x == 0)
			os << '\n' << '#';
		os << chars.at(level.grid[i].type);
	}
	os << '\n';
	os << "# ---LAYOUT END---" << '\n';
	os << "seed: " << std::hex << level.seed.first << level.seed.second << std::dec << '\n';
	os << "  width: " << level.size.x;
	os << "  height: " << level.size.y;
	return os;
}

LevelLayout generateLevel(const LevelGenerator::Config& config) {
	LevelLayout result;
	LevelGenerator generator(result);
	generator(config);
	return result;
}

void LevelGenerator::operator()(const Config& config) {
	pockets.clear();
	level.seed = config.seed;
	level.size = config.size;
	level.grid.assign(1uLL * config.size.x * config.size.y, {});
	PcgEngine rand(config.seed);
	std::uniform_real_distribution<float> widthDist(0.f, 1.f * config.size.x);
	std::uniform_real_distribution<float> heightDist(0.f, 1.f * config.size.y);
	std::uniform_real_distribution<float> angleDist(-std::numbers::pi_v<float>, std::numbers::pi_v<float>);
	std::uniform_int_distribution<int> enemyDist(config.minEnemies, config.maxEnemies);
	std::bernoulli_distribution chestDist(config.treasureChance);
	auto center = glm::vec2(config.size) * 0.5f;
	auto basePocketIndex = tryMakePocket(center, config.baseRadius, Pocket::Type::base);
	if (basePocketIndex >= 0) {
		hollowOutPocket(basePocketIndex);
		getTile(pockets[basePocketIndex].center)->type = Tile::Type::core;
		addAtRandomToPocket(basePocketIndex, config.unitCount, Tile::Type::unit, rand, [this](glm::ivec2 pos) {
			return !isTileAdjacentTo(pos, [this](glm::ivec2 otherPos) {
				auto other = getTile(otherPos);
				return other != nullptr && other->type == Tile::Type::wall;
			});
		});
	}
	float distanceMod = 0.f;
	for (std::size_t i = 0; i < config.keyDistances.size();) {
		auto angle = angleDist(rand);
		auto distance = config.keyDistances[i] + distanceMod;
		glm::vec2 pos {distance * glm::cos(angle), distance * glm::sin(angle)};
		auto index = tryMakePocket(center + pos, config.keyRadius, Pocket::Type::key);
		if (index >= 0) {
			hollowOutPocket(index);
			getTile(pockets[index].center)->type = Tile::Type::ore;
			addEnemiesToPocket(index, config.keyEnemies, rand);
			i++;
		} else {
			distanceMod += 0.1f;
			if (distanceMod > config.size.x + config.size.y)
				break;
		}
	}
	for (int i = 0; i < config.extraPocketAttempts; i++) {
		auto x = widthDist(rand);
		auto y = heightDist(rand);
		auto index = tryMakePocket({x, y}, config.pocketRadius, Pocket::Type::standard);
		if (index >= 0) {
			hollowOutPocket(index);
			if (chestDist(rand))
				addChestToPocket(index, rand);
			addEnemiesToPocket(index, enemyDist(rand), rand);
		}
	}
}

bool LevelGenerator::inBounds(glm::ivec2 pos) const noexcept {
	return glm::all(glm::greaterThanEqual(pos, glm::ivec2(0))) && glm::all(glm::lessThan(pos, level.size));
}

const LevelGenerator::Tile* LevelGenerator::getTile(glm::ivec2 pos) const noexcept {
	return inBounds(pos) ? &level.grid[1uLL * pos.y * level.size.x + pos.x] : nullptr;
}

LevelGenerator::Tile* LevelGenerator::getTile(glm::ivec2 pos) noexcept {
	return inBounds(pos) ? &level.grid[1uLL * pos.y * level.size.x + pos.x] : nullptr;
}

bool LevelGenerator::hasRoomForPocket(glm::vec2 pos, float radius) const noexcept {
	int left = static_cast<int>(pos.x - radius);
	int top = static_cast<int>(pos.y - radius);
	int right = static_cast<int>(pos.x + radius + 1.f);
	int bottom = static_cast<int>(pos.y + radius + 1.f);
	for (int i = top; i <= bottom; i++) {
		for (int j = left; j <= right; j++) {
			if (glm::distance(pos, glm::vec2 {j + 0.5f, i + 0.5f}) < radius) {
				auto tile = getTile(glm::ivec2 {j, i});
				if (tile == nullptr || tile->pocketIndex >= 0)
					return false;
			}
		}
	}
	return true;
}

int LevelGenerator::tryMakePocket(glm::vec2 pos, float radius, Pocket::Type type) noexcept {
	if (!hasRoomForPocket(pos, radius))
		return -1;
	int left = static_cast<int>(pos.x - radius);
	int top = static_cast<int>(pos.y - radius);
	int right = static_cast<int>(pos.x + radius + 1.f);
	int bottom = static_cast<int>(pos.y + radius + 1.f);
	int index = static_cast<int>(pockets.size());
	for (int i = top; i <= bottom; i++) {
		for (int j = left; j <= right; j++) {
			if (glm::distance(pos, glm::vec2 {j + 0.5f, i + 0.5f}) < radius) {
				auto tile = getTile(glm::ivec2 {j, i});
				tile->pocketIndex = index;
			}
		}
	}
	auto& pocket = pockets.emplace_back();
	pocket.type = type;
	pocket.center = glm::ivec2(pos);
	return index;
}

inline bool LevelGenerator::isTileSafeToHollowOut(glm::ivec2 pos) const noexcept {
	auto tile = getTile(pos);
	if (tile == nullptr)
		return false;
	return !isTileAdjacentTo(pos, [&](glm::ivec2 otherPos) {
		auto other = getTile(otherPos);
		return other != nullptr && other->pocketIndex != tile->pocketIndex && other->type != Tile::Type::wall;
	});
}

void LevelGenerator::clearDfsVisitedFlags(glm::ivec2 pos) noexcept {
	auto tile = getTile(pos);
	if (tile == nullptr || !tile->dfsVisited)
		return;
	tile->dfsVisited = false;
	for (const auto& dir : directions) {
		clearDfsVisitedFlags(pos + dir);
	}
}

void LevelGenerator::hollowOutPocket(int index) noexcept {
	forEachPocketTile(index, [this](glm::ivec2 pos) {
		if (isTileSafeToHollowOut(pos))
			getTile(pos)->type = Tile::Type::floor;
	});
}

void LevelGenerator::addEnemiesToPocket(int index, int count, PcgEngine& rand) noexcept {
	addAtRandomToPocket(index, count, Tile::Type::enemy, rand, [](glm::ivec2) {
		return true;
	});
}

void LevelGenerator::addChestToPocket(int index, PcgEngine& rand) noexcept {
	addAtRandomToPocket(index, 1, Tile::Type::chest, rand, [this](glm::ivec2 pos) {
		return isTileAdjacentTo(pos, [this](glm::ivec2 otherPos) {
			auto other = getTile(otherPos);
			return other != nullptr && other->type == Tile::Type::wall;
		});
	});
}
