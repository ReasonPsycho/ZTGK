//
// Created by cheily on 08.06.2024.
//

#include "SaveSignal.h"
#include "ECS/SignalQueue/Signal.h"

Signal SaveSignal::signal() {
    return Signal(Signal::signal_types.level_save, std::make_shared<SaveSignal>());
}
