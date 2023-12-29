#version 430

layout(local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

struct CellData {
    int spatialLookup[2];
    int startIndices;
};

layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

uniform int groupWidth;
uniform int groupHeight;
uniform int stepIndex;

void main() {


    int i = int(gl_GlobalInvocationID.x);

    uint hIndex = i & (groupWidth - 1);
    uint indexLeft = hIndex + (groupHeight + 1) * (i / groupWidth);
    uint rightStepSize = stepIndex == 0 ? groupHeight - 2 * hIndex : (groupHeight + 1) / 2;
    uint indexRight = indexLeft + rightStepSize;

    if (indexRight < cellData.length()){
        CellData valueLow;
        CellData valueHigh;
        valueLow = cellData[indexLeft];
        valueHigh = cellData[indexRight];
        if (valueLow.spatialLookup[1] > valueHigh.spatialLookup[1]){
            cellData[indexLeft] = valueHigh;
            cellData[indexRight] = valueLow;
        }
    }
}
