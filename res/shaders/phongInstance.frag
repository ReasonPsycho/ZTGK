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
uniform float saturationMultiplayer;  // sat multiplier is the factor by which you increase saturation.
uniform float lightMultiplayer;  // sat multiplier is the factor by which you increase saturation
uniform int toon_color_levels;

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
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular);
float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, float far_plane, int lightIndex);
float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos, float far_plane, int lightID);
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);
vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}
vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}
vec3 fade(vec3 t) {return t*t*t*(t*(t*6.0-15.0)+10.0);}
float cnoise(vec3 P);
vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

out vec4 FragColor;


const mat4 light_shade_mat = mat4( 251, 166, 10,  165,
142, 9,   212, 250,
7,   165, 250, 168,
220, 250, 142, 4 ) / 255.0;

vec3 light_shade_color()
{
    ivec2 gridPos = ivec2(gl_FragCoord) % 4;
    float factor  = light_shade_mat[gridPos.x][3 - gridPos.y];

    return vec3(factor);
}

const mat4 dark_shade_mat = mat4( 251, 166, 10,  165,
142, 9,   212, 8,
7,   165, 250, 168,
220, 8,   142, 4 ) / 255.0;

vec3 dark_shade_color()
{
    ivec2 gridPos = ivec2(gl_FragCoord) % 4;
    float factor  = dark_shade_mat[gridPos.x][3 - gridPos.y];

    return vec3(factor);
}

vec4 reinhard(vec4 hdr_color)
{
    // reinhard tonemapping
    vec3 ldr_color = hdr_color.rgb / (hdr_color.rgb + 1.0);

    // gamma correction
    ldr_color = pow(ldr_color, vec3(1.0 / 2.2)); //Gamma

    return vec4(ldr_color, 1.0);
}

uniform float diffuse_levels;
uniform float specular_levels;
uniform float light_shade_cutoff;
uniform float dark_shade_cutoff;


