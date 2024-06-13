//
// Created by cheily on 15.05.2024.
//

#ifndef ZTGK_HUDCOMPTYPE_H
#define ZTGK_HUDCOMPTYPE_H

#include "ECS/Component.h"

enum hudcType {
    UNDEFINED,
    SPRITE, TEXT,
    HOVERABLE, BUTTON, SLIDER,
    MINIMAP
};
#endif //ZTGK_HUDCOMPTYPE_H
