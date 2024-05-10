#version 460
out vec4 FragColor;


in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 WorldPos;
    vec3 Normal;
    flat int textureType;
    flat bool inFogOfWar;
    flat int typeOfSelection;
    flat int CheckVector2Int;
}vs_out;




struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D shininess;
    sampler2D normal;//TODO use it somwhere lol
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

uniform vec3 viewPos;
uniform Material material;

//Lighting and shadows
uniform vec3 camPos;
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


layout (binding = 8) uniform samplerCubeArray cubeShadowMaps;
layout (binding = 9) uniform sampler2DArray planeShadowMaps;
layout (binding = 10) uniform sampler2DArray diffuseTextureArray;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, int lightIndex);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex);
float CubeShadowCalculation(vec3 fragPos, vec3 lightPos ,float far_plane, int lightIndex);
float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos,float far_plane, int lightID);

void main()
{
    // properties
    vec3 norm =  vs_out.Normal;
    vec3 viewDir = normalize(viewPos - vs_out.FragPos);

    vec3 result = vec3(0);
    if (!vs_out.inFogOfWar){

        result = 0.2f * vec3(texture(diffuseTextureArray, vec3(vs_out.TexCoords, float(vs_out.textureType))));//We do be calculating ambient here
        int index = 0;
        for (int i = 0; i < dirLights.length(); ++i) {
            result += CalcDirLight(dirLights[i], norm, viewDir, index++);
        }

        for (int i = 0; i < spotLights.length(); ++i) {
            result += CalcSpotLight(spotLights[i], norm, vs_out.WorldPos, viewDir, index++);
        }

        index = 0;
        for (int i = 0; i < pointLights.length(); ++i) {
            result += CalcPointLight(pointLights[i], norm, vs_out.WorldPos, viewDir, index++);
        }

    }
    else {

        result = vec3(0.5, 0.5, 0.5);
    }

    if(vs_out.typeOfSelection != 0){
        result = mix(result, selectionColor[vs_out.typeOfSelection], 0.5);
    }
    
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, int lightIndex)
{
    vec3 lightDir = normalize(vec3(-light.direction));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
    // combine results
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(diffuseTextureArray, vec3(vs_out.TexCoords, float(vs_out.textureType))));
    vec3 specular = vec3(light.specular) * spec * vec3(texture(material.specular, vs_out.TexCoords));

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz,light.position.w, lightIndex));

    return (diffuse + specular) * shadow;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex)
{
    vec3 lightDir = normalize(vec3(light.position)  - worldPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
    // attenuation
    float distance = length(vec3(light.position)  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(diffuseTextureArray, vec3(vs_out.TexCoords, float(vs_out.textureType))));
    vec3 specular =  vec3(light.specular) * spec * vec3(texture(material.specular, vs_out.TexCoords));
    diffuse *= attenuation;
    specular *= attenuation;

    float shadow = 1;
    shadow = (1.0 - CubeShadowCalculation(vs_out.WorldPos, light.position.xyz, light.position.w, lightIndex));


    return (diffuse + specular) * shadow;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex)
{
    vec3 lightDir = normalize(vec3(light.position) - worldPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
    // attenuation
    float distance = length(vec3(light.position)  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(vec3(-light.direction)));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(diffuseTextureArray, vec3(vs_out.TexCoords, float(vs_out.textureType))));
    vec3 specular =  vec3(light.specular) * spec * vec3(texture(material.specular, vs_out.TexCoords));
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz,light.position.w, lightIndex));


    return (diffuse + specular) * shadow;
}

float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, float far_plane, int lightIndex)
{
    vec3 fragToLight = vs_out.WorldPos - lightPos;
    float currentDepth = length(fragToLight) ;
    float shadow = 0.0;
    float bias = 0.05;
    int samples = 20;
    float viewDistance = length(camPos - vs_out.WorldPos);
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

float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos,float far_plane, int lightID)
{
    vec4 fragPosLightSpace = lightSpaceMatrix * vec4(vs_out.WorldPos, 1.0);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize( vs_out.Normal);
    vec3 lightDir = normalize(lightPos - vs_out.WorldPos);
    float bias = max(biasMuliplayer * (1.0 - dot(normal, lightDir)),  maxBias);
    // check whether current frag pos is in shadow
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(planeShadowMaps, 0).xy;
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(planeShadowMaps, vec3(projCoords.x + x * texelSize.x,projCoords.y + y * texelSize.y, lightID)).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;


    return shadow;
}
