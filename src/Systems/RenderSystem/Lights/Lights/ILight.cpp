#include "ILight.h"

int ILight::nextID = 0;

ILight::~ILight() {
    DeleteShadow();
}

void ILight::DeleteShadow() {
    glDeleteTextures(1, &depthMap);
    glDeleteFramebuffers(1, &depthMapFBO);
}
