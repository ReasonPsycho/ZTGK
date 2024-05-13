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

out vec4 FragPos; // Send position to next stage
uniform mat4 shadowMatrice;


void main()
{
    uint index = gl_InstanceID;
    vec4 pos = wallData[index].matrix * vec4(aPos, 1.0);
    gl_Position = shadowMatrice * pos;
    FragPos = pos;
}
