#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 camPos;


struct TangentData{ // So it's easier to operate on
    vec3 ViewPos;
    vec3 FragPos;
    mat3 TBN;//No light position but TBN since fuck transporting 20 lights pos that are allready in SSBO
};


out VS_OUT {
    vec2 TexCoords;
    vec3 WorldPos;
    vec3 Normal;
    TangentData tangentData;
}vs_out;

void main()
{
    //Standard calculation
    vs_out.TexCoords = aTexCoords;
    vs_out.WorldPos = vec3(model* vec4(aPos, 1.0) );
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0);

    //Tanget calculations
    vec3 T = normalize(mat3(model) * aTangent);
    vec3 B = normalize(mat3(model) * aBitangent);
    vec3 N = normalize(mat3(model) * aNormal);
    mat3 TBN = transpose(mat3(T, B, N));

    vs_out.tangentData.ViewPos  = TBN * (camPos + vec3(0.000001));
    vs_out.tangentData.FragPos  = TBN *  vs_out.WorldPos;
    vs_out.tangentData.TBN  = TBN;
}
