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
#include "ECS/Unit/Mining/IMineable.h"

#include "../ECS/Raycasting/Colliders/BoxCollider.h"

class Entity {
public:
    
    Entity(Scene *scene, std::string name);
    Entity(Scene *scene,Entity *parent, std::string name);

    ~Entity();
    
    Scene *scene;

    std::string name;
    //Scene graph
    Entity *parent = nullptr;
    
    //Space information
    Transform transform = Transform();
    
    //Add child. Argument input is argument of any constructor that you create. By default, you can use the default constructor and don't put argument input.
    Entity* addChild(std::unique_ptr<Entity> child);
    void removeChild(Entity *child);
    [[nodiscard]] Entity * getChild(unsigned id) const;
    [[nodiscard]] Entity * getChild(const std::string & name) const;
    [[nodiscard]] Entity * getChildR(unsigned id) const;
    [[nodiscard]] Entity * getChildR(const std::string & name) const;
    void Destroy();
    
    //UpdateImpl transform if it was changed
    void updateSelfAndChild();

    //Force UpdateImpl of transform even if local space don't change
    void forceUpdateSelfAndChild();



//    template <typename T>
//    void addComponent(std::unique_ptr<T> component) {
//        component->setEntity(this);
//        std::type_index typeName = std::type_index(typeid(T));
//        components[typeName] = std::move(component); // now the map owns the component
//        scene->systemManager.addComponent(components[typeName].get()); // pass raw pointer
//    }

    void addComponent(std::unique_ptr<Component> component) {
        component->setEntity(this);
        std::type_index typeName = std::type_index(typeid(*component));
        components[typeName] = std::move(component);
        scene->systemManager.addComponent(components[typeName].get());
    }

    void removeComponentFromMap(Component * comp);


    template <typename T>
    T* getComponent() {
        auto typeName = std::type_index(typeid(T));
        auto it = components.find(typeName);

        if (it != components.end()) {
            Component* component = it->second.get();
            if (T* castedComponent = dynamic_cast<T*>(component)) {
                return castedComponent;
            } else {
                spdlog::error("Type mismatch in getComponent()");
            }
        }
        // Component of type T doesn't exist for the entity - handle this case appropriately
        return nullptr;
    }

    template <typename T>
    T* getMineableComponent(Entity* entity) {
        // Try to get the component of class T
        T* component = entity->getComponent<T>();
        if (component != nullptr) {
            return component;
        }

        // If the direct component of type T is not found, check other components
        for (auto& pair : entity->components) {
            Component* baseComponent = pair.second.get();
            // Try to dynamically cast the component to IMineable or its derived class
            if (IMineable* mineableComponent = dynamic_cast<IMineable*>(baseComponent)) {
                // Try to dynamically cast to T
                if (T* castedComponent = dynamic_cast<T*>(mineableComponent)) {
                    return castedComponent;
                }
            }
        }

        // If the component of type T or its derived class is not found, return nullptr
        return nullptr;
    }


    void showImGuiDetails(Camera *camera);
    
//protected:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components; 
    std::vector<std::unique_ptr<Entity>> children;

    unsigned uniqueID;     // Instance variable to store the unique ID for each object

    bool removedChild = false;
    bool updateChildren = true;

};


#endif