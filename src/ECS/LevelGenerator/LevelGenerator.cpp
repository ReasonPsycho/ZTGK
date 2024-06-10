// 
// Created by Seren on 24.04.2024. 
// 
 
#include "LevelGenerator.h" 
#include <format> 
#include <map> 
#include "ECS/Utils/RNG.h" 
 
std::ostream& operator<<(std::ostream& os, const LevelLayout& level) { 
	using TileType = LevelLayout::Tile::Type; 
	std::map<TileType, char> chars { 
		{TileType::wall,  'O'}, 
		{TileType::floor, ' '}, 
		{TileType::chest, '*'}, 
		{TileType::ore,   '^'}, 
		{TileType::core,  'c'}, 
		{TileType::unit,  '+'}, 
		{TileType::bug,   'x'}, 
        {TileType::shroom,'s'} 
	}; 
	os << "# ---LAYOUT START---"; 
	for (std::size_t i = 0; i < level.grid.size(); i++) { 
		if (i % level.size.x == 0) 
			os << '\n' << '#'; 
		os << chars.at(level.grid[i].type); 
	} 
	os << '\n'; 
	os << "# ---LAYOUT END---" << '\n'; 
	os << "seed: " << std::format("{:016x}{:016x}", level.seed.first, level.seed.second) << '\n'; 
	os << "grid:\n"; 
	os << "  width: " << level.size.x << '\n'; 
	os << "  height: " << level.size.y << '\n'; 
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
	std::uniform_int_distribution<int> enemyDist(config.minEnemies, config.maxEnemies); 
	auto noiseSize = config.size / 4; 
	generatePerlinNoiseGrid(noiseSize, rand); 
	auto padding = config.wallThickness * 0.5f; 
	auto center = glm::floor(glm::vec2(config.size) * 0.5f) + 0.5f; 
	auto basePocketIndex = tryMakePocket(center, config.baseRadius + padding, Pocket::Type::base); 
	if (basePocketIndex >= 0) { 
		hollowOutPocket(basePocketIndex, padding, 0.f); 
		for(int i = -2; i <= 2; i++){ 
            for(int j = -2; j <= 2; j++){ 
                getTile(glm::ivec2(pockets[basePocketIndex].center) + glm::ivec2(i, j))->type = Tile::Type::core; 
            } 
        } 
//        getTile(glm::ivec2(pockets[basePocketIndex].center))->type = Tile::Type::core; 
		addAtRandomToPocket(basePocketIndex, config.unitCount, Tile::Type::unit, rand, [this](glm::ivec2 pos) { 
			return !isTileAdjacentTo(pos, [this](glm::ivec2 otherPos) { 
				auto other = getTile(otherPos); 
				return other != nullptr && (other->type == Tile::Type::wall || other->type == Tile::Type::core); 
			}); 
		}); 
	} 
	float distanceMod = 0.f; 
	for (std::size_t i = 0; i < config.keyDistances.size();) { 
		auto distance = config.keyDistances[i] + distanceMod; 
		glm::vec2 pos = distance * randomUnitVec2(rand); 
		auto index = tryMakePocket(center + pos, config.keyRadius + padding, Pocket::Type::key); 
		if (index >= 0) { 
			hollowOutPocket(index, padding, config.noiseImpact * 0.5f); 
			getTile(glm::ivec2(pockets[index].center))->type = Tile::Type::ore; 
			addEnemiesToPocket(index, config.keyEnemies, rand); 
			i++; 
		} else { 
			distanceMod += 0.1f; 
			if (distanceMod > config.size.x + config.size.y) { 
				distanceMod = 0.f; 
				i++; 
			} 
		} 
	} 
	int firstExtra = static_cast<int>(pockets.size()); 
	for (int i = 0; i < config.extraPocketAttempts; i++) { 
		auto x = widthDist(rand); 
		auto y = heightDist(rand); 
		auto index = tryMakePocket({x, y}, config.pocketRadius + padding, Pocket::Type::standard); 
		if (index >= 0) { 
			hollowOutPocket(index, padding, config.noiseImpact); 
			addEnemiesToPocket(index, enemyDist(rand), rand); 
		} 
	} 
	int lastExtra = static_cast<int>(pockets.size() - 1); 
	if (firstExtra <= lastExtra) { 
		std::uniform_int_distribution<int> chestDist(firstExtra, lastExtra); 
		for (int i = 0, j = 0; i < config.chestCount && j < config.chestCount * 10; j++) { 
			auto index = chestDist(rand); 
			if (!pockets[index].hasChest) { 
				if (addChestToPocket(index, rand)) 
					i++; 
			} 
		}; 
	} 
} 
 
inline void LevelGenerator::generatePerlinNoiseGrid(glm::ivec2 size, PcgEngine& rand) noexcept { 
	perlinNoiseGridSize = size; 
	perlinNoiseGrid.resize(1uLL * size.x * size.y); 
	for (auto&& v : perlinNoiseGrid) { 
		v = randomUnitVec2(rand); 
	} 
} 
 
float LevelGenerator::getPerlinNoise(glm::vec2 pos) const noexcept { 
	auto size = perlinNoiseGridSize; 
	auto p = glm::clamp(pos, 0.f, 1.f) * glm::vec2(size - 1); 
	auto low = glm::floor(p); 
	auto high = glm::ceil(p); 
	float result = 0.f; 
	for (int i = 0; i < 3; i++) { 
		auto x = i & 1 ? high.x : low.x; 
		auto y = i & 2 ? high.y : low.y; 
		auto index = static_cast<std::size_t>(y) * size.x + static_cast<std::size_t>(x); 
		const auto& value = perlinNoiseGrid[index]; 
		auto displacement = p - glm::vec2(x, y); 
		result += glm::dot(displacement, value) * glm::abs((1.f - displacement.x) * (1.f - displacement.y)); 
	} 
	return result; 
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
	pocket.center = pos; 
	pocket.radius = radius; 
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
 
void LevelGenerator::hollowOutPocket(int index, float padding, float noiseImpact) noexcept { 
	const auto& pocket = pockets[index]; 
	forEachPocketTile(index, [&](glm::ivec2 pos) { 
		auto d = glm::distance(glm::vec2(pos) + glm::vec2(0.5f), pocket.center); 
		float noise = noiseImpact != 0.f ? getPerlinNoise(glm::vec2(pos) / glm::vec2(level.size - 1)) * noiseImpact : 0.f; 
		if (d < pocket.radius - padding + noise && isTileSafeToHollowOut(pos)) 
			getTile(pos)->type = Tile::Type::floor; 
	}); 
} 
 
void LevelGenerator::addEnemiesToPocket(int index, int count, PcgEngine& rand) noexcept { 
	addAtRandomToPocket(index, count, RNG::RandomBool() ? Tile::Type::bug : Tile::Type::shroom, rand, [](glm::ivec2) { 
		return true; 
	}); 
} 
 
bool LevelGenerator::addChestToPocket(int index, PcgEngine& rand) noexcept { 
	auto added = addAtRandomToPocket(index, 1, Tile::Type::chest, rand, [this](glm::ivec2 pos) { 
		return isTileAdjacentTo(pos, [this](glm::ivec2 otherPos) { 
			auto other = getTile(otherPos); 
			return other != nullptr && other->type == Tile::Type::wall; 
		}); 
	}); 
	if (added == 0) 
		return false; 
	pockets[index].hasChest = true; 
	return true; 
} 
