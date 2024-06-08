#version 460
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 frag_normal_depth; //Meant for outline process
layout (location = 2) out vec4 BloomBuffer; //Meant for outline process

struct TangentData{ // So it's easier to operate on
    vec3 ViewPos;
    vec3 FragPos;
    mat3 TBN;//No light position but TBN since fuck transporting 20 lights pos that are allready in SSBO
};


in VS_OUT {
     vec2 TexCoords;
     vec3 WorldPos;
    vec3 LocalPos;
     vec3 Normal;
     TangentData tangentData;
}fs_in;

struct Material {
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    sampler2D normalTexture;
    sampler2D depthTexture;
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

uniform float dirtLevel;
uniform bool isInFogOfWar;

uniform float ambient;

uniform vec4 colorMask;

uniform bool outlineMapping;


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

// function prototypes

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular);
float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, float far_plane, int lightIndex);
float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos, int lightID);
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

vec4 alpha_blend(vec4 top, vec4 bottom)
{
    vec3  color = (top.rgb * top.a) + (bottom.rgb * (1 - top.a));
    float alpha = top.a + bottom.a * (1 - top.a);

    return vec4(color, alpha);
}

void main()
{
    vec2 texCoords = fs_in.TexCoords;
    vec3 viewDir = normalize(fs_in.tangentData.ViewPos - fs_in.tangentData.FragPos);

    texCoords = ParallaxMapping(fs_in.TexCoords,  viewDir);
    if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
    discard;

    float dirtinessMap  =  1 *  cnoise(fs_in.LocalPos*2) +
    +  0.5 * cnoise(fs_in.LocalPos*4) +
    + 0.25 * cnoise(fs_in.LocalPos*8);
    dirtinessMap = dirtinessMap / (1 + 0.5 + 0.25);
    dirtinessMap = pow(dirtinessMap, dirtLevel * 4);
    //dirtinessMap = (dirtinessMap + 1) * 0.5; // Scale the noise from -1.0 - 1.0 to 0.0 - 1.0
    dirtinessMap = 1.0 - dirtinessMap; // Invert the noise map
    // dirtinessMap +=  * 1; //TODO here just put how clean it is ^^

    dirtinessMap -= (1 - texture(material.depthTexture, fs_in.TexCoords).r) *  0.8;
    texCoords = ParallaxMapping(texCoords,  viewDir);
    dirtinessMap = ceil(dirtinessMap * diffuse_levels ) / diffuse_levels;
    
    vec3 normal = fs_in.Normal;
    if(useNormalMap){
        normal = texture(material.diffuseTexture, texCoords).rgb;
        normal = normalize(normal * 2.0  - 1);
    }

    vec3 diffuse = vec3(texture(material.diffuseTexture, texCoords));
    vec3 specular = vec3(texture(material.specularTexture, texCoords));
    
    if(dirtinessMap > 0.1){
        diffuse -= vec3(dirtinessMap) * 0.5;
        specular -= vec3(dirtinessMap)* 0.5;
    }
    
    vec3 result = ambient * diffuse; //We do be calculating ambient here
    int index = 0;
    for (int i = 0; i < dirLightAmount; ++i) {
        result += CalcDirLight(dirLights[i], normal, viewDir, index++,  diffuse,specular);
    }

    for (int i = 0; i < spotLightAmount; ++i) {
        result += CalcSpotLight(spotLights[i], normal, fs_in.WorldPos, viewDir, index++, diffuse,specular);
    }

    index = 0;
    for (int i = 0; i < pointLightAmount; ++i) {
        result += CalcPointLight(pointLights[i], normal, fs_in.WorldPos, viewDir, index++,  diffuse,specular);
    }
    
    result = mix(result,vec3(colorMask),colorMask.a);
    
    FragColor = vec4(result, 1.0);

    if(outlineMapping){
        float depth = gl_FragCoord.z;
        frag_normal_depth = vec4(normal, depth);
    }

    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    
    if(brightness > 1.0)
       BloomBuffer = vec4(FragColor.rgb, 1.0);
    else
        BloomBuffer = vec4(0.0, 0.0, 0.0, 1.0);
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
    vec3 diffuse_color = vec3(light.diffuse) * diff * diffuse;
    vec3 specular_color = vec3(light.specular) * spec * specular;

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, lightIndex));
    
    return (diffuse_color + specular_color) * shadow;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular)
{
    vec3 lightDir = normalize(vec3(light.position)  - worldPos);
    vec3 half_vector = normalize(viewDir - lightDir);

    // attenuation
    float distance = length(vec3(light.position)  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


    // diffuse shading
    float df = max(0.0, dot(normal, lightDir));
    // specular shading
    float sf = max(0.0, dot(normal, half_vector)) * attenuation;


    /* Calculate rim lighting */
    float rim_dot       = 1.0 - max(dot(viewDir, normal), 0.0);
    float rim_intensity = rim_dot * pow(df, rim_threshold);
    rim_intensity = smoothstep(rim_amount - 0.01, rim_amount + 0.01, rim_intensity);
    vec3  rim           = rim_intensity * vec3(light.specular);

    df*= attenuation;

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
    vec3 specular_color =  vec3(light.specular) * diff_color_modulation *specular;
    
    float shadow = 1;
    shadow = (1.0 - CubeShadowCalculation(fs_in.WorldPos, light.position.xyz,light.position.w, lightIndex));


    return (df * diffuse_color + sf * specular_color + rim) * shadow; //Prob also need to style shadow or just use hard ones
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 worldPos, vec3 viewDir, int lightIndex,vec3 diffuse,vec3 specular)
{
    vec3 lightDir = normalize(vec3(light.position)  - worldPos);
    vec3 half_vector = normalize(viewDir - lightDir);

    // attenuation
    float distance = length(vec3(light.position)  - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // spotlight intensity
    float theta = dot(lightDir, normalize(vec3(-light.direction)));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
        // diffuse shading
    float df = max(0.0, dot(normal, lightDir));
    // specular shading
    float sf = max(0.0, dot(normal, half_vector)) * attenuation * intensity;

    /* Calculate rim lighting */
    float rim_dot       = 1.0 - max(dot(viewDir, normal), 0.0);
    float rim_intensity = rim_dot * pow(df, rim_threshold);
    rim_intensity = smoothstep(rim_amount - 0.01, rim_amount + 0.01, rim_intensity);
    vec3  rim           = rim_intensity * vec3(light.specular);
    
    df *=  attenuation * intensity;

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
    vec3 specular_color =  vec3(light.specular) * diff_color_modulation *specular;

    float shadow = 1;
    shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, lightIndex));
    
    
    return (df * diffuse_color + sf * specular_color + rim) * shadow; //Prob also need to style shadow or just use hard ones
}

