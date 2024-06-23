//
// Created by igork on 23.05.2024.
//

#include "Pranium.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Entity.h"
#include "ECS/Utils/Globals.h"
#include "ECS/Unit/Equipment/InventoryManager.h"
#include "ECS/Unit/Equipment/ConcreteItems/PraniumOre.h"
#include "ECS/Unit/Mining/MiningSystem.h"
#include "ECS/Render/Components/BetterSpriteRender.h"
#include "ECS/Utils/RNG.h"



Pranium::Pranium(float timeToMine, Vector2Int gridPosition, Grid *grid) : IMineable(timeToMine, gridPosition, grid) {
    name = "Pranium";
    //ztgk::game::scene->systemManager.getSystem<MiningSystem>()->addComponent(this);

}

void Pranium::onMine(Unit *unit) {

}

void Pranium::onMined(Unit *unit) {
    IMineable::onMined(unit);
    if (parentEntity->getChild("Pralka")->getComponent<Render>())
        parentEntity->getChild("Pralka")->getComponent<Render>()->Remove();
    auto item = InventoryManager::instance->create_item(Item::item_types.pranium_ore);
    auto pos = grid->GridToWorldPosition(gridPosition);
    InventoryManager::instance->spawn_item_on_map(item, gridPosition);
    spdlog::debug("Mined chest");
//    tile->getEntity()->removeComponentFromMap(this);

}

void Pranium::generatePranium(Model *model) {
    auto parent = getEntity();
    auto render = parent->getComponent<Render>();
    if(render != nullptr){
        parent->removeComponentFromMap(render);
    }
    auto pralkaEntity = ztgk::game::scene->addEntity(parent, "Pralka");
    pralkaEntity->addComponent(std::make_unique<Render>(model));
    pralkaEntity->transform.setLocalRotation(glm::vec3(glm::radians(0.0f), glm::radians(-90.0f), glm::radians(0.f)));
    pralkaEntity->transform.setLocalScale(glm::vec3(0.5, 0.5, 0.5));
    pralkaEntity->transform.setLocalPosition(glm::vec3(-0.5f, 0, 0));
    pralkaEntity->updateSelfAndChild();

}

void Pranium::UpdateImpl() {
    auto tile = grid->getTileAt(gridPosition);
    auto render = getEntity()->getChild("Pralka")->getComponent<Render>();
    if(tile == nullptr || render == nullptr) return;
    render->isInFogOfWar = tile->isInFogOfWar;

    tryToSendEmote();


}

Pranium::~Pranium() {
    ztgk::game::scene->systemManager.getSystem<MiningSystem>()->removeComponent(this);
}

void Pranium::tryToSendEmote() {
    if (getEntity()->getChild("Emote") == nullptr) {
        ztgk::game::scene->addEntity(getEntity(), "Emote");
    }
    auto emoChild = getEntity()->getChild("Emote");

    if (emoChild->getComponent<BetterSpriteRender>() == nullptr) {
        emoChild->addComponent(std::make_unique<BetterSpriteRender>(ztgk::game::emotes.at(ztgk::game::EMOTES::PRANIUM).get() , 4));
        //emoChild->addComponent(std::make_unique<PointLight>());
    }
    else if(emoChild->getComponent<BetterSpriteRender>() != nullptr && emoChild->getComponent<BetterSpriteRender>()->toBeDeleted) {
        emoChild->removeComponentFromMap(emoChild->getComponent<BetterSpriteRender>());
        //emoChild->removeComponentFromMap(emoChild->getComponent<PointLight>());
    }
}