#version 430

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct CellData {
    int spatialLookup[2];
    int startIndices;
};

layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

void main() { // This is dumb implementation it should be seperate structor etc etc.
    int index = int(gl_GlobalInvocationID.x);
    if (index >= cellData.length()) { return; }
    if (index == 0) {
        cellData[index].startIndices = 9999999;
        return;
    }
    if (index  == cellData.length() - 1) {
        cellData[index].startIndices = 9999999;
        return;
    }
    
    int currentKey = cellData[index].spatialLookup[1];
    int nextKey = cellData[index + 1].spatialLookup[1];

    if (currentKey == nextKey) {
        cellData[index].startIndices = 9999999;
        return;
    }

    int searchIndex = int(gl_GlobalInvocationID.x) - 1;
    int previusKey = cellData[searchIndex].spatialLookup[1];

    
    while (currentKey == previusKey && searchIndex != -1){
        searchIndex--;
        previusKey = cellData[searchIndex].spatialLookup[1];
    }

    cellData[currentKey].startIndices = searchIndex + 1;
}