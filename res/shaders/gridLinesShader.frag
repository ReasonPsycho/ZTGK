#version 330 core 
 
out vec4 fragColor; 
 
uniform vec2 resolution; // Screen resolution 
 
void main() { 
    // Condition to draw coordinate lines 
    if (abs(gl_FragCoord.x - 0.5 * 1920) < 1.0 || 
    abs(gl_FragCoord.y - 0.5 * 1080) < 1.0) { 
        fragColor = vec4(1.0, 1.0, 1.0, 1.0); // White color for lines 
    } else { 
        fragColor = vec4(0.0, 0.0, 0.0, 0.0); // Transparent for other pixels 
    } 
} 
