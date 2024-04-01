//
// Created by redkc on 23/02/2024.
//

#ifndef REASONABLEGL_SYSTEMMANAGER_H
#define REASONABLEGL_SYSTEMMANAGER_H


#include <unordered_map>
#include <typeindex>
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include "ECS/System.h"
#include "imgui.h"

class Component;
class Entity; 

class SystemManager {
public:
    template <typename T>
    void addComponent(T* component) {
        std::type_index typeIndex(typeid(*component));

        for (auto& [_, system] : systems) {
            for (int i = 0; i < system->getNumComponentTypes(); ++i) {
                if (typeIndex == system->getComponentTypes()[i]) {
                    // Pass the pointer or whatever information needed here
                    system->addComponent(component);
                }
            }
        }
    }

    template <typename T>
    void removeComponent(T* component) {
        std::type_index typeIndex(typeid(*component));

        for (auto& [_, system] : systems) {
            for (int i = 0; i < system->getNumComponentTypes(); ++i) {
                if (typeIndex == system->getComponentTypes()[i]) {
                    // Pass the pointer or whatever information needed here
                    system->removeComponent(component);
                }
            }
        }
    }

    template <typename T>
    void addSystem(T* system) {
        std::type_index typeIndex(typeid(*system));
        systems[typeIndex] = system;
    }
    
    template <typename T>
    T* getSystem() {
        auto typeIndex = std::type_index(typeid(T));
        auto it = systems.find(typeIndex);
        if (it == systems.end()) {
            return nullptr; // or throw an exception
        }
        return dynamic_cast<T*>(it->second);
    }

    virtual void showImGuiDetails(Camera *camera);
    std::unordered_map<std::type_index, System*> systems;
};


#endif //REASONABLEGL_SYSTEMMANAGER_H
