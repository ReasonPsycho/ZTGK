#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 FragColor = texture(ourTexture, TexCoord);
}