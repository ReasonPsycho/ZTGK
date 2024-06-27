#version 460
layout (location = 0) out vec4 FragColor;

in flat int[4] currentWallData;

vec3 selectionColor[10] = vec3[]
(
    vec3(1, 1, 1), //Just here to simplyfiy the logic
    vec3(0, 1, 0),  // green - lmb
    vec3(0, 0, 1),  // blue - rmb
    vec3(1, 1, 0.5),  // yellow - move order
    vec3(1, 0, 0),  // red - enemy
    vec3(0.6, 0.6, 0),  // gold - item
    vec3(0.9, 0.7, 1),   // light blue(?) - explosion/dmg aoe
    vec3(0.6, 1, 0.4),   // light green - heal aoe
    vec3(1, 0.5, 0.5),  // light red - take damage
    vec3(0.7, 0.7, 1)  // very light blue - show item range
);

vec3 tileStateColor[8] = vec3[]
(
    vec3(1, 1, 1), //Just here to simplyfiy the logic
    vec3(0, 1, 0),  // WALL
    vec3(0, 0, 1),  // CHEST
    vec3(1, 1, 0.5),  // ORE
    vec3(1, 0, 0),  // CORE
    vec3(0.6, 0.6, 0),  // SPONGE
    vec3(0.9, 0.7, 1),   // BUG
    vec3(0.6, 1, 0.4)   // SHROOM
);


void main()
{   
    vec3 result =vec3(0.7568627451,0.8745098039,0.9607843137);
    if (currentWallData[1] == 1){
        vec3 result =vec3(0,0,0);
    }else if (currentWallData[2] != 0){
        result = selectionColor[currentWallData[2]] ;
    } else{
        result = tileStateColor[currentWallData[3]] ;
    }
    FragColor = vec4(result, 1.0);
}