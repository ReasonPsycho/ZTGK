#version 430

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

struct CellData {
    int spatialLookup[2];
    int startIndices;
};

layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

uniform int numPairs;
uniform int numStages;

void main() {
    int numberOfReapets = int(ceil(numPairs / gl_WorkGroupSize.x));
    
    if(numPairs < gl_WorkGroupSize.x){
        numberOfReapets = 1;
    }
    
    for (int stageIndex = 0; stageIndex < numStages; stageIndex++) {
        for (int stepIndex = 0; stepIndex < stageIndex + 1; stepIndex++) {

            uint groupWidth = 1 << (stageIndex - stepIndex);
            uint groupHeight = 2 * groupWidth - 1;
            for (int repeat = 1; repeat < numberOfReapets + 1; repeat++) {

                uint index = uint(gl_GlobalInvocationID.x * repeat);

                uint h = index & (groupWidth - 1);
                uint indexLow = h + (groupWidth + 1) * (index / groupWidth);
                uint indexHigh = indexLow + (stepIndex == 0 ? groupHeight - 2 * h : (groupHeight + 1) / 2);

                barrier();
                if (indexHigh >= cellData.length()) return;
                
                CellData valueLow = cellData[indexLow];
                CellData valueHigh = cellData[indexHigh];
                
                if (valueLow.spatialLookup[1] > valueHigh.spatialLookup[1]){
                    cellData[indexLow] = valueHigh;
                    cellData[indexHigh] = valueLow;
                    barrier();
                }
            }
        }
    }
}