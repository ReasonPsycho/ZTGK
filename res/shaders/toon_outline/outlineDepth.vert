
#version 460 core
layout (location = 0) in vec3 in_pos;
layout (location = 2) in vec3 in_normal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 view_normal;

void main()
{
    view_normal =  mat3(transpose(inverse(model))) * in_normal;

    gl_Position = projection * view * vec4(in_pos, 1.0);
}