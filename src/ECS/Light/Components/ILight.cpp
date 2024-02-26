#include "ILight.h"

ILight::~ILight() {
    DeleteShadow();
}

void ILight::DeleteShadow() {
    glDeleteTextures(1, &depthMap);
    glDeleteFramebuffers(1, &depthMapFBO);
}

ILight::ILight() {
    
}


