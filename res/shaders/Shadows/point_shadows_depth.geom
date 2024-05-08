#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrice;

out vec4 FragPos;// FragPos from GS (output per emitvertex)

void main()
{
    int face = 0; // Choose the face to render

    gl_Layer = face;
    
    for (int i = 0; i < 3; ++i)// for each triangle's vertices
    {
        FragPos = gl_in[i].gl_Position;
        gl_Position = shadowMatrice * FragPos;
        EmitVertex();
    }
    EndPrimitive();
} 