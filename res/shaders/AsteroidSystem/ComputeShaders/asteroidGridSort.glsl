#version 430

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;


struct CellData {
    int key;
    int cellHash;
};

struct Offsets {
    int value;
};


layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

layout (std430, binding = 2) buffer OffsetsBuffer {
    Offsets offsets[];
};

uniform int groupWidth;
uniform int groupHeight;
uniform int stepIndex;

void main() {


    int i = int(gl_WorkGroupID .x);

    uint hIndex = i & (groupWidth - 1);
    uint indexLeft = hIndex + (groupHeight + 1) * (i / groupWidth);
    uint rightStepSize = stepIndex == 0 ? groupHeight - 2 * hIndex : (groupHeight + 1) / 2;
    uint indexRight = indexLeft + rightStepSize;

    if (indexRight < cellData.length()) {
        CellData valueLow;
        CellData valueHigh;
        valueLow = cellData[indexLeft];
        valueHigh = cellData[indexRight];
        if (valueLow.cellHash > valueHigh.cellHash) {
            cellData[indexLeft] = valueHigh;
            cellData[indexRight] = valueLow;
        }
    }
}
