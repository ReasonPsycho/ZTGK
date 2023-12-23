#version 430

//HERE SHOULD BE LAYOUT

struct CellData {
    int spatialLookup[2];
    int startIndices;
};

layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

uniform int numOfIterations;
uniform int numStages;

void main() {
    for (int stageIndex = 0; stageIndex < numStages; stageIndex++) {
        for (int stepIndex = 0; stepIndex < stageIndex + 1; stepIndex++) {
            uint groupWidth = 1 << (stageIndex - stepIndex);
            uint groupHeight = 2 * groupWidth - 1;
            for (uint repeat = 0; repeat < numOfIterations; repeat++) {

                uint i = uint(gl_LocalInvocationID.x * (repeat + 1));
                
                uint hIndex = i & (groupWidth - 1);
                uint indexLeft = hIndex + (groupHeight + 1) * (i / groupWidth);
                uint rightStepSize = stepIndex == 0 ? groupHeight - 2 * hIndex : (groupHeight + 1) / 2;
                uint indexRight = indexLeft + rightStepSize;

                bool withinTable = indexRight < cellData.length();
                barrier();
                CellData valueLow;
                CellData valueHigh;
                if (withinTable){
                    valueLow = cellData[indexLeft];
                    valueHigh = cellData[indexRight];
                }
                barrier();
                if ( withinTable && (valueLow.spatialLookup[1] > valueHigh.spatialLookup[1])){
                    cellData[indexLeft] = valueHigh;
                    cellData[indexRight] = valueLow;
                }
            }
        }
    }
}
