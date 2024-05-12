//
// Created by redkc on 10/04/2024.
//

#ifndef ZTGK_WIRERENDERSYSTEM_H
#define ZTGK_WIRERENDERSYSTEM_H


#include "ECS/System.h"
#include "ECS/Raycasting/Collider.h"
#include "ECS/Raycasting/Ray.h"
#include "ECS/Raycasting/Colliders/BoxCollider.h"

class WireRenderSystem : public System {


public:
    void DrawColliders();
    void DrawRays();
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const std::type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 3;};

    void registerComponents() override{};
    void Innit();
    void UpdateImpl() override;

    
    
    explicit WireRenderSystem(Primitives *primitives, Camera *camera);

    std::vector<unique_ptr<Ray>> rayComponents;
    void PushToSSBO(Camera* camera);
    Model* boxModel;
    
private:
    bool renderBoxes = false;
    bool renderRays = false;
    Primitives*  primitives;
    Camera*  camera;
    Shader rayShader = Shader("res/shaders/ray.vert", "res/shaders/ray.frag");
    Shader boxShader = Shader("res/shaders/wiremesh.vert", "res/shaders/wiremesh.frag");
    std::vector<Collider *> colliderComponents;
    std::vector<BoxColliderData> boxColliderDataArray;
    GLuint wireBoxBufferID;
    GLuint wireBoxDataBufferBindingPoint = 7;
    std::array<std::type_index, 3> componentTypes = {
            std::type_index(typeid(Collider)),
            std::type_index(typeid(BoxCollider)), //Sphere isn't supported yet XD
            std::type_index(typeid(Ray)) //Sphere isn't supported yet XD
    };
    
};


#endif //ZTGK_WIRERENDERSYSTEM_H
