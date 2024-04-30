//
// Created by igork on 18.04.2024.
//

#ifndef ZTGK_UNITSYSTEM_H
#define ZTGK_UNITSYSTEM_H
#include "ECS/System.h"
#include "Unit.h"

class UnitSystem : public System{
public:
    UnitSystem();

    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override;
    int getNumComponentTypes() override {return 1;};

    void showImGuiDetailsImpl(Camera *camera) override;

    void UpdateImpl() override;

    void selectUnit(Unit* unit);
    void deselectUnit(Unit* unit);
    void deselectAllUnits();

    std::vector<Unit* > selectedUnits;

    std::vector<Unit *> unitComponents;
private:
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(Unit))
    };
};


#endif //ZTGK_UNITSYSTEM_H
