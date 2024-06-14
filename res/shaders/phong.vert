#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout(location = 5) in ivec4 boneIds;
layout(location = 6) in vec4 weights;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 camPos;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 5;
uniform mat4 finalBonesMatrices[MAX_BONES];
uniform bool isAnimated;

struct TangentData{ // So it's easier to operate on
    vec3 ViewPos;
    vec3 FragPos;
    mat3 TBN;//No light position but TBN since fuck transporting 20 lights pos that are allready in SSBO
};


out VS_OUT {
    vec2 TexCoords;
    vec3 WorldPos;
    vec3 LocalPos;
    vec3 Normal;
    TangentData tangentData;
}vs_out;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    if(isAnimated){
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
        {
            if(boneIds[i] == -1)
            continue;
            if(boneIds[i] >=MAX_BONES)
            {
                totalPosition = vec4(aPos,1.0f);
                break;
            }
            vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos,1.0f);
            totalPosition += localPosition * weights[i];
            vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
        } 
    }else{
        totalPosition = vec4(aPos,1.0f);
    }
   
    
    //Standard calculation
    vs_out.TexCoords = aTexCoords;
    vs_out.LocalPos = vec3(totalPosition);
    vs_out.WorldPos = vec3(model* totalPosition);
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
