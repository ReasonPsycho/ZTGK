#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

struct WallData
{
    mat4x4 matrix;
    int[4] data;
};


layout (std430, binding = 6) buffer WallDataBuffer {
    WallData wallData[]; // Array of velocities
};


void main()
{
    uint index = gl_InstanceID;
    gl_Position = wallData[index].matrix * vec4(aPos, 1.0);
}
