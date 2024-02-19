#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp> //glm::mat4
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include "modelLoading/Model.h"
#include "Camera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Systems/EntitySystem/Transform.h"


class Entity {
public:

    explicit Entity() = default;
    
    explicit Entity(Entity* parent);

    //Scene graph
    std::vector<std::shared_ptr<Entity>> children;
    Entity *parent = nullptr;

    //Space information
    Transform transform;

    //Add child. Argument input is argument of any constructor that you create. By default you can use the default constructor and don't put argument input.
    void addChild(std::shared_ptr<Entity> child) {
        child->parent = this;
        children.push_back(child);
    }

    //Update transform if it was changed
    void updateSelfAndChild();

    //Force update of transform even if local space don't change
    void forceUpdateSelfAndChild();

    virtual void draw(Shader &regularShader){}; //TODO split this logic to some render stuff
    virtual void draw(Shader &regularShader,Shader &instancedShader){};
    
    void drawSelfAndChild(Shader &ourShader);
    void drawSelfAndChild(Shader &regularShader,Shader &instancedShader);
};


#endif