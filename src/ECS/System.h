//
// Created by redkc on 23/02/2024.
//

#ifndef REASONABLEGL_SYSTEM_H
#define REASONABLEGL_SYSTEM_H



#include <glm/glm.hpp> //glm::mat4
#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include "ECS/Render/Camera/Camera.h"


class System {
public:
    System();
    std::string name;
    
    virtual ~System() = default;
    
    virtual void addComponent(void* component) = 0;
    virtual const std::type_index* getComponentTypes() = 0;
    virtual int getNumComponentTypes() = 0;

    virtual void showImGuiDetails(Camera *camera) = 0;

    int uniqueID;     // Instance variable to store the unique ID for each object

private:
    static int nextID; // Static variable to keep track of the next available ID
};


#endif //REASONABLEGL_SYSTEM_H
