#version 430

layout(local_size_x = 3, local_size_y = 3, local_size_z = 3) in;

struct AsteroidData {
    vec4 position;
    vec4 rotation;
    vec4 scale;
    vec4 velocity;
    vec4 angularVelocity;
    vec4 separationVector;
};

struct CellData {
    int key;
    int cellHash;
};

struct Offsets {
    int value;
};

layout(std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[];
};

layout(std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

layout(std430, binding = 2) buffer OffsetsBuffer {
    Offsets offsets[];
};

vec3 PositionToCellCoord(vec3 position, float radius) {
    return floor(position / radius);
}

uint HashCell(vec3 cellCoord) {
    uint a = uint(cellCoord.x * 9737339);
    uint c = uint(cellCoord.y * 9737341);
    uint b = uint(cellCoord.z * 9737333);
    return (a + b + c) % uint(cellData.length());
}

vec3 SeparationVector(vec3 a, vec3 b, float ra, float rb){
    return ((a - b)/length(a - b)) * (ra + rb  - length(a-b));
}

float MeanOfScales(vec3 scale) {
    return dot(scale, vec3(1.0)) / 3.0;
}

uniform float collisionRadius;
uniform float gridRadius;

void main() {
    uint index = gl_GlobalInvocationID.x;
    vec3 sumOfCollisions = vec3(0);
    int amountOfCollisions = 0;
    AsteroidData currentAsteroid = asteroidsData[index];
    float scale = MeanOfScales(currentAsteroid.scale.xyz);

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            for (int z = -1; z <= 1; ++z) {
                
                vec3 cellCoord = PositionToCellCoord(currentAsteroid.position.xyz , gridRadius) + vec3(x, y, z);
                uint hash = HashCell(cellCoord);
                int currentTablePos = offsets[hash].value;

                while (currentTablePos < int(cellData.length()) && cellData[currentTablePos].cellHash == int(hash)) {
                    //if (cellData[currentTablePos].key != int(index)) { We aleready kinda ignore case when points are the same
                        AsteroidData asteroidToCheck = asteroidsData[currentTablePos];
                        float scale2 = MeanOfScales(asteroidToCheck.scale.xyz);

                        float dist = length(asteroidToCheck.position.xyz - currentAsteroid.position.xyz);
                        if (dist <= collisionRadius * scale + collisionRadius * scale2) {
                            if(asteroidToCheck.position.xyz != currentAsteroid.position.xyz){
                                sumOfCollisions += SeparationVector(asteroidToCheck.position.xyz, currentAsteroid.position.xyz, collisionRadius * scale, collisionRadius * scale2);
                                amountOfCollisions++;
                            }
                        }
                    currentTablePos++;
                }
            }
        }
    }

    if (amountOfCollisions == 0) {
        asteroidsData[index].separationVector = vec4(0);
    } else {
        sumOfCollisions /= float(amountOfCollisions);
        asteroidsData[index].separationVector = vec4(-sumOfCollisions, 1);
    }
}
