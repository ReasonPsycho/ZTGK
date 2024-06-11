//
// Created by cheily on 08.06.2024.
//

#include "LoadSignal.h"
#include "ECS/SignalQueue/Signal.h"

Signal LoadSignal::signal() {
    return Signal(Signal::signal_types.level_load, std::make_shared<LoadSignal>());
}
