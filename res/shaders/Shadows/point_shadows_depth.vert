#version 330 core 
layout (location = 0) in vec3 aPos; 
 
uniform mat4 model; 
uniform mat4 shadowMatrice; 
uniform vec3 lightPos; 
out vec4 FragPos; // Send position to next stage 
 
void main() 
{ 
    vec4 pos = model * vec4(aPos, 1.0); 
    gl_Position = shadowMatrice * pos; 
    FragPos = pos; 
} 
