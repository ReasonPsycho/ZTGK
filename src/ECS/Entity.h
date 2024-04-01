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
#include "Scene.h"


class Entity {
public:
    
    Entity(Scene *scene, std::string name);
    Entity(Scene *scene,Entity *parent, std::string name);

    ~Entity();
    
    Scene *scene;

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
    void addComponent(std::unique_ptr<T> component) {
        component->setEntity(this);
        std::type_index typeName = std::type_index(typeid(T));
        components[typeName] = std::move(component); // now the map owns the component
        scene->systemManager.addComponent(components[typeName].get()); // pass raw pointer
    }

    template <typename T>
    T* getComponent() {
        std::type_index typeName = std::type_index(typeid(T));
        auto it = components.find(typeName);

        if(it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        // Component of type T doesn't exist for the entity - handle this case appropriately
        return nullptr; // This is just an example, you could also assert(false) or throw an exception
    }

    void showImGuiDetails(Camera *camera);
    
//protected:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components; 
    std::vector<std::unique_ptr<Entity>> children;

    unsigned uniqueID;     // Instance variable to store the unique ID for each object
    
};


#endif