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
#include "tracy/Tracy.hpp"
#include "ECS/Utils/Globals.h"
#include "ECS/Light/LightSystem.h"

class InstanceRenderSystem : public System {
public:
    InstanceRenderSystem(Camera * camera);
    
    void Innit();
    void DrawTiles(Shader* regularShader,Camera * camera);
    void DrawParticles(Shader* regularShader,Camera * camera);
    void DrawLights(Shader* regularShader,Camera * camera);
    void SimpleDrawTiles(Shader *regularShader, Camera *camera, glm::vec3 viewPos, float renderDistance);
    void PushToSSBO(Camera* camera);

    //ECS
    void registerComponents() override{};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void UpdateImpl() override;
    const std::type_index* getComponentTypes() override {return nullptr; };
    int getNumComponentTypes() override { return 0;};
    
    
    Model* tileModel;


private:
    Camera * camera;
    GLuint wallDataBufferID;
    GLuint wallDataBufferBindingPoint = 6;
    GLuint tileTextureArray;
    GLuint tileTextureBindingPoint = 10;
    int numberOfTextures = 3;
    double maxBias = 0.005f;
    double biasMuliplayer = 0.00001f;
    double factor = 2;
    double units = 0;
    float dirtLayer = 0.2;
    float saturation = 2;
    
    
    string tilePath =  "res/textures/tiles/Tile";
    

    std::vector<Chunk* > loadedChunks;
    MaterialPhong wallMaterial;
    MaterialPhong particleMaterial;
    MaterialPhong lightMaterial;
    std::vector<WallData> wallData;


    //ECS
    std::array<std::type_index, 0> componentTypes = {};
};


#endif //ZTGK_INSTANCERENDERSYSTEM_H
