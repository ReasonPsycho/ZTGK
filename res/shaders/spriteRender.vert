#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 WorldPos;
    vec3 ViewPos;
}vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 camPos;
uniform vec3 cameraUp;

uniform mat4 model;
uniform float scale;


void main()
{
    
    //Standard calculation
    vs_out.TexCoords = aTexCoords;
    vs_out.WorldPos = vec3(model* vec4(aPos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.ViewPos = camPos;
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0);
}
