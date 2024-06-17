//
// Created by cheily on 08.04.2024.
//

#pragma once


#include "ECS/System.h"
#include "Group.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "ECS/SignalQueue/SignalReceiver.h"
#include "ECS/HUD/Interactables/HUDHoverable.h"
#include "ECS/HUD/Interactables/HUDButton.h"
#include "ECS/HUD/Interactables/HUDSlider.h"
#include "ECS/HUD/Components/Minimap.h"
#include "MinimapRenderer.h"

struct HUDRemapGroupsSignalData;

class HUD : public System {
public:

    std::unordered_map<unsigned, Group> groups;
    std::vector<Group *> z_sorted_groups;
    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<SpriteRenderer> spriteRenderer;
    std::unique_ptr<MinimapRenderer> minimapRenderer;
    std::unique_ptr<SignalReceiver> signalReceiver;

    void UpdateImpl() override;

    void draw();
    void drawGroup(unsigned groupID);
    Group * getDefaultGroup() const;
    Group * getGroupOrDefault(unsigned groupID) const;
    Group * getGroupOrAddDefault(unsigned groupID);
    Group * findGroupByName(const std::string & name) const;
    unsigned int
    addGroup(unsigned int parentGroupID = 0, const string &name = "", bool hidden = false, glm::vec3 offset = {0, 0, 0});
    bool removeGroup(unsigned groupID);

    std::vector<AHUDComponent *> getOfGroup(unsigned groupID);
    glm::vec3 getGroupTreeOffset(unsigned leafGroupID) const;
    bool isGroupTreeHidden(unsigned leafGroupID) const;

    bool filterInteractionButtons = true;
    int interactableButtonFilter = GLFW_MOUSE_BUTTON_LEFT;

#pragma region Element Creation
    Entity *createButton(const std::string &text, glm::vec2 centerPos, glm::vec2 size, glm::vec4 defaultColor,
                         HUDHoverable::hover_func onHoverEnter, HUDHoverable::hover_func onHoverExit,
                         HUDButton::button_func onPress, HUDButton::button_func onRelease, Entity *parent,
                         unsigned int parentGroupID = 0);
    Entity *
    createButton(glm::vec2 centerPos, glm::vec2 size, const std::string &foregroundSpritePath,
                 const std::string &backgroundSpritePath, const std::function<void()> &onRelease, Entity *parent,
                 unsigned int parentGroupID = 0);
    Entity *
    createButton(const std::string &text, glm::vec2 centerPos, glm::vec2 size, glm::vec4 color, glm::vec4 hoverColor,
                 glm::vec4 pressColor, const std::function<void()> &onRelease, Entity *parent,
                 unsigned int parentGroupID = 0);

    Entity * createSlider_Bar(SliderDirection direction, glm::vec2 midLeftPos, glm::vec2 size, glm::vec4 backgroundColor, glm::vec4 fillColor,
                              Entity * parent = nullptr, unsigned parentGroupID = 0,
                              bool displayValue = false, float displayMax = 0, float displayMin = 0);
    Entity * createSlider_BarControllable(SliderDirection direction, glm::vec2 midLeftPos, glm::vec2 size, glm::vec4 backgroundColor, glm::vec4 fillColor,
                                          Entity * parent = nullptr, unsigned parentGroupID = 0,
                                          bool displayValue = false, float displayMax = 0, float displayMin = 0);
    Entity * createSlider_SettingBar(SliderDirection direction, glm::vec2 midLeftPos, glm::vec2 size,
                                     Entity * parent = nullptr, unsigned parentGroupID = 0,
                                     float displayMax = 100, float displayMin = 0, std::string displayFormat = "{:.0f}/{:.0f}");
#pragma endregion

    void init();
    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override { return reinterpret_cast<const std::type_index *>(&componentTypes); }
    int getNumComponentTypes() override { return 6; }
    void showImGuiDetailsImpl(Camera *camera) override;
    void registerComponents() override{};

    std::unordered_map<unsigned, std::vector<Sprite*>> sprites;
    std::unordered_map<unsigned, std::vector<Text*>> texts;
    std::unordered_map<unsigned, std::vector<HUDHoverable*>> hoverables;
    std::unordered_map<unsigned, std::vector<HUDButton*>> buttons;
    std::unordered_map<unsigned, std::vector<HUDSlider*>> sliders;
    Minimap * minimap = nullptr;

    void sort_z();
    void remap_groups(HUDRemapGroupsSignalData data);

private:
    std::array<std::type_index, 6> componentTypes = {
        std::type_index(typeid(Sprite)),
        std::type_index(typeid(Text)),
        std::type_index(typeid(HUDHoverable)),
        std::type_index(typeid(HUDButton)),
        std::type_index(typeid(HUDSlider)),
        std::type_index(typeid(Minimap))
    };

    Entity *bar_base(glm::vec2 midLeftPos, glm::vec2 size,
                     glm::vec4 backgroundColor, glm::vec4 fillColor,
                     Entity *parent, unsigned int parentGroupID,
                     bool displayValue, float displayMax, float displayMin);
};
