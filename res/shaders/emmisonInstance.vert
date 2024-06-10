#version 460 
 
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTexCoords; 
 
out VS_OUT { 
    vec2 TexCoords; 
    vec3 Normal; 
    vec3 WorldPos; 
    vec3 ViewPos; 
}vs_out; 
 
uniform mat4 projection; 
uniform mat4 view; 
uniform vec3 camPos; 
 
 
uniform int spotLightAmount; 
uniform int dirLightAmount; 
uniform int pointLightAmount; 
 
flat out vec4 specularData; 
flat out vec4 diffuseData; 
 
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
 
void main() 
{ 
 
    //Instance shader set up 
    uint index = gl_InstanceID; 
    uint currentIndex = 0; 
    mat4 model = mat4(1); //So it's universal beetween instance and normal shader 
    vec3 billboard_position = vec3(0); 
 
    float scale = 0.5; // Change this value to the desired scale factor 
    mat4 scaleMatrix = mat4( 
    vec4(scale, 0.0, 0.0, 0.0), 
    vec4(0.0, scale, 0.0, 0.0), 
    vec4(0.0, 0.0, scale, 0.0), 
    vec4(0.0, 0.0, 0.0, 1.0) 
    ); 
     
    if(index < dirLightAmount){  
        diffuseData = dirLights[index].diffuse; 
      specularData = dirLights[index].specular; 
    }else if(index - dirLightAmount < spotLightAmount){ 
        currentIndex = index - dirLightAmount; 
        diffuseData = spotLights[currentIndex].diffuse; 
        specularData = spotLights[currentIndex].specular; 
        billboard_position = vec3(spotLights[currentIndex].position); 
    }else{ 
        currentIndex = index - dirLightAmount - spotLightAmount; 
        diffuseData = pointLights[currentIndex].diffuse; 
        specularData = pointLights[currentIndex].specular; 
        billboard_position = vec3(pointLights[currentIndex].position); 
    } 
 
    vec3 look = normalize(camPos - billboard_position); 
    vec3 up = vec3(0.0, 1.0, 0.0); 
    vec3 right = cross(up, look); 
 
    // Build the billboard's model matrix 
    model[0] = vec4(right, 0.0); 
    model[1] = vec4(up, 0.0); 
    model[2] = vec4(look, 0.0); 
    model[3] = vec4(billboard_position, 1.0); 
 
    model*= scaleMatrix; 
     
    //Standard calculation 
    vs_out.TexCoords = aTexCoords; 
    vs_out.WorldPos = vec3(model* vec4(aPos, 1.0)); 
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal; 
    vs_out.ViewPos = camPos; 
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0); 
} 
