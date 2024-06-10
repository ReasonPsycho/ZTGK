#version 330 
 
in vec2 texCoord; 
uniform vec4 inColor; 
uniform sampler2D tex; 
uniform bool hasTex; 
 
out vec4 color; 
 
void main() { 
    if (hasTex) color = texture(tex, texCoord) * inColor; 
    else color = inColor; 
} 
