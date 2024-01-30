#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp> //glm::mat4
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include "modelLoading/Model.h"
#include "Camera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Transform.h"


class Entity {
public:
    //Scene graph
    std::list<std::unique_ptr<Entity>> children;
    Entity *parent = nullptr;

    //Space information
    Transform transform;

    Model *pModel = nullptr;

    // constructor, expects a filepath to a 3D model.


    //Add child. Argument input is argument of any constructor that you create. By default you can use the default constructor and don't put argument input.
    template<typename... TArgs>
    void addChild(TArgs &... args);

    //Update transform if it was changed
    void updateSelfAndChild();

    //Force update of transform even if local space don't change
    void forceUpdateSelfAndChild();


    void drawSelfAndChild(Shader &ourShader, unsigned int &display, unsigned int &total);
};


#endif