//
// Created by cheily on 20.03.2024.
//

#pragma once


#include <deque>
#include <ranges>
#include "Signal.h"
#include "SignalReceiver.h"
#include "ECS/System.h"

class SignalQueue : public System {
public:
    long long timestamp = 0;
    std::deque<Signal> queue = std::deque<Signal>();
    std::vector<SignalReceiver *> receivers = std::vector<SignalReceiver *>();

    void init();
    long long get_delta();
    long long update_delta();

    void update() {
        process_all();
    }
    void process_one(long long delta_time);
    void process_all();

    void post(const Signal &signal);
    void cancel(unsigned signalId);
    std::vector<Signal> peek(unsigned signal_type = 0);

    SignalQueue &operator+=(Signal &signal);
    SignalQueue &operator-=(Signal &signal);
    SignalQueue &operator+=(SignalReceiver *receiver);
    SignalQueue &operator-=(SignalReceiver *receiver);

    std::array<std::type_index, 1> component_types = {std::type_index(typeid(SignalReceiver))};
    void addComponent(void *component) override;
    const type_index *getComponentTypes() override { return reinterpret_cast<const type_index *>(&component_types); };
    int getNumComponentTypes() override { return 1; };

};

