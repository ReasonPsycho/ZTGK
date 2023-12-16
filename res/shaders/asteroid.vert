#version 460
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

struct AsteroidData
{
    mat4 model;    // 16
    vec3 velocity;    // 16
    vec3 rotation;    // 16
};


layout(std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[]; // Array of velocities
};

uniform mat4 view;
uniform mat4 projection;

void main()
{
    uint index = gl_InstanceID;

    TexCoords = aTexCoords;
    gl_Position = projection * view * asteroidsData[index].model * vec4(aPos, 1.0f);
}