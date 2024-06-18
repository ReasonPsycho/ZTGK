#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 WorldPos;
    vec3 ViewPos;
}vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 camPos;
uniform vec3 cameraUp;

uniform mat4 model;
uniform float scale;
bool isBilborded;




void main()
{

    mat4 localModel;
    if(isBilborded) {
        vec3 scale = vec3(length(model[0]), length(model[1]), length(model[2])); // preserve object's scale
        vec3 billboard_position = vec3(model[3].xyz);

        vec3 look = normalize(camPos - billboard_position);
        vec3 right = cross(vec3(0.0, 1.0, 0.0), look);
        vec3 up = cross(look, right);

        localModel = mat4(
        vec4(right * scale.x, 0.0),
        vec4(up * scale.y, 0.0),
        vec4(look * scale.z, 0.0),
        vec4(billboard_position, 1.0)
        );
    } else {
        localModel = model;
    }
    
    //Standard calculation
    vs_out.TexCoords = aTexCoords;
    vs_out.WorldPos = vec3(localModel* vec4(aPos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(localModel))) * aNormal;
    vs_out.ViewPos = camPos;
    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0);
}
