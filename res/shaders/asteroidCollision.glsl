#version 430

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct AsteroidData
{
    vec4 position;
    vec4 rotation;
    vec4 scale;
    vec4 velocity;
    vec4 angularVelocity;
};

struct CellData {
    int spatialLookup[2];
    int startIndices;
};


layout (std430, binding = 0) buffer AsteroidBuffer {
    AsteroidData asteroidsData[];
};

layout (std430, binding = 1) buffer CellBuffer {
    CellData cellData[];
};

vec3 PositionToCellCoord(vec3 position, float radius){
    vec3 r;
    r.x = int(position.x/radius);
    r.y = int(position.y/radius);
    r.z = int(position.z/radius);
    return r;
}

uint HashCell(vec3 cellCord){
    uint a = uint(cellCord.x * 15823);
    uint c = uint(cellCord.x * 19609);
    uint b = uint(cellCord.x * 9737333);
    return (a + b + c) % uint(cellData.length());
}

uniform float collisonRadius;

void main() {
    uint index = gl_GlobalInvocationID.x;
    vec3 sumOfColisions = vec3(0);
    AsteroidData currebtAsteroid = asteroidsData[index];
    for(int x = -1; x < 1;i ++ ){ 
        for(int y = -1; x < 1;i ++ ){
            for(int z = -1; x < 1;i ++ ){
                vec3 currentPos = asteroidsData[index].position.xyz;
                vec3 cellCord = PositionToCellCoord(asteroidsData[index].position.xyz,collisonRadius);
                uint hash = HashCell(cellCord);
                int currentTablePos = cellData[hash].startIndices;
                while(cellData[currentTablePos].spatialLookup[1] == hash){
                    AsteroidData asteroidThatICheck = asteroidsData[cellData[currentTablePos].spatialLookup[0]];
                    
                }
            }
        } 
    }
}