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

// Free function templates
template<typename T>
Component* createComponent() {
    return new T();
}

template<typename T>
Component* createComponentWrapper() {
    return createComponent<T>();
}



class SystemManager {
public:
    
// Inside SystemManager class
    template<typename T>
    void registerComponent() {
        std::type_index ti(typeid(T));
        componentFactories[ti] = [](){ return std::make_unique<T>(); };
    }
    
    template<typename T>
    void addComponent(T *component) {
        std::type_index typeIndex(typeid(*component));

        for (auto &[_, system]: systems) {
            for (int i = 0; i < system->getNumComponentTypes(); ++i) {
                if (typeIndex == system->getComponentTypes()[i]) {
                    // Pass the pointer or whatever information needed here
                    system->addComponent(component);
                }
            }
        }
    }

    template<typename T>
    void removeComponent(T *component) {
        std::type_index typeIndex(typeid(*component));

        for (auto &[_, system]: systems) {
            for (int i = 0; i < system->getNumComponentTypes(); ++i) {
                if (typeIndex == system->getComponentTypes()[i]) {
                    // Pass the pointer or whatever information needed here
                    system->removeComponent(component);
                    break;
                }
            }
        }
    }

    template<typename T>
    void addSystem(std::unique_ptr<T> system) {
        std::type_index typeIndex(typeid(*system));
        system->systemManager = this;
        system->registerComponents();
        systems[typeIndex] = std::move(system);
    }

    template<typename T>
    T* getSystem() {
        auto typeIndex = std::type_index(typeid(T));
        auto it = systems.find(typeIndex);
        if (it == systems.end()) {
            return nullptr; // or throw an exception
        }
        return dynamic_cast<T*>(it->second.get());
    }


    virtual void showImGuiDetails(Camera *camera);
    virtual void showImGuiEnitityBar(Entity *entity);
    void Update();
    void FinishInnit();
    std::unordered_map<std::type_index, std::function<std::unique_ptr<Component>()>> componentFactories;
    std::unordered_map<std::type_index, std::unique_ptr<System>> systems;
    
    bool isAddComponentMenuOpen = false;
    int selectedItem = -1;
    Entity* selectedEntity = nullptr;
    std::vector<std::string> componentNames;
    std::vector<std::type_index> componentKeys;
    std::vector<const char*> cStringList;

};


#endif //REASONABLEGL_SYSTEMMANAGER_H
