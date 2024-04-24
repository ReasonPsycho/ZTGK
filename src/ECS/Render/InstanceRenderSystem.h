//
// Created by redkc on 16/04/2024.
//

#ifndef ZTGK_INSTANCERENDERSYSTEM_H
#define ZTGK_INSTANCERENDERSYSTEM_H



#include "ECS/Render/Camera/Camera.h"
#include "ECS/Grid/Tile.h"
#include "ECS/System.h"
#include "ECS/Render/ModelLoading/Model.h"

class InstanceRenderSystem : public System {
public:
    InstanceRenderSystem();
    void Innit();
    const std::type_index* getComponentTypes() override {return reinterpret_cast<const std::type_index *>(&componentTypes); };
    int getNumComponentTypes() override { return 1;};
    void addComponent(void* component) override;
    void removeComponent(void* component) override;
    void showImGuiDetails(Camera *camera) override;
    void DrawTiles(Shader* regularShader);
    void PushToSSBO();
    void Update();

    Model* tileModel;
private:
    GLuint wallDataBufferID;
    GLuint wallDataBufferBindingPoint = 6;
    GLuint tileTextureArray;
    GLuint tileTextureBindingPoint = 10;
    int numberOfTextures = 3;
    
    string tilePath =  "res/textures/tiles/Tile";
    
    std::vector<Tile *> tileComponents;
    std::vector<WallData> wallData;
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(Tile))
    };
};


#endif //ZTGK_INSTANCERENDERSYSTEM_H
