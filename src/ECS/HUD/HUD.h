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

struct HUDRemapGroupsSignalData;

class HUD : public System {
public:
//    struct btn_callback_ctx {
//        HUD * hud = nullptr;
//        Entity * entity = nullptr;
//    };
//    using btn_callback = std::function<void(btn_callback_ctx context)>;

    std::unordered_map<unsigned, Group> groups;
    std::vector<Group *> z_sorted_groups;
    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<SpriteRenderer> spriteRenderer;
    std::unique_ptr<SignalReceiver> signalReceiver;

    void draw();
    void drawGroup(unsigned groupID);
    Group * getDefaultGroup() const;
    Group * getGroupOrDefault(unsigned groupID) const;
    Group * getGroupOrAddDefault(unsigned groupID);
    Group * findGroupByName(const std::string & name) const;
    unsigned int
    addGroup(glm::vec3 offset = {0, 0, 0}, bool hidden = false, const std::string &name = "", unsigned parentGroupID = 0);
    bool removeGroup(unsigned groupID);

    std::vector<AHUDComponent *> getOfGroup(unsigned groupID);
    glm::vec3 getGroupTreeOffset(unsigned leafGroupID) const;
    bool isGroupTreeHidden(unsigned leafGroupID) const;

    Entity * createButton(const std::string & text, const std::function<void()> & onPress, const std::function<void()> & onRelease, glm::vec2 pos, glm::vec2 size, unsigned parentGroupID = 0);
    Entity * createButton(const std::string & text, const std::string & foregroundSpritePath, const std::string & backgroundSpritePath, const std::function<void()> & onPress, const std::function<void()> & onRelease, glm::vec2 pos, glm::vec2 size, unsigned parentGroupID = 0);
//    Entity * newButton(const std::string & text, const btn_callback & callback, glm::vec2 pos, glm::vec2 size, Entity * parent = nullptr);

    void init();
    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override { return reinterpret_cast<const std::type_index *>(&componentTypes); }
    int getNumComponentTypes() override { return 4; }
    void showImGuiDetailsImpl(Camera *camera) override;
    void registerComponents() override{};

    std::unordered_map<unsigned, std::vector<Sprite*>> sprites;
    std::unordered_map<unsigned, std::vector<Text*>> texts;
    std::unordered_map<unsigned, std::vector<HUDHoverable*>> hoverables;
    std::unordered_map<unsigned, std::vector<HUDButton*>> buttons;

    void sort_z();
    void remap_groups(HUDRemapGroupsSignalData data);

private:
    std::array<std::type_index, 4> componentTypes = {
        std::type_index(typeid(Sprite)),
        std::type_index(typeid(Text)),
        std::type_index(typeid(HUDHoverable)),
        std::type_index(typeid(HUDButton))
    };
};
