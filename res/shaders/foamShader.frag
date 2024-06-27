#version 460
layout (location = 0) out vec4 FoamMask;


struct TangentData{ // So it's easier to operate on
    vec3 ViewPos;
    vec3 FragPos;
    mat3 TBN;//No light position but TBN since fuck transporting 20 lights pos that are allready in SSBO
};

in VS_OUT {
    vec2 TexCoords;
    vec3 WorldPos;
    vec3 Normal;
    TangentData tangentData;
}fs_in;

struct Material {
    sampler2DArray diffuseTextureArray;
    sampler2DArray specularTextureArray;
    sampler2DArray normalTextureArray;
    sampler2DArray depthTextureArray;
};

uniform bool useNormalMap;
uniform int spotLightAmount;
uniform int dirLightAmount;
uniform int pointLightAmount;
uniform float heightScale;
uniform vec3 viewPos;
uniform vec3 camPos;
uniform Material material;
uniform float saturationMultiplayer;  // sat multiplier is the factor by which you increase saturation.
uniform float lightMultiplayer;  // sat multiplier is the factor by which you increase saturation
uniform int toon_color_levels;

uniform float diffuse_levels;
uniform float specular_levels;
uniform float light_shade_cutoff;
uniform float dark_shade_cutoff;

uniform float rim_threshold;
uniform float rim_amount;

uniform float repeatFactor;
uniform float u_time;


void main() {
    // Multiply the texture coordinates by the repeat factor to increase repetition
    vec2 repeatedTexCoords = fs_in.TexCoords * repeatFactor;
    vec4 color = vec4(texture(material.diffuseTextureArray, vec3(repeatedTexCoords, 0)));

    float currentFrame = mod(u_time, 30.0);  // Normalize currentFrame to instead vary from 0.0 to 6.0
    vec4 texture = vec4(texture(material.diffuseTextureArray, vec3(repeatedTexCoords, (currentFrame/10) + 1)));
    color = mix(color,texture,texture.a * abs(sin(currentFrame/5)));
    
    FoamMask = color;
}