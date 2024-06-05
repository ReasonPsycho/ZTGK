#version 460
out vec4 FragColor;

in VS_OUT {
    vec2 TexCoords;
    vec3 WorldPos;
    vec3 ViewPos;
    vec3 Normal;
}fs_in;

 in flat int[4] currentWallData;
 in flat int[4] currentTextures;

struct Material { 
    sampler2DArray diffuseTextureArray;
    sampler2DArray specularTextureArray;
    sampler2DArray normalTextureArray;
    sampler2DArray depthTextureArray;
};

uniform Material material;


vec3 selectionColor[5] = vec3[]
(
vec3(1, 1, 1), //Just here to simplyfiy the logic
vec3(0, 1, 0),
vec3(0, 0, 1),
vec3(1, 0, 0),
vec3(1, 0, 1)
);


void main()
{
    if (currentWallData[1] != 1){
        discard;
    }
    FragColor = vec4(0);
}