#version 460
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 frag_normal_depth; //Meant for outline process
layout (location = 2) out vec4 BloomBuffer; //Meant for outline process
layout (location = 3) out vec4 FogOfWarMask;//Meant for outline process

in VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 WorldPos;
    vec3 ViewPos;
}fs_in;

struct Material {
    sampler2DArray diffuseTextureArray;
    sampler2DArray specularTextureArray;
    sampler2DArray normalTextureArray;
    sampler2DArray depthTextureArray;
};

uniform Material material;
uniform bool outlineMapping;
in flat int[4] currentTextures;

void main()
{
    vec2 texCoords = fs_in.TexCoords;
    vec4 diffuse = vec4(texture(material.diffuseTextureArray, vec3(texCoords, float(currentTextures[0]))));

    if(diffuse.a < 0.1)
    discard;
    
    FragColor = diffuse;

    vec3 normal = fs_in.Normal;

    if(outlineMapping){
        float depth = gl_FragCoord.z;
        frag_normal_depth = vec4(normal, depth);
    }

    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));

    if(brightness > 1.0)
        BloomBuffer = vec4(FragColor.rgb, 1.0);
    else
        BloomBuffer = vec4(0.0, 0.0, 0.0, 1.0);

    FogOfWarMask =  vec4(vec3(0), 0);
}