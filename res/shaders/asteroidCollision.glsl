#version 430

layout(local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

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
    uint a = uint(cellCord.x * 9737339);
    uint c = uint(cellCord.y * 9737341);
    uint b = uint(cellCord.z * 9737333);
    return (a + b + c) % uint(cellData.length());
}

vec3 SeperationVector(vec3 a, vec3 b, float ra, float rb){
    return ((a - b)/length(a - b)) * (ra * rb  - length(a-b));
}

float MeanOfScales(vec3 scale){
    return (scale.x + scale.y + scale.z)/3;
}

uniform float collisonRadius;

void main() {
    uint index = gl_GlobalInvocationID.x;
    vec3 sumOfColisions = vec3(0);
    int amountOfCollisons = 0;
    AsteroidData currebtAsteroid = asteroidsData[index];
    float scale = MeanOfScales(currebtAsteroid.scale.xyz) ;
    for (int x = -1; x < 1;x ++){
        for (int y = -1; y < 1;y ++){
            for (int z = -1; z < 1;z ++){
                vec3 cellCord = PositionToCellCoord(asteroidsData[index].position.xyz + vec3(x, y, z), collisonRadius);
                uint hash = HashCell(cellCord);
                int currentTablePos = cellData[hash].startIndices;
                if (currentTablePos != 9999999){
                    while (cellData[currentTablePos].spatialLookup[1] == hash){
                        if (cellData[currentTablePos].spatialLookup[0] != index){
                            AsteroidData asteroidThatICheck = asteroidsData[cellData[currentTablePos].spatialLookup[0]];
                            float scale2 = MeanOfScales(asteroidThatICheck.scale.xyz);
                            if (length(asteroidThatICheck.position.xyz - currebtAsteroid.position.xyz) <= collisonRadius * scale + collisonRadius * scale2){
                                sumOfColisions += SeperationVector(asteroidThatICheck.position.xyz, currebtAsteroid.position.xyz, collisonRadius * scale, collisonRadius * scale2);
                                amountOfCollisons++;
                            }
                        }
                        currentTablePos++;
                    }
                }
                    
            }
        }
    }
    if (amountOfCollisons == 0) return;
    sumOfColisions /= amountOfCollisons;
    sumOfColisions = normalize(sumOfColisions);
    asteroidsData[index].velocity = vec4(-sumOfColisions * 4, 1);
}