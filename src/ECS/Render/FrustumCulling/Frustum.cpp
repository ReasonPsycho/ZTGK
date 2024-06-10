#include "Frustum.h" 
 
// 
// Created by redkc on 24/04/2024. 
// 
Frustum createFrustumFromCamera(Camera &cam) { 
    Frustum     frustum; 
    const float halfVSide = cam.farClip * tanf(glm::radians(cam.Zoom) * .5f); 
    const float halfHSide = halfVSide * cam.GetAspectRatio(); 
    const glm::vec3 frontMultFar =  cam.farClip * cam.Front; 
 
    frustum.nearFace = { cam.Position + cam.nearClip* cam.Front, cam.Front }; 
    frustum.farFace = { cam.Position + frontMultFar, -cam.Front }; 
    frustum.rightFace = { cam.Position, glm::cross(frontMultFar - cam.Right * halfHSide, cam.Up) }; 
    frustum.leftFace = { cam.Position, glm::cross(cam.Up, frontMultFar + cam.Right * halfHSide) }; 
    frustum.topFace = { cam.Position, glm::cross(cam.Right, frontMultFar - cam.Up * halfVSide) }; 
    frustum.bottomFace = { cam.Position, glm::cross(frontMultFar + cam.Up * halfVSide, cam.Right) }; 
    return frustum; 
} 
