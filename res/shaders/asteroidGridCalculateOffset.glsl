#version 430

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

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

void main() { // This is dumb implementation it should be seperate structor etc etc.
    int index = int(gl_WorkGroupID .x);
    if (index >= cellData.length()) { return; }

    int null = cellData.length();

    int key = cellData[index].cellHash;
    int keyPrev = index == 0 ? null : cellData[index - 1].cellHash;

    if (key != keyPrev)
    {
        offsets[key].value = index;
    }
}