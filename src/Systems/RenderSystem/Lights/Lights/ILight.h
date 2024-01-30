//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_ILIGHT_H
#define OPENGLGP_ILIGHT_H

#include "Camera.h"

enum LightType {
    Directional,
    Spot,
    Point,
};

class ILight {
public:
    ILight(Shader *shadowMapShader) : shadowMapShader(shadowMapShader) {
        uniqueID = nextID++; // Assign the current value of nextID and then increment it for the next instance
    }

    ~ILight();

    enum LightType lightType;
    glm::mat4x4 model{};

    virtual void showImGuiDetails(Camera *camera) = 0; // Pure virtual function
    virtual void EditLight(Camera *camera) = 0;

    virtual void GenerateShadow(void (*funcPtr)()) = 0; // Pure virtual function
    virtual void InnitShadow() = 0;

    void DeleteShadow();

    unsigned int depthMap{};
private:
    static int nextID; // Static variable to keep track of the next available ID
protected:
    int uniqueID;     // Instance variable to store the unique ID for each object

    //For shadows
    bool initializedShadow = false;
    unsigned int depthMapFBO{};
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    Shader *shadowMapShader;
    glm::mat4 shadowProj{};
};

#endif //OPENGLGP_ILIGHT_H