float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, float far_plane, int lightIndex)
{
    vec3 fragToLight = fs_in.WorldPos - lightPos;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias = 0.05;
    int samples = 20;
    float viewDistance = length(camPos - fs_in.WorldPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for (int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(cubeShadowMaps, vec4(fragToLight + gridSamplingDisk[i] * diskRadius, lightIndex)).r;      
        closestDepth *= far_plane;   // undo mapping [0;1]
        if (currentDepth - bias > closestDepth){
            shadow += 1.0;
        }
    }
    shadow /= float(samples);
    return shadow;
}

float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos, int lightID)
{
    vec4 fragPosLightSpace = lightSpaceMatrix * vec4(fs_in.WorldPos, 1.0);
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(planeShadowMaps, vec3(projCoords.xy, lightID)).r;    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)

    vec3 normal = normalize( vec3(texture(material.normalTexture, fs_in.TexCoords)));
    vec3 lightDir = normalize(lightPos - fs_in.WorldPos);
    float bias = max(0.00001 * (1.0 - dot(normal, lightDir)),  0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(planeShadowMaps, 0).xy;
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(planeShadowMaps, vec3(projCoords.xy + vec2(x, y) * texelSize, lightID)).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if (projCoords.z > 1.0){
        shadow = 1.0;
    }

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
    float currentDepthMapValue = texture(material.depthTexture, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(material.depthTexture, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }

    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(material.depthTexture, prevTexCoords).r - currentLayerDepth + layerDepth;

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