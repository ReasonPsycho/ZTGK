//
// Created by redkc on 16/01/2024.
//

#ifndef OPENGLGP_ILIGHT_H
#define OPENGLGP_ILIGHT_H

#include "Camera.h"

class ILight {
public:
    ILight(){
        uniqueID = nextID++; // Assign the current value of nextID and then increment it for the next instance
    }

    glm::mat4x4 model;

    virtual void showImGuiDetails(Camera* camera) = 0; // Pure virtual function
    virtual void EditLight(Camera* camera) = 0;
    
private:
    static int nextID; // Static variable to keep track of the next available ID
protected:
    int uniqueID;     // Instance variable to store the unique ID for each object
};

#endif //OPENGLGP_ILIGHT_H
