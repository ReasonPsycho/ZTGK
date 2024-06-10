#version 460 
layout (location = 0) out vec4 FragColor; 
layout (location = 1) out vec4 BrightColor; 
in vec2 TexCoords; 
in vec3 WorldPos; 
in vec3 Normal; 
 
// material parameters 
uniform sampler2D albedoMap; 
uniform sampler2D normalMap; 
uniform sampler2D metallicMap; 
uniform sampler2D roughnessMap; 
uniform sampler2D aoMap; 
 
// IBL 
uniform samplerCube irradianceMap; 
uniform samplerCube prefilterMap; 
uniform sampler2D brdfLUT; 
 
//Lighting and shadows 
uniform vec3 camPos; 
uniform float far_plane; 
 
#define MAX_LIGHTS 5 // IDKKKK!!!!! 
 
layout (binding = 8) uniform samplerCube cubeShadowMaps[MAX_LIGHTS]; 
layout (binding = 8 + 5) uniform sampler2D planeShadowMaps[MAX_LIGHTS]; 
 
struct DirLight { 
    vec4 color; 
    vec4 position; 
    vec4 direction; 
    mat4x4 lightSpaceMatrix; 
}; 
 
struct PointLight { 
    vec4 color; 
    vec4 position; 
 
    float constant; 
    float linear; 
    float quadratic; 
    float pointlessfloat; 
}; 
 
struct SpotLight { 
    vec4 color; 
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
 
uniform bool shadows; 
 
 
 
const float PI = 3.14159265359; 
 
// ---------------------------------------------------------------------------- 
// Shadows 
// array of offset direction for sampling 
 
 
vec3 gridSamplingDisk[20] = vec3[] 
( 
    vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), 
    vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1), 
    vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0), 
    vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1), 
    vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1) 
); 
 
float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, int lightIndex) 
{ 
    // get vector between fragment position and light position 
    vec3 fragToLight = fragPos - lightPos; 
    // use the fragment to light vector to sample from the depth map     
    // float closestDepth = texture(depthMap, fragToLight).r; 
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value 
    // closestDepth *= far_plane; 
    // now get current linear depth as the length between the fragment and light position 
    float currentDepth = length(fragToLight); 
    // test for shadows 
    // float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range 
    // float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0; 
    // PCF 
    // float shadow = 0.0; 
    // float bias = 0.05;  
    // float samples = 4.0; 
    // float offset = 0.1; 
    // for(float x = -offset; x < offset; x += offset / (samples * 0.5)) 
    // { 
    // for(float y = -offset; y < offset; y += offset / (samples * 0.5)) 
    // { 
    // for(float z = -offset; z < offset; z += offset / (samples * 0.5)) 
    // { 
    // float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r; // use lightdir to lookup cubemap 
    // closestDepth *= far_plane;   // Undo mapping [0;1] 
    // if(currentDepth - bias > closestDepth) 
    // shadow += 1.0; 
    // } 
    // } 
    // } 
    // shadow /= (samples * samples * samples); 
    float shadow = 0.0; 
    float bias = 0.15; 
    int samples = 20; 
    float viewDistance = length(camPos - fragPos); 
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0; 
    for (int i = 0; i < samples; ++i) 
    { 
        float closestDepth = texture(cubeShadowMaps[lightIndex], fragToLight + gridSamplingDisk[i] * diskRadius).r; 
        closestDepth *= far_plane;   // undo mapping [0;1] 
        if (currentDepth - bias > closestDepth) 
        shadow += 1.0; 
    } 
    shadow /= float(samples); 
 
    // display closestDepth as debug (to visualize depth cubemap) 
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);     
 
    return shadow; 
} 
 
