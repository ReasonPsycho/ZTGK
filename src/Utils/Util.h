//
// Created by cheily on 21.03.2024.
//

#pragma once

#include <atomic>
#include <chrono>
#include "Console.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace ztgk {
    static constexpr short ID_POOL_SYSTEM = 0;
    static constexpr short ID_POOL_ENTITY = 1;
    static constexpr short ID_POOL_COMPONENT = 2;
    static constexpr short ID_POOL_SIGNAL_RECEIVER = 3;
    static constexpr short ID_POOL_SIGNAL = 4;
    static constexpr short ID_POOL_HUD_GROUP = 5;
    static constexpr short ID_POOL_CONSOLE = 6;

    template<int POOL>
    constexpr unsigned id() {
        static std::atomic<unsigned> _id{0};
        return _id++;
    }

    static constexpr short MASK_ID_POOL_SIGNAL_TYPE = 0;

    template<int POOL>
    constexpr unsigned mask_id() {
        static std::atomic<unsigned> _id{1};
        auto ret = unsigned(_id);
        _id = _id << 1;
        return ret;
    }

    // in millis
    long long time();

    extern Console console;

    static struct {
        const glm::vec4 BLACK = { 0, 0, 0, 1 };
        const glm::vec4 WHITE = { 1, 1, 1, 1 };
        const glm::vec4 RED = { 1, 0, 0, 1 };
        const glm::vec4 GREEN = { 0, 1, 0, 1 };
        const glm::vec4 BLUE = { 0, 0, 1, 1 };
        const glm::vec4 YELLOW = { 1, 1, 0, 1 };
        const glm::vec4 CYAN = { 0, 1, 1, 1 };
        const glm::vec4 MAGENTA = { 1, 0, 1, 1 };
        const glm::vec4 GRAY = { 0.5, 0.5, 0.5, 1 };
        const glm::vec4 BROWN = { 0.647, 0.165, 0.165, 1 };
        const glm::vec4 ORANGE = { 1, 0.647, 0, 1 };
        const glm::vec4 PURPLE = { 0.5, 0, 0.5, 1 };
        const glm::vec4 TEAL = { 0, 0.5, 0.5, 1 };
        const glm::vec4 PINK = { 1, 0.753, 0.796, 1 };
        const glm::vec4 LIME = { 0, 1, 0, 1 };
        const glm::vec4 NAVY = { 0, 0, 0.5, 1 };
        const glm::vec4 MAROON = { 0.5, 0, 0, 1 };
        const glm::vec4 OLIVE = { 0.5, 0.5, 0, 1 };
        const glm::vec4 TURQUOISE = { 0.251, 0.878, 0.816, 1 };
        const glm::vec4 INDIGO = { 0.294, 0, 0.51, 1 };
    } color;

    template<typename T>
    struct Vec2 {
        T x;
        T y;

        Vec2(T x, T y) : x(x), y(y) {}

        Vec2() = default;

        bool operator==(const Vec2 &other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vec2 &other) const {
            return x != other.x || y != other.y;
        }

        Vec2 operator+(const Vec2 &other) const {
            return {x + other.x, y + other.y};
        }

        Vec2 operator-(const Vec2 &other) const {
            return {x - other.x, y - other.y};
        }

        Vec2 operator*(T scalar) const {
            return {x * scalar, y * scalar};
        }

        Vec2 operator/(T scalar) const {
            return {x / scalar, y / scalar};
        }

        Vec2 &operator+=(const Vec2 &other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2 &operator-=(const Vec2 &other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vec2 &operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vec2 &operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }
    };

    template<typename T>
    struct Vec3 {
        T x;
        T y;
        T z;

        Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

        Vec3() = default;

        bool operator==(const Vec3 &other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const Vec3 &other) const {
            return x != other.x || y != other.y || z != other.z;
        }

        Vec3 operator+(const Vec3 &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vec3 operator-(const Vec3 &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        Vec3 operator*(T scalar) const {
            return {x * scalar, y * scalar, z * scalar};
        }

        Vec3 operator/(T scalar) const {
            return {x / scalar, y / scalar, z / scalar};
        }

        Vec3 &operator+=(const Vec3 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3 &operator-=(const Vec3 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vec3 &operator*=(T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vec3 &operator/=(T scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }
    };
}
