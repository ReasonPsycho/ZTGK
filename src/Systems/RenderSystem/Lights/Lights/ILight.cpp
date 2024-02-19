#include "ILight.h"

int ILight::nextID = 0;

ILight::~ILight() {
    DeleteShadow();
}

void ILight::DeleteShadow() {
    glDeleteTextures(1, &depthMap);
    glDeleteFramebuffers(1, &depthMapFBO);
}

ILight::ILight(Shader *shadowMapShader, Shader *instanceShadowMapShader) : shadowMapShader(shadowMapShader),
                                                                           instanceShadowMapShader(
                                                                                   instanceShadowMapShader) {
    uniqueID = nextID++; // Assign the current value of nextID and then increment it for the next instance
}
