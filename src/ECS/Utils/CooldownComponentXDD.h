//
// Created by igork on 22.06.2024.
//

#ifndef SCRUB_SQUAD_COOLDOWNCOMPONENTXDD_H
#define SCRUB_SQUAD_COOLDOWNCOMPONENTXDD_H
#include "ECS/Component.h"

class CooldownComponentXDD : public Component {
public:
    CooldownComponentXDD(float cooldown) : cooldown(cooldown) {
        name = "CooldownComponentXDD";
    }
    float cooldown;

    void UpdateImpl() override;

};


#endif //SCRUB_SQUAD_COOLDOWNCOMPONENTXDD_H
