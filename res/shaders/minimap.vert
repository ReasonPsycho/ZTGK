#version 460

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 camPos;

struct WallData
{
    mat4x4 matrix;
    int[4] data;
    int[4] textures;
};

layout (std430, binding = 6) buffer WallDataBuffer {
    WallData wallData[]; // Array of velocities
};

out flat int[4] currentWallData;

void main()
{
    //Instance shader set up
    uint index = gl_InstanceID;
    mat4 model = wallData[index].matrix; //So it's universal beetween instance and normal shader

    // "My special dataTM" calculation
    currentWallData = wallData[index].data;

    vec3 position = vec3(model* vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(position, 1.0);
}
