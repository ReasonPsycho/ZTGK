//
// Created by igork on 20.03.2024.
//

#ifndef ZTGK_VECTORUTILS_H
#define ZTGK_VECTORUTILS_H


struct Vector2Int {
    int x;
    int z;

    Vector2Int(int x, int z) : x(x), z(z) {}
    Vector2Int() = default;

    bool operator==(const Vector2Int& other) const {
        return x == other.x && z == other.z;
    }

    bool operator!=(const Vector2Int& other) const {
        return x != other.x || z != other.z;
    }

    Vector2Int operator+(const Vector2Int& other) const {
        return {x + other.x, z + other.z};
    }

    Vector2Int operator-(const Vector2Int& other) const {
        return {x - other.x, z - other.z};
    }

    Vector2Int operator*(int scalar) const {
        return {x * scalar, z * scalar};
    }

    Vector2Int operator/(int scalar) const {
        return {x / scalar, z / scalar};
    }

    Vector2Int& operator+=(const Vector2Int& other) {
        x += other.x;
        z += other.z;
        return *this;
    }

    Vector2Int& operator-=(const Vector2Int& other) {
        x -= other.x;
        z -= other.z;
        return *this;
    }

    Vector2Int& operator*=(int scalar) {
        x *= scalar;
        z *= scalar;
        return *this;
    }

    Vector2Int& operator/=(int scalar) {
        x /= scalar;
        z /= scalar;
        return *this;
    }



};

struct Vector3{
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3() = default;

    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3& other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    Vector3 operator+(const Vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator-(const Vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vector3 operator/(float scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }

    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }


};

template<typename T>
struct Vec2 {
    T x;
    T y;

    Vec2(T x, T y) : x(x), y(y) {}
    Vec2() = default;

    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2& other) const {
        return x != other.x || y != other.y;
    }

    Vec2 operator+(const Vec2& other) const {
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }

    Vec2 operator*(T scalar) const {
        return {x * scalar, y * scalar};
    }

    Vec2 operator/(T scalar) const {
        return {x / scalar, y / scalar};
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& operator/=(T scalar) {
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

    bool operator==(const Vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3& other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(T scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vec3 operator/(T scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }

    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vec3& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};

#endif //ZTGK_VECTORUTILS_H
