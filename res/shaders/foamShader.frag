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
    sampler2D diffuseTexture; 
    sampler2D specularTexture; 
    sampler2D normalTexture; 
    sampler2D depthTexture; 
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
 
 
void main() { 
    // Multiply the texture coordinates by the repeat factor to increase repetition 
    vec2 repeatedTexCoords = fs_in.TexCoords * repeatFactor; 
    vec4 color = texture(material.diffuseTexture, repeatedTexCoords); 
 
    FoamMask = color; 
} 
