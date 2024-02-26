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
#include "modelLoading/Model.h"
#include "Camera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Transform/Transform.h"
#include "Systems/SystemManager.h"
#include "Component.h"


class Entity {
public:

    explicit Entity(SystemManager* systemManager);
    
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

    void drawSelfAndChild(Shader &ourShader);
    void drawSelfAndChild(Shader &regularShader,Shader &instancedShader);


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
    
private:
    std::unordered_map<std::type_index, Component*> components;
    std::vector<std::unique_ptr<Entity>> children;
    SystemManager *systemManager;
};


#endif