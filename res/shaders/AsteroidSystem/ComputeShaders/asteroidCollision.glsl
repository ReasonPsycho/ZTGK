#version 430

layout(local_size_x = 27, local_size_y = 1, local_size_z = 1) in;

struct AsteroidData {
    vec4 position;
    vec4 rotation;
    vec4 scale;
    vec4 velocity;
    vec4 angularVelocity;
    vec4 separationVector;
};

const ivec3 offsets3D[27] =
{
ivec3(-1, -1, -1),
ivec3(-1, -1, 0),
ivec3(-1, -1, 1),
ivec3(-1, 0, -1),
ivec3(-1, 0, 0),
ivec3(-1, 0, 1),
ivec3(-1, 1, -1),
ivec3(-1, 1, 0),
ivec3(-1, 1, 1),
ivec3(0, -1, -1),
ivec3(0, -1, 0),
ivec3(0, -1, 1),
ivec3(0, 0, -1),
ivec3(0, 0, 0),
ivec3(0, 0, 1),
ivec3(0, 1, -1),
ivec3(0, 1, 0),
ivec3(0, 1, 1),
ivec3(1, -1, -1),
ivec3(1, -1, 0),
ivec3(1, -1, 1),
ivec3(1, 0, -1),
ivec3(1, 0, 0),
ivec3(1, 0, 1),
ivec3(1, 1, -1),
ivec3(1, 1, 0),
ivec3(1, 1, 1)
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

uvec3 PositionToCellCoord(vec3 position, float radius) {
    return ivec3(floor(position / radius));
}

uint HashCell(uvec3 cellCord){
    uint a = uint(cellCord.x * 15823);
    uint c = uint(cellCord.y * 9737333);
    uint b = uint(cellCord.z * 440817757);
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
    uint index = gl_WorkGroupID.x;
    vec3 sumOfCollisions = vec3(0);
    int amountOfCollisions = 0;
    AsteroidData currentAsteroid = asteroidsData[index];
    float scale = MeanOfScales(currentAsteroid.scale.xyz);
    uvec3 cellCoord = PositionToCellCoord(currentAsteroid.position.xyz, gridRadius) + offsets3D[gl_LocalInvocationID.x];
    uint hash = HashCell(cellCoord);
    int currentTablePos = offsets[hash].value;

    while (currentTablePos < int(cellData.length()) && cellData[currentTablePos].cellHash == int(hash)) {
        //if (cellData[currentTablePos].key != int(index)) { We aleready kinda ignore case when points are the same
        AsteroidData asteroidToCheck = asteroidsData[cellData[currentTablePos].key];
        float scale2 = MeanOfScales(asteroidToCheck.scale.xyz);

        float dist = length(asteroidToCheck.position.xyz - currentAsteroid.position.xyz);
        if (dist <= collisionRadius * scale/2 + collisionRadius * scale2/2) {
            if (dist != 0){
                sumOfCollisions += SeparationVector(asteroidToCheck.position.xyz, currentAsteroid.position.xyz, collisionRadius * scale/2, collisionRadius * scale2/2);
                amountOfCollisions++;
            }
        }
        currentTablePos++;
    }


    if (amountOfCollisions != 0) {
        sumOfCollisions /= float(amountOfCollisions);
        asteroidsData[index].separationVector += vec4(-sumOfCollisions, 1);
    }
}
