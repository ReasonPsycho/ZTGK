//
// Created by igork on 23.05.2024.
//

#include "Pranium.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Entity.h"

Pranium::Pranium(float timeToMine, Vector2Int gridPosition, Grid *grid) : IMineable(timeToMine, gridPosition, grid) {
    name = "Pranium";

}

void Pranium::onMine(Unit *unit) {

}

void Pranium::onMined(Unit *unit) {
    //todo drop pranium
}

void Pranium::generatePranium(Model *model) {
    auto parent = getEntity();
    auto render = parent->getComponent<Render>();
    if(render != nullptr){
        parent->removeComponentFromMap(render);
    }
    parent->addComponent(std::make_unique<Render>(model));


}
