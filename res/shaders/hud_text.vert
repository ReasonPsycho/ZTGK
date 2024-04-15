#version 330 core
layout (location = 0) in vec2 pos; // <vec2 pos, vec2 tex>
layout (location = 1) in vec2 texPos;
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(pos, 0.0, 1.0);
    TexCoords = texPos;
}
