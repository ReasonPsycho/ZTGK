#version 460

struct TangentData{ // So it's easier to operate on
    vec3 ViewPos;
    vec3 FragPos;
    mat3 TBN;//No light position but TBN since fuck transporting 20 lights pos that are allready in SSBO
};

in VS_OUT {
    vec2 TexCoords;
    vec3 WorldPos;
    vec3 ViewPos;
    vec3 Normal;
    TangentData tangentData;
}fs_in;
 in flat int[4] currentWallData;
 in flat int[4] currentTextures;

struct Material { //TODO here switch to array sampler material
    sampler2DArray diffuseTextureArray;
    sampler2DArray specularTextureArray;
    sampler2DArray normalTextureArray;
    sampler2DArray depthTextureArray;
};

struct DirLight {
    vec4 diffuse;
    vec4 specular;

    vec4 position;
    vec4 direction;
    mat4x4 lightSpaceMatrix;
};

struct PointLight {
    vec4 diffuse;
    vec4 specular;

    vec4 position;
    float constant;
    float linear;

    float quadratic;
    float pointlessfloat;
};

struct SpotLight {
    vec4 diffuse;
    vec4 specular;

    vec4 position;
    vec4 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    float pointlessfloat;
    float pointlessfloat2;
    float pointlessfloat3;

    mat4x4 lightSpaceMatrix;
};

layout (std430, binding = 3) buffer DirLightBuffer {
    DirLight dirLights[];
};

layout (std430, binding = 4) buffer PointLightBuffer {
    PointLight pointLights[];
};

layout (std430, binding = 5) buffer SpotLightBuffer {
    SpotLight spotLights[];
};

layout (binding = 8) uniform samplerCubeArray cubeShadowMaps;
layout (binding = 9) uniform sampler2DArray planeShadowMaps;

uniform int spotLightAmount;
uniform int dirLightAmount;
uniform int pointLightAmount;
uniform float heightScale;
uniform Material material;
uniform float maxBias;
uniform float biasMuliplayer;

vec3 selectionColor[5] = vec3[]
(
vec3(1, 1, 1), //Just here to simplyfiy the logic
vec3(0, 1, 0),
vec3(0, 0, 1),
vec3(1, 0, 0),
vec3(1, 0, 1)
);

vec3 gridSamplingDisk[20] = vec3[]
(
vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);


// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, int lightIndex,vec2 texCoords);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec2 texCoords);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec2 texCoords);
float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, float far_plane, int lightIndex);
float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos, float far_plane, int lightID);
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

out vec4 FragColor;

void main()
{
    vec2 texCoords = fs_in.TexCoords;
    vec3 viewDir = normalize(fs_in.tangentData.ViewPos - fs_in.tangentData.FragPos);

    texCoords = ParallaxMapping(texCoords,  viewDir);
 

    
    // properties
    // obtain normal from normal map
    vec3 normal = texture(material.normalTextureArray, vec3(texCoords,currentTextures[2])).rgb;
    normal = normalize(normal * 2.0 - 1);
    

    vec3 result = vec3(0);
    if (currentWallData[1] != 1){

        result = 0.2f * vec3(texture(material.diffuseTextureArray, vec3(texCoords, float(currentTextures[0]))));//We do be calculating ambient here
        int index = 0;
        for (int i = 0; i < dirLightAmount; ++i) {
            result += CalcDirLight(dirLights[i], normal, viewDir, index++, texCoords);
        }

        for (int i = 0; i < spotLightAmount; ++i) {
            result += CalcSpotLight(spotLights[i], normal, fs_in.tangentData.FragPos, viewDir, index++, texCoords);
        }

        index = 0;
        for (int i = 0; i < pointLightAmount; ++i) {
            result += CalcPointLight(pointLights[i], normal, fs_in.tangentData.FragPos, viewDir, index++, texCoords);
        }

    }
    else {

        result = vec3(0.5, 0.5, 0.5);
    }

    if (currentWallData[2] != 0){
        result = mix(result, selectionColor[currentWallData[2]], 0.5);
    }

    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, int lightIndex,vec2 texCoords)
{
    vec3 lightDir = normalize(vec3(-light.direction));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
    // combine results
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(material.diffuseTextureArray, vec3(texCoords, float(currentTextures[0]))));
    vec3 specular = vec3(light.specular) * spec *vec3(texture(material.specularTextureArray, vec3(texCoords,float(currentTextures[1]))));

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, light.position.w, lightIndex));

    return (diffuse + specular) * shadow;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec2 texCoords)
{
    vec3 lightDir = normalize(  vec3(fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    // diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
    // attenuation
    float distance = length(vec3( fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(material.diffuseTextureArray, vec3(texCoords, float(currentTextures[0]))));
    vec3 specular =  vec3(light.specular) * spec *vec3(texture(material.specularTextureArray, vec3(texCoords,currentTextures[1])));
    diffuse *= attenuation;
    specular *= attenuation;

    float shadow = 1;
    shadow = (1.0 - CubeShadowCalculation(fs_in.WorldPos, light.position.xyz, light.position.w, lightIndex));


    return (diffuse + specular) * shadow;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec2 texCoords)
{
    vec3 tangentLightDir = normalize(  vec3(fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    vec3 lightDir = normalize(   vec3(light.position)  - fs_in.WorldPos);
    // diffuse shading
    float diff = max(dot(normal, tangentLightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-tangentLightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
    // attenuation
    float distance = length(vec3( fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(vec3(-light.direction)));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results,vec2 
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(material.diffuseTextureArray, vec3(texCoords, float(currentTextures[0]))));
    vec3 specular =  vec3(light.specular) * spec * vec3(texture(material.specularTextureArray, vec3(texCoords,float(currentTextures[1]))));
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, light.position.w, lightIndex));


    return (diffuse + specular) * shadow;
}

float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, float far_plane, int lightIndex)
{
    vec3 fragToLight = fs_in.WorldPos -  lightPos;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias = 0.05;
    int samples = 20;
    float viewDistance = length(fs_in.ViewPos -  fs_in.WorldPos );
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for (int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(cubeShadowMaps, vec4(fragToLight + gridSamplingDisk[i] * diskRadius, lightIndex)).r;
        closestDepth *= far_plane;// undo mapping [0;1]
        if (currentDepth - bias > closestDepth){
            shadow += 1.0;
        }
    }
    shadow /= float(samples);
    return shadow;
}

float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos, float far_plane, int lightID)
{
    vec4 fragPosLightSpace = lightSpaceMatrix * vec4( fs_in.WorldPos  , 1.0);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize( lightPos -  fs_in.WorldPos );
    float bias = max(biasMuliplayer * (1.0 - dot(normal, lightDir)), maxBias);
    // check whether current frag pos is in shadow
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(planeShadowMaps, 0).xy;
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(planeShadowMaps, vec3(projCoords.x + x * texelSize.x, projCoords.y + y * texelSize.y, lightID)).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if (projCoords.z > 1.0)
    shadow = 0.0;


    return shadow;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    // number of depth layers
    const float minLayers = 8;
    const float maxLayers = 40;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy / viewDir.z * heightScale;
    vec2 deltaTexCoords = P / numLayers;

    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue =     texture(material.depthTextureArray, vec3(currentTexCoords, currentTextures[3])).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue =     texture(material.depthTextureArray, vec3(currentTexCoords, currentTextures[3])).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth =     texture(material.depthTextureArray, vec3(prevTexCoords, currentTextures[3])).r- currentLayerDepth + layerDepth;

    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}