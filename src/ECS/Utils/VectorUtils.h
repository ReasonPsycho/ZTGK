//
// Created by igork on 20.03.2024.
//

#ifndef ZTGK_VECTORUTILS_H
#define ZTGK_VECTORUTILS_H


#include "glm/vec3.hpp"

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

class VectorUtils {
public:
    static glm::vec3 Vector3ToGlmVec3(const Vector3 &vector) {
        return {vector.x, vector.y, vector.z};
    }
    static Vector3 GlmVec3ToVector3(const glm::vec3 &vector) {
        return {vector.x, vector.y, vector.z};
    }
};

#endif //ZTGK_VECTORUTILS_H
