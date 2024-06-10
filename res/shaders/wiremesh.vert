#version 460 
 
layout (location = 0) in vec3 aPos; 
struct BoxColliderData 
{ 
   mat4x4 matrix; 
   vec4 color; 
}; 
 
out vec4 boxColor; 
 
layout (std430, binding = 7) buffer BoxColliderDataBuffer { 
   BoxColliderData boxColliderData[]; // Array of velocities 
}; 
 
uniform mat4 projection; 
uniform mat4 view; 
 
void main() 
{ 
   int index = gl_InstanceID; 
   boxColor =  boxColliderData[index].color; 
   gl_Position = projection * view * boxColliderData[index].matrix * vec4(aPos, 1.0); 
} 
