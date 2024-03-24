#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp> //glm::mat4
#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include "glm/gtc/type_ptr.hpp"
#include "Transform/Transform.h"
#include "Component.h"
#include "SystemManager.h"


class Entity {
public:

    Entity(SystemManager* systemManager,std::string name);
    
    std::string name;
    //Scene graph
    const Entity *parent = nullptr;
    
    //Space information
    Transform transform = Transform();

    
    //Add child. Argument input is argument of any constructor that you create. By default you can use the default constructor and don't put argument input.
    Entity* addChild(std::unique_ptr<Entity> child);
    
    //Update transform if it was changed
    void updateSelfAndChild();

    //Force update of transform even if local space don't change
    void forceUpdateSelfAndChild();



    template <typename T>
    void addComponent(T* component) {
        component->setEntity(this);
        std::type_index typeName = std::type_index(typeid(T));
        components[typeName] = component;
        systemManager->addComponent(component);
    }

    template <typename T>
    T* getComponent() {
        std::type_index typeName = std::type_index(typeid(T));
        auto it = components.find(typeName);

        if(it != components.end()) {
            return static_cast<T*>(it->second);
        }
        // Component of type T doesn't exist for the entity - handle this case appropriately
        return nullptr; // This is just an example, you could also assert(false) or throw an exception
    }

    void showImGuiDetails(Camera *camera);
    
//protected:
    int uniqueID;     // Instance variable to store the unique ID for each object
    std::unordered_map<std::type_index, Component*> components;
    std::vector<std::unique_ptr<Entity>> children;
    SystemManager *systemManager;
    bool isSelected = false;

private:
    static int nextID; // Static variable to keep track of the next available ID
    
};


#endif