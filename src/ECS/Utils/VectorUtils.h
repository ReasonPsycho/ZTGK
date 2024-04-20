//
// Created by igork on 20.03.2024.
//

#ifndef ZTGK_VECTORUTILS_H
#define ZTGK_VECTORUTILS_H


#include "glm/vec3.hpp"
#include <cmath>

struct Vector2Int {
    int x;
    int z;

    Vector2Int(int x, int z) : x(x), z(z) {}
    Vector2Int() = default;

    void normalize() {
        int length = sqrt(x * x + z * z);
        x /= length;
        z /= length;
    }

    int dot(Vector2Int other) {
        return x * other.x + z * other.z;
    }


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

    static float Distance(Vector2Int a, Vector2Int b) {
        return sqrt(pow(a.x - b.x, 2) + pow(a.z - b.z, 2));
    }
    static float Distance(Vector3 a, Vector3 b) {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
    }

    static float DistanceSquared(Vector2Int a, Vector2Int b) {
        return pow(a.x - b.x, 2) + pow(a.z - b.z, 2);
    }

    static float DistanceSquared(Vector3 a, Vector3 b) {
        return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
    }


    static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta) {
        Vector3 a = target - current;
        float magnitude = a.x * a.x + a.y * a.y + a.z * a.z;
        if (magnitude <= maxDistanceDelta || magnitude == 0.0f) {
            return target;
        }
        float num = sqrt(magnitude);
        return current + a / num * maxDistanceDelta;
    }
};

#endif //ZTGK_VECTORUTILS_H
