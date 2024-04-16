#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VS_OUT {
     vec3 FragPos;
     vec3 Normal;
     vec2 TexCoords;
     vec3 WorldPos;
}vs_out;

void main()
{
    vs_out.FragPos = aPos;
    vs_out.Normal = aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.WorldPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(aPos, 1.0);
}
