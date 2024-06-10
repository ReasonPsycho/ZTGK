#version 330 core 
in vec4 FragPos; 
 
uniform vec3 lightPos; 
uniform float far_plane; 
 
void main() 
{ 
    // write this as modified depth 
    gl_FragDepth = (length ( FragPos.xyz -lightPos)/ far_plane) + 0.01 ; 
} 
