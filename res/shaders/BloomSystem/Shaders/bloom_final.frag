#version 330 core 
out vec4 FragColor; 
 
in vec2 TexCoords; 
 
uniform sampler2D scene; 
uniform sampler2D bloomBlur; 
uniform bool bloom; // IDK why it's here since we almost aleways gonna aplay it. 
uniform float exposure; 
 
void main() 
{ 
    const float gamma = 2.2; 
    vec3 hdrColor = texture(scene, TexCoords).rgb; 
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb; 
    if (bloom) { 
        hdrColor += bloomColor; // additive blending 
    } 
 
    //hdrColor = hdrColor / (hdrColor + vec3(1.0)); 
    //hdrColor = pow(hdrColor, vec3(1.0/2.2)); 
 
    FragColor = vec4(hdrColor, 1.0); 
} 
