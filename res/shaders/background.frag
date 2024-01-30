#version 330 core
out vec4 FragColor;
out vec4 BrightColor;

in vec3 WorldPos;

uniform samplerCube environmentMap;

void main()
{
    vec3 envColor = textureLod(environmentMap, WorldPos, 0.0).rgb;

    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2));
    BrightColor =  vec4(vec3(0.0), 1.0);
    FragColor = vec4(envColor, 1.0);
}