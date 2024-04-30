//
// Created by redkc on 16/04/2024.
//

#ifndef ZTGK_INSTANCERENDERSYSTEM_H
#define ZTGK_INSTANCERENDERSYSTEM_H



#include "ECS/Render/Camera/Camera.h"
#include "ECS/Grid/Grid.h"
#include "ECS/System.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Utils/VectorUtils.h"
#include "ECS/Render/FrustumCulling/Frustum.h"

class InstanceRenderSystem : public System {
public:
    InstanceRenderSystem(Camera * camera);
    void Innit();
    const std::type_index* getComponentTypes() override { return nullptr; };
    int getNumComponentTypes() override { return 0;};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void DrawTiles(Shader* regularShader,Camera * camera);
    void PushToSSBO(Camera* camera);
    void UpdateImpl();

    Model* tileModel;
private:
    Camera * camera;
    GLuint wallDataBufferID;
    GLuint wallDataBufferBindingPoint = 6;
    GLuint tileTextureArray;
    GLuint tileTextureBindingPoint = 10;
    int numberOfTextures = 3;
    
    string tilePath =  "res/textures/tiles/Tile";
    
    std::vector<WallData> wallData;
};


#endif //ZTGK_INSTANCERENDERSYSTEM_H
