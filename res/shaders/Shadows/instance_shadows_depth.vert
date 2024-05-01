#version 460

layout (location = 0) in vec3 aPos;

struct WallData
{
    mat4x4 matrix;
    int[4] data;
};


layout (std430, binding = 6) buffer WallDataBuffer {
    WallData wallData[]; // Array of velocities
};

uniform mat4 lightSpaceMatrix;

void main()
{
    uint index = gl_InstanceID;
    gl_Position = vec4(lightSpaceMatrix * wallData[index].matrix * vec4(aPos, 1.0));
}
