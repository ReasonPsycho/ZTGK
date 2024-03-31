//
// Created by redkc on 23/02/2024.
//

#include "System.h"


int System::nextID = 0;

System::System() {
    uniqueID = nextID++; // Assign the current value of nextID and then increment it for the next instance
}