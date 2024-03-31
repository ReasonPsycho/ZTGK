//
// Created by redkc on 23/02/2024.
//

#include "System.h"
#include "Utils/Util.h"
using namespace ztgk;

int System::nextID = 0;

System::System() {
    uniqueID = id<ID_POOL_SYSTEM>(); // Assign the current value of nextID and then increment it for the next instance
}