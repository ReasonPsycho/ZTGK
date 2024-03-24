#version 330 core

uniform float near;
uniform float far;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    gl_FragDepth = LinearizeDepth(gl_FragCoord.z) / far;
}

