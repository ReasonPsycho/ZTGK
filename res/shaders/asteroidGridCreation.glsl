#version 430

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct AsteroidData
{
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

layout (std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[];
};

layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

layout (std430, binding = 2) buffer OffsetsBuffer {
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

uniform float gridRadius;

void main() {
    uint index = gl_WorkGroupID .x;
    cellData[index].key = int(index);
    cellData[index].cellHash = int(HashCell(PositionToCellCoord(asteroidsData[index].position.xyz,gridRadius)));
}