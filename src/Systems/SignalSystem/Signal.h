//
// Created by cheily on 20.03.2024.
//

#pragma once

#include <functional>
#include <any>
#include <chrono>

struct s_signal_types {
    unsigned test_signal;
    unsigned keyboard_signal;
    unsigned mouse_signal;
    unsigned audio_signal;

    s_signal_types();
};

struct SignalData;


struct Signal {
    static s_signal_types signal_types;

    // initialize this, 0 will not be picked up by any receivers
    unsigned stype = 0;
    // auto-init, effectively const but setting that breaks default ops, don't change during lifetime
    unsigned sid;

    // optional, mainly for logging
    std::string message;
    // leave 0 if signal is immediate, otherwise time_to_live in millis (update_delta unit)
    long long time_to_live = 0;
    // Signal Receivers should change this to TRUE if they want to stop the signal from propagating further down the chain
    bool consume = false;
    // leave 0 if message is general, to be processed by any receiver listening to this signal type
    unsigned receiver_id = 0;
    // data cargo, type inferred from stype and manually any_cast; check presence with std::any::has_value
    //todo void * or union this instead, inspired by sdl event types but the union would need to be edited every time there's a new type
    std::any data = std::any();
    // optional callback for the signal to function as a timed event on its own, see std::bind to enqueue param-taking lambdas, default assignment avoids null check
    std::function<void()> callback = []() {};

    Signal();

    explicit Signal(unsigned int signalType, long long ttl = 0, unsigned int receiverId = 0,
                    const std::function<void()> &callback = []() {});

    ~Signal() = default;
};
