#version 460

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 vxColor;

uniform mat4 projection;

out vec4 color;

void main() {
    gl_Position = projection * vec4(position, 0.0, 1.0);
    color = vxColor;
}