float PlaneShadowCalculation(mat4x4 lightSpaceMatrix, vec3 lightPos, int lightID) 
{ 
    vec4 fragPosLightSpace = lightSpaceMatrix * vec4(lightPos, 1.0); 
    // perform perspective divide 
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; 
    // transform to [0,1] range 
    projCoords = projCoords * 0.5 + 0.5; 
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords) 
    float closestDepth = texture(planeShadowMaps[lightID], projCoords.xy).r; 
    // get depth of current fragment from light's perspective 
    float currentDepth = projCoords.z; 
    // calculate bias (based on depth map resolution and slope) 
    vec3 normal = normalize(Normal); 
    vec3 lightDir = normalize(lightPos - WorldPos); 
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 
    // check whether current frag pos is in shadow 
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; 
    // PCF 
    float shadow = 0.0; 
    vec2 texelSize = 1.0 / textureSize(planeShadowMaps[lightID], 0); 
    for (int x = -1; x <= 1; ++x) 
    { 
        for (int y = -1; y <= 1; ++y) 
        { 
            float pcfDepth = texture(planeShadowMaps[lightID], projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0; 
        } 
    } 
    shadow /= 9.0; 
 
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum. 
    if (projCoords.z > 1.0) 
    shadow = 0.0; 
 
    return shadow; 
} 
 
 
// ---------------------------------------------------------------------------- 
// Easy trick to get tangent-normals to world-space to keep PBR code simplified. 
// Don't worry if you don't get what's going on; you generally want to do normal  
// mapping the usual way for performance anyways; I do plan make a note of this  
// technique somewhere later in the normal mapping tutorial. 
vec3 getNormalFromMap() 
{ 
    vec3 tangentNormal = texture(normalMap, TexCoords).xyz * 2.0 - 1.0; 
 
    vec3 Q1 = dFdx(WorldPos); 
    vec3 Q2 = dFdy(WorldPos); 
    vec2 st1 = dFdx(TexCoords); 
    vec2 st2 = dFdy(TexCoords); 
 
    vec3 N = normalize(Normal); 
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t); 
    vec3 B = -normalize(cross(N, T)); 
    mat3 TBN = mat3(T, B, N); 
 
    return normalize(TBN * tangentNormal); 
} 
// ---------------------------------------------------------------------------- 
float DistributionGGX(vec3 N, vec3 H, float roughness) 
{ 
    float a = roughness * roughness; 
    float a2 = a * a; 
    float NdotH = max(dot(N, H), 0.0); 
    float NdotH2 = NdotH * NdotH; 
 
    float nom = a2; 
    float denom = (NdotH2 * (a2 - 1.0) + 1.0); 
    denom = PI * denom * denom; 
 
    return nom / denom; 
} 
// ---------------------------------------------------------------------------- 
float GeometrySchlickGGX(float NdotV, float roughness) 
{ 
    float r = (roughness + 1.0); 
    float k = (r * r) / 8.0; 
 
    float nom = NdotV; 
    float denom = NdotV * (1.0 - k) + k; 
 
    return nom / denom; 
} 
// ---------------------------------------------------------------------------- 
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) 
{ 
    float NdotV = max(dot(N, V), 0.0); 
    float NdotL = max(dot(N, L), 0.0); 
    float ggx2 = GeometrySchlickGGX(NdotV, roughness); 
    float ggx1 = GeometrySchlickGGX(NdotL, roughness); 
 
    return ggx1 * ggx2; 
} 
// ---------------------------------------------------------------------------- 
vec3 fresnelSchlick(float cosTheta, vec3 F0) 
{ 
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0); 
} 
// ---------------------------------------------------------------------------- 
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) 
{ 
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0); 
} 
// ---------------------------------------------------------------------------- 
 
//Lights calculation 
 
