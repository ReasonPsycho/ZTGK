//
// Created by Seren on 24.04.2024.
//

#pragma once

#include <cstdint>
#include <limits>
#include <random>
#include <utility>

class PcgEngine {
public:
	using seed_type = std::pair<std::uint64_t, std::uint64_t>;
	using result_type = std::uint32_t;
	PcgEngine() {}
	PcgEngine(seed_type value)
		: state {value.first}, inc {value.second} {}
	static constexpr result_type min() {
		return std::numeric_limits<result_type>::min();
	}
	static constexpr result_type max() {
		return std::numeric_limits<result_type>::max();
	}
	inline void seed(seed_type value) {
		state = value.first;
		inc = value.second;
	}
	inline result_type operator()() {
		std::uint32_t x = static_cast<std::uint32_t>((state >> 18 ^ state) >> 27);
		std::uint32_t s = state >> 59;
		state = state * 0x5851F42D4C957F2DuLL + (inc | 1);
		return (x >> s) | (x << ((~s + 1) & 31));
	}
private:
	std::uint64_t state {};
	std::uint64_t inc {};
};

inline PcgEngine::seed_type pcgRandomSeed() {
	std::random_device dev;
	std::uint64_t seeds[2] {};
	for (auto& seed : seeds) {
		seed = dev();
		seed = seed << 32 | dev();
	}
	return {seeds[0], seeds[1]};
}