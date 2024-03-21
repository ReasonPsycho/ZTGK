//
// Created by cheily on 20.03.2024.
//

#pragma once

struct Signal;

//todo unsure about this
struct SignalReceiver /*: Component*/ {

    unsigned uid;
    unsigned receive_type_mask = 0;

    //todo virtual if override, if component, no
     virtual void receive(const Signal& signal) {

    }

    SignalReceiver();
    explicit SignalReceiver(unsigned int receiveTypeMask);
    virtual ~SignalReceiver() = default;
};


