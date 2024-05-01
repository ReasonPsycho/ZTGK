//
// Created by redkc on 23/02/2024.
//

#include "SystemManager.h"
#include "System.h"
#include "Utils/Util.h"
#include "tracy/Tracy.hpp"

using namespace ztgk;

System::System() {
    uniqueID = id<ID_POOL_SYSTEM>(); // Assign the current value of nextID and then increment it for the next instance
}

SystemManager *System::getSystemManager() {
    return systemManager;
}

void System::showImGuiDetails(Camera *camera) {
    ZoneTransientN(zoneName,(name).c_str(),true);
    showImGuiDetailsImpl(camera);
}

void System::Update() {
    ZoneTransientN(zoneName,(name).c_str(),true);
    UpdateImpl();
}

