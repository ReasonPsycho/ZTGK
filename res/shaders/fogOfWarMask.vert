#version 460 
 
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTexCoords; 
 
 
uniform mat4 projection; 
uniform mat4 view; 
uniform mat4 gridMatrix; 
uniform vec3 camPos; 
 
struct WallData 
{ 
    mat4x4 matrix; 
    int[4] data; 
    int[4] textures; 
}; 
 
layout (std430, binding = 6) buffer WallDataBuffer { 
    WallData wallData[]; // Array of velocities 
}; 
 
 
 
 
out VS_OUT { 
    vec2 TexCoords; 
    vec3 WorldPos; 
    vec3 ViewPos; 
    vec3 Normal; 
}vs_out; 
 
out flat int[4] currentWallData; 
out flat int[4] currentTextures; 
 
void main() 
{ 
    //Instance shader set up 
    uint index = gl_InstanceID; 
    mat4 model = wallData[index].matrix; //So it's universal beetween instance and normal shader 
     
    //Standard calculation 
     
    vs_out.TexCoords = aTexCoords; 
    vs_out.WorldPos = vec3(model* vec4(aPos, 1.0) * gridMatrix); 
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal; 
    vs_out.ViewPos = camPos; 
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0); 
     
 
    // "My special dataTM" calculation 
    currentWallData = wallData[index].data; 
    currentTextures = wallData[index].textures; 
} 
