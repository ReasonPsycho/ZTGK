#version 460
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 frag_normal_depth; //Meant for outline process
layout (location = 2) out vec4 BloomBuffer; //Meant for outline process
layout (location = 3) out vec4 FogOfWarMask;//Meant for outline process

in VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 WorldPos;
    vec3 ViewPos;
}fs_in;

uniform sampler2D diffuseTexture;
uniform bool outlineMapping;
uniform float alpha;
uniform float depthBias; // new uniform variable

void main()
{
    vec2 texCoords = fs_in.TexCoords;
    
    vec4 diffuse = vec4(texture(diffuseTexture, texCoords));

    diffuse.a *= alpha;
    if(diffuse.a < 0.02)
    discard;
    
    vec3 normal = fs_in.Normal;

    gl_FragDepth = gl_FragDepth - depthBias/400; //400 is constant value of far clip
    
    if(outlineMapping){
        float depth = gl_FragCoord.z + depthBias;
        frag_normal_depth = vec4(normal, depth);
    }

    FragColor = diffuse;
    
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));

    if(brightness > 1.0)
        BloomBuffer = vec4(FragColor.rgb, 1.0);
    else
        BloomBuffer = vec4(0.0, 0.0, 0.0, 1.0);

    FogOfWarMask =  vec4(vec3(0), 0);
}