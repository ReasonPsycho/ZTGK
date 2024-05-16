#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


out VS_OUT {
     vec3 FragPos;
     vec2 TexCoords;
     vec3 WorldPos;
    vec3 Normal;
}vs_out;

void main()
{
    vs_out.FragPos = aPos;
    vs_out.TexCoords = aTexCoords;
    vs_out.WorldPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0);
}
