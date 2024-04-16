#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

struct WallData
{
    mat4x4 matrix;
};


layout (std430, binding = 6) buffer WallDataBuffer {
    WallData wallData[]; // Array of velocities
};

uniform mat4 projection;
uniform mat4 view;

out VS_OUT {
     vec3 FragPos;
     vec2 TexCoords;
     vec3 WorldPos;
}vs_out;

void main()
{
    uint index = gl_InstanceID;

    vs_out.FragPos = aPos;
    vs_out.TexCoords = aTexCoords;
    vs_out.WorldPos = vec3(wallData[index].matrix * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0);
}
