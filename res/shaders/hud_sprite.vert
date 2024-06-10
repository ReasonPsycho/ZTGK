#version 330 
 
layout (location = 0) in vec2 pos; 
layout (location = 1) in vec2 texPos; 
 
uniform mat4 projection; 
 
out vec2 texCoord; 
 
void main() { 
    gl_Position = projection * vec4(pos, 0.0, 1.0); 
    texCoord = texPos; 
} 