void main()
{
    vec2 texCoords = fs_in.TexCoords;
    vec3 viewDir = normalize(fs_in.tangentData.ViewPos - fs_in.tangentData.FragPos);

    float dirtinessMap  =  1 *  cnoise(fs_in.WorldPos*2) +
    +  0.5 * cnoise(fs_in.WorldPos*4) +
    + 0.25 * cnoise(fs_in.WorldPos*8);
    dirtinessMap = dirtinessMap / (1 + 0.5 + 0.25);
    dirtinessMap = pow(dirtinessMap, currentWallData[0]/100.0 * 4);
    //dirtinessMap = (dirtinessMap + 1) * 0.5; // Scale the noise from -1.0 - 1.0 to 0.0 - 1.0
    dirtinessMap = 1.0 - dirtinessMap; // Invert the noise map
   // dirtinessMap +=  * 1; //TODO here just put how clean it is ^^
    
    dirtinessMap -= (1 - texture(material.depthTextureArray, vec3( fs_in.TexCoords, currentTextures[3])).r) *  0.8;
    texCoords = ParallaxMapping(texCoords,  viewDir);
 

    
    // properties
    // obtain normal from normal map
    vec3 normal = texture(material.normalTextureArray, vec3(texCoords,currentTextures[2])).rgb;
    normal = normalize(normal * 2.0 - 1);



    
    vec3 diffuse = vec3(texture(material.diffuseTextureArray, vec3(texCoords, float(currentTextures[0]))));

    vec3 specular = vec3(texture(material.specularTextureArray, vec3(texCoords,float(currentTextures[1]))));


    if(dirtinessMap > 0.1){
        diffuse -= vec3(dirtinessMap);
        specular -= vec3(dirtinessMap);
    }
    
    vec3 result = vec3(0);
    if (currentWallData[1] != 1){

        result = 0.1f * diffuse;//We do be calculating ambient here
        int index = 0;
        for (int i = 0; i < dirLightAmount; ++i) {
            result += CalcDirLight(dirLights[i], normal, viewDir, index++,  diffuse,specular);
        }

        for (int i = 0; i < spotLightAmount; ++i) {
            result += CalcSpotLight(spotLights[i], normal, fs_in.tangentData.FragPos, viewDir, index++, diffuse,specular);
        }

        index = 0;
        for (int i = 0; i < pointLightAmount; ++i) {
            result += CalcPointLight(pointLights[i], normal, fs_in.tangentData.FragPos, viewDir, index++,  diffuse,specular);
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
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular)
{
    vec3 lightDir = normalize(vec3(-light.direction));
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0);
    // combine results
     diffuse = vec3(light.diffuse) * diff * diffuse;
    specular = vec3(light.specular) * spec * vec3(specular);

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, light.position.w, lightIndex));

    return (diffuse + specular) * shadow;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular)
{
    vec3 lightDir = normalize(  vec3(fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    vec3 half_vector = normalize(viewDir - lightDir);

    // attenuation
    float distance = length(vec3( fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // diffuse shading
    float df = max(0.0, dot(normal, lightDir)) *attenuation;
    // specular shading
    float sf = max(0.0, dot(normal, half_vector)) * attenuation;

    //flooring
    df = ceil(df * diffuse_levels ) / diffuse_levels;
    sf = floor((sf * specular_levels ) + 0.5) / specular_levels;

    //color modulation
    vec3 diff_color_modulation;

    if (df >= light_shade_cutoff)
    {
        diff_color_modulation = vec3(1.0);
    }
    else if (df >= dark_shade_cutoff)
    {
        diff_color_modulation = light_shade_color();
    }
    else
    {
        diff_color_modulation = dark_shade_color();
    }

    vec3 diffuse_color = vec3(light.diffuse) * diff_color_modulation * diffuse;
    vec3 specular_color =  vec3(light.specular) * diff_color_modulation * specular;

    float shadow = 1;
    shadow = (1.0 - CubeShadowCalculation(fs_in.WorldPos, light.position.xyz, light.position.w, lightIndex));

    return (df * diffuse_color + sf * specular_color) * shadow; //Prob also need to style shadow or just use hard ones
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular)
{
    vec3 tangentLightDir = normalize(  vec3(fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    vec3 lightDir = normalize(   vec3(light.position)  - fs_in.WorldPos);
    vec3 half_vector = normalize(viewDir - tangentLightDir);

    // attenuation
    float distance = length(vec3( fs_in.tangentData.TBN * vec3(light.position))  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // spotlight intensity
    float theta = dot(lightDir, normalize(vec3(-light.direction)));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);


    // diffuse shading
    float df = max(0.0, dot(normal, tangentLightDir)) *attenuation * intensity;
    // specular shading
    float sf = max(0.0, dot(normal, half_vector)) * attenuation * intensity;
    
    //flooring
    df = ceil(df * diffuse_levels) / diffuse_levels;
    sf = floor((sf * specular_levels ) + 0.5) / specular_levels;

    //color modulation
    vec3 diff_color_modulation;

    if (df >= light_shade_cutoff)
    {
        diff_color_modulation = vec3(1.0);
    }
    else if (df >= dark_shade_cutoff)
    {
        diff_color_modulation = light_shade_color();
    }
    else
    {
        diff_color_modulation = dark_shade_color();
    }

    vec3 diffuse_color = vec3(light.diffuse) * diff_color_modulation * diffuse;
    vec3 specular_color =  vec3(light.specular) * diff_color_modulation * specular;

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, light.position.w, lightIndex));

    return (df * diffuse_color + sf * specular_color) * shadow; //Prob also need to style shadow or just use hard ones
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

float cnoise(vec3 P){
    vec3 Pi0 = floor(P); // Integer part for indexing
    vec3 Pi1 = Pi0 + vec3(1.0); // Integer part + 1
    Pi0 = mod(Pi0, 289.0);
    Pi1 = mod(Pi1, 289.0);
    vec3 Pf0 = fract(P); // Fractional part for interpolation
    vec3 Pf1 = Pf0 - vec3(1.0); // Fractional part - 1.0
    vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
    vec4 iy = vec4(Pi0.yy, Pi1.yy);
    vec4 iz0 = Pi0.zzzz;
    vec4 iz1 = Pi1.zzzz;

    vec4 ixy = permute(permute(ix) + iy);
    vec4 ixy0 = permute(ixy + iz0);
    vec4 ixy1 = permute(ixy + iz1);

    vec4 gx0 = ixy0 / 7.0;
    vec4 gy0 = fract(floor(gx0) / 7.0) - 0.5;
    gx0 = fract(gx0);
    vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);
    vec4 sz0 = step(gz0, vec4(0.0));
    gx0 -= sz0 * (step(0.0, gx0) - 0.5);
    gy0 -= sz0 * (step(0.0, gy0) - 0.5);

    vec4 gx1 = ixy1 / 7.0;
    vec4 gy1 = fract(floor(gx1) / 7.0) - 0.5;
    gx1 = fract(gx1);
    vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);
    vec4 sz1 = step(gz1, vec4(0.0));
    gx1 -= sz1 * (step(0.0, gx1) - 0.5);
    gy1 -= sz1 * (step(0.0, gy1) - 0.5);

    vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
    vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
    vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
    vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
    vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
    vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
    vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
    vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);

    vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
    g000 *= norm0.x;
    g010 *= norm0.y;
    g100 *= norm0.z;
    g110 *= norm0.w;
    vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
    g001 *= norm1.x;
    g011 *= norm1.y;
    g101 *= norm1.z;
    g111 *= norm1.w;

    float n000 = dot(g000, Pf0);
    float n100 = dot(g100, vec3(Pf1.x, Pf0.yz));
    float n010 = dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));
    float n110 = dot(g110, vec3(Pf1.xy, Pf0.z));
    float n001 = dot(g001, vec3(Pf0.xy, Pf1.z));
    float n101 = dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));
    float n011 = dot(g011, vec3(Pf0.x, Pf1.yz));
    float n111 = dot(g111, Pf1);

    vec3 fade_xyz = fade(Pf0);
    vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
    vec2 n_yz = mix(n_z.xy, n_z.zw, fade_xyz.y);
    float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x);
    return 2.2 * n_xyz;
}