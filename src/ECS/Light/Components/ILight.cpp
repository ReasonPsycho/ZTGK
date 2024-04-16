#include "ILight.h"

ILight::~ILight() {
}

ILight::ILight() {
    
}

void ILight::DeleteShadow() {
    glDeleteTextures(1, &depthMap);
    glDeleteFramebuffers(1, &depthMapFBO);
}

