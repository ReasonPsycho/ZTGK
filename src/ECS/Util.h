//
// Created by cheily on 21.03.2024.
//

#pragma once

#include <atomic>
#include <chrono>

namespace ztgk {
    // entity i component aktualnie używają własnej generacji, jak krzychu zrobił tak narazie zostawiam
    static constexpr short ID_POOL_ENTITY = 0;
    static constexpr short ID_POOL_COMPONENT = 1;
    static constexpr short ID_POOL_SIGNAL_RECEIVER = 2;
    static constexpr short ID_POOL_SIGNAL = 3;

    template<int POOL>
    constexpr unsigned id() {
        static std::atomic<unsigned> _id{0};
        return ++_id;
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
