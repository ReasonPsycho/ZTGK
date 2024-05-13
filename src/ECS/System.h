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
class SystemManager;

class System {
public:
    System();
    std::string name;
    
    virtual ~System() = default;

    //Component system
    virtual void addComponent(void* component) = 0;
    virtual void removeComponent(void* component) = 0;
    virtual void registerComponents() = 0;
    virtual const std::type_index* getComponentTypes() = 0;
    virtual int getNumComponentTypes() = 0;

    //Imgui
    void showImGuiDetails(Camera *camera);
    
    //Logic

    void Update();

    SystemManager *getSystemManager();

    unsigned uniqueID;     // Instance variable to store the unique ID for each object
    SystemManager* systemManager;
protected:
    virtual void UpdateImpl(){};

    virtual void showImGuiDetailsImpl(Camera *camera) = 0;
    
};


#endif //REASONABLEGL_SYSTEM_H
