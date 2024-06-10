#version 460 
 
 
in vec4 boxColor; 
out vec4 FragColor; 
 
void main() 
{ 
   FragColor = vec4( vec3(boxColor),0.6); 
} 