// calculates the color when using a directional light. 
vec3 CalcDirLight(DirLight light, vec3 N, vec3 V, float roughness, float metallic, vec3 albedo, vec3 F0, int lightIndex) 
{ 
    // calculate per-light radiance 
    vec3 L = normalize(-light.direction.xyz); 
    vec3 H = normalize(V + L); 
    vec3 radiance = light.color.xyz * light.color.w; 
 
    // Cook-Torrance BRDF 
    float NDF = DistributionGGX(N, H, roughness); 
    float G = GeometrySmith(N, V, L, roughness); 
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0); 
 
    vec3 numerator = NDF * G * F; 
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;// + 0.0001 to prevent divide by zero 
    vec3 specular = numerator / denominator; 
 
    // kS is equal to Fresnel 
    vec3 kS = F; 
    // for energy conservation, the diffuse and specular light can't 
    // be above 1.0 (unless the surface emits light); to preserve this 
    // relationship the diffuse component (kD) should equal 1.0 - kS. 
    vec3 kD = vec3(1.0) - kS; 
    // multiply kD by the inverse metalness such that only non-metals  
    // have diffuse lighting, or a linear blend if partly metal (pure metals 
    // have no diffuse light). 
    kD *= 1.0 - metallic; 
 
    // scale light by NdotL 
    float NdotL = max(dot(N, L), 0.0); 
 
    float shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, lightIndex)); 
 
 
    // add to outgoing radiance Lo 
    return (kD * albedo / PI + specular) * radiance * NdotL * shadow;// note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again 
} 
 
 
// calculates the color when using a point light. 
vec3 CalcPointLight(PointLight light, vec3 N, vec3 V, float roughness, float metallic, vec3 albedo, vec3 F0, int lightIndex) 
{ 
    // calculate per-light radiance 
    vec3 L = normalize(light.position.xyz - WorldPos); 
    vec3 H = normalize(V + L); 
    float distance = length(light.position.xyz - WorldPos); 
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    vec3 radiance = light.color.xyz * attenuation * light.color.w; 
 
    // Cook-Torrance BRDF 
    float NDF = DistributionGGX(N, H, roughness); 
    float G = GeometrySmith(N, V, L, roughness); 
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0); 
 
    vec3 numerator = NDF * G * F; 
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero 
    vec3 specular = numerator / denominator; 
 
    // kS is equal to Fresnel 
    vec3 kS = F; 
    // for energy conservation, the diffuse and specular light can't 
    // be above 1.0 (unless the surface emits light); to preserve this 
    // relationship the diffuse component (kD) should equal 1.0 - kS. 
    vec3 kD = vec3(1.0) - kS; 
    // multiply kD by the inverse metalness such that only non-metals  
    // have diffuse lighting, or a linear blend if partly metal (pure metals 
    // have no diffuse light). 
    kD *= 1.0 - metallic; 
 
    // scale light by NdotL 
    float NdotL = max(dot(N, L), 0.0); 
    float shadow = (1.0 - CubeShadowCalculation(WorldPos, light.position.xyz, lightIndex)); 
    // add to outgoing radiance Lo 
    return (kD * albedo / PI + specular) * radiance * NdotL * shadow; // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again 
 
} 
// calculates the color when using a spot light. 
vec3 CalcSpotLight(SpotLight light, vec3 N, vec3 V, float roughness, float metallic, vec3 albedo, vec3 F0, int lightIndex) 
{ 
    // calculate per-light radiance 
    vec3 L = normalize(-light.direction.xyz); 
    vec3 H = normalize(V + L); 
    float distance = length(light.position.xyz - WorldPos); 
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
 
    float theta = dot(L, normalize(-light.direction.xyz)); 
    float epsilon = light.cutOff - light.outerCutOff; 
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
 
    vec3 radiance = light.color.xyz * attenuation * light.color.w; 
 
 
    // Cook-Torrance BRDF 
    float NDF = DistributionGGX(N, H, roughness); 
    float G = GeometrySmith(N, V, L, roughness); 
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0); 
 
    vec3 numerator = NDF * G * F; 
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero 
    vec3 specular = numerator / denominator; 
 
    // kS is equal to Fresnel 
    vec3 kS = F; 
    // for energy conservation, the diffuse and specular light can't 
    // be above 1.0 (unless the surface emits light); to preserve this 
    // relationship the diffuse component (kD) should equal 1.0 - kS. 
    vec3 kD = vec3(1.0) - kS; 
    // multiply kD by the inverse metalness such that only non-metals  
    // have diffuse lighting, or a linear blend if partly metal (pure metals 
    // have no diffuse light). 
    kD *= 1.0 - metallic; 
 
    // scale light by NdotL 
    float NdotL = max(dot(N, L), 0.0); 
    float shadow = (1.0 - PlaneShadowCalculation(light.lightSpaceMatrix, light.position.xyz, lightIndex)); 
 
    // add to outgoing radiance Lo 
    return (kD * albedo / PI + specular) * radiance * NdotL * shadow; // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again 
} 
 
 
void main() 
{ 
    // material properties 
    vec3 albedo = pow(texture(albedoMap, TexCoords).rgb, vec3(2.2)); 
    float metallic = texture(metallicMap, TexCoords).r; 
    float roughness = texture(roughnessMap, TexCoords).r; 
    float ao = texture(aoMap, TexCoords).r; 
 
    // input lighting data 
    vec3 N = getNormalFromMap(); 
    vec3 V = normalize(camPos - WorldPos); 
    vec3 R = reflect(-V, N); 
 
    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0  
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)     
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic); 
 
    // reflectance equation 
    vec3 Lo = vec3(0.0); 
    int planeLightIndex = 0; 
    int cubeLightIndex = 0; 
 
    for (int i = 0; i < dirLights.length(); ++i) { 
        Lo += CalcDirLight(dirLights[i], N, V, roughness, metallic, albedo, F0, planeLightIndex++); 
    } 
    for (int i = 0; i < pointLights.length(); ++i) { 
        Lo += CalcPointLight(pointLights[i], N, V, roughness, metallic, albedo, F0, cubeLightIndex++); 
    } 
    for (int i = 0; i < spotLights.length(); ++i) { 
 
        Lo += CalcSpotLight(spotLights[i], N, V, roughness, metallic, albedo, F0, planeLightIndex++); 
    } 
 
    // ambient lighting (we now use IBL as the ambient term) 
    vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness); 
 
    vec3 kS = F; 
    vec3 kD = 1.0 - kS; 
    kD *= 1.0 - metallic; 
 
    vec3 irradiance = texture(irradianceMap, N).rgb; 
    vec3 diffuse = irradiance * albedo; 
 
    // sample both the pre-filter map and the BRDF lut and combine them together as per the Split-Sum approximation to get the IBL specular part. 
    const float MAX_REFLECTION_LOD = 4.0; 
    vec3 prefilteredColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb; 
    vec2 brdf = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg; 
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y); 
 
    vec3 ambient = (kD * diffuse + specular) * ao; 
 
    vec3 color = ambient + Lo; 
 
 
    float brightness = dot(color, vec3(0.5, 0.5, 0.5)); 
    if (brightness > 1.0) { 
        BrightColor = vec4(color, 1.0); 
    } 
    else { 
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0); 
    } 
 
 
    // HDR tonemapping 
    // color = color / (color + vec3(1.0)); //Todo exposure 
    // gamma correct 
    // color = pow(color, vec3(1.0 / 2.2));  // Todo gamma 
 
    FragColor = vec4(color, 1.0); 
} 
