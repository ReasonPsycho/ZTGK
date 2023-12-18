#version 430

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

struct AsteroidData
{
    vec4 position;
    vec4 rotation;
    vec4 scale;
    vec4 velocity;
    vec4 angularVelocity;
};

struct CellData {
    int spatialLookup[2];
    int startIndices;
};

struct CellCord {
    int x;
    int y;
    int z;
};

layout (std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[];
};

layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

uniform int numPairs;

void main() {
    int index = int(gl_GlobalInvocationID.x);
    int h = index & (groupWidth - 1);
    int indexLow = h + (groupWidth + 1) * (index / groupWidth);
    int indexHigh = indexLow + (stepIndex == 0 ? groupHeight - 2 * h : (groupHeight + 1) / 2);

    if (indexHigh >= cellData.length()) return;

    CellData valueLow = cellData[indexLow];
    CellData valueHigh = cellData[indexHigh];

    if(valueLow.spatialLookup[1] > valueHigh.spatialLookup[1]){
        cellData[indexLow] = valueHigh;
        cellData[indexHigh] = valueLow;
    }
}