//
// Created by redkc on 10/04/2024.
//

#ifndef ZTGK_WIRERENDERER_H
#define ZTGK_WIRERENDERER_H


#include "ECS/System.h"
#include "ECS/Raycasting/Collider.h"
#include "ECS/Raycasting/Ray.h"
#include "ECS/Raycasting/Colliders/BoxCollider.h"

class WireRenderer : public System {


public:
    void DrawColliders();
    void DrawRays();
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetails(Camera *camera) override;
    void Innit();
    
    
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const std::type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 3;};
    
    explicit WireRenderer(Primitives *primitives, Camera *camera);

    std::vector<unique_ptr<Ray>> rayComponents;
    
private:
    Primitives*  primitives;
    Camera*  camera;
    Shader wireShader = Shader("res/shaders/wiremesh.vert", "res/shaders/wiremesh.frag");
    std::vector<Collider *> colliderComponents;
    std::array<std::type_index, 3> componentTypes = {
            std::type_index(typeid(Collider)),
            std::type_index(typeid(BoxCollider)), //Sphere isn't supported yet XD
            std::type_index(typeid(Ray)) //Sphere isn't supported yet XD
    };

    bool enabled = false;
};


#endif //ZTGK_WIRERENDERER_H
