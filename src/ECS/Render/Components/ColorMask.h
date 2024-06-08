//
// Created by redkc on 07/06/2024.
//

#ifndef ZTGK_COLORMASK_H
#define ZTGK_COLORMASK_H


#include <map>
#include "ECS/Entity.h"
#include "ECS/Utils/Time.h"


struct ColorMaskData
{
    glm::vec4 color;
    float timer;
    bool constant;
    ColorMaskData(glm::vec4 color,float timer):color(color),timer(timer),constant(false){};
    ColorMaskData(glm::vec4 color):color(color),timer(10),constant(true){};
    ColorMaskData():color(glm::vec4(0)),timer(10),constant(false){};

};

class ColorMask : public Component {
        
public:
    ColorMask();
    void AddMask(std::string name,glm::vec4 color,float timer);
    void AddMask(std::string name,glm::vec4 color);
    void RemoveMask(std::string name);
    bool HasMask(std::string name);
    void UpdateImpl() override;
    void showImGuiDetailsImpl(Camera *camera) override;
    
private:
    std::map<std::string, ColorMaskData> maskDataMap;

    //Imgui bullshit
    bool isConstant = false;
    float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float timer = 0.0f;
    char input_buf[64] = "Name";
};


#endif //ZTGK_COLORMASK_H
