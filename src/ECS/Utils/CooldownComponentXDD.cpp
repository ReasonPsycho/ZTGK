//
// Created by igork on 22.06.2024.
//

#include "CooldownComponentXDD.h"
#include "ECS/Utils/Time.h"
#include "ECS/Entity.h"
void CooldownComponentXDD::UpdateImpl() {
    cooldown -= Time::Instance().DeltaTime();
    if(cooldown < 0){
        parentEntity->removeComponentFromMap(this);
    }
}
