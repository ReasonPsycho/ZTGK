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

    SignalQueue();
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

    SignalQueue &operator+=(const Signal& signal);
    SignalQueue &operator-=(const Signal& signal);
    SignalQueue &operator+=(SignalReceiver *receiver);
    SignalQueue &operator-=(SignalReceiver *receiver);

    std::array<std::type_index, 1> component_types = {std::type_index(typeid(SignalReceiver))};
    void addComponent(void *component) override;
    void removeComponent(void* component) override;

    const std::type_index *getComponentTypes() override { return reinterpret_cast<const std::type_index *>(&component_types); };
    int getNumComponentTypes() override { return 1; };
    void showImGuiDetails(Camera *camera);


    // editor
    struct editor_s_new_signal_config {
        int choice{0};
        bool enablelog{false};
        SignalReceiver * logger;
        std::vector<std::string> log{};

        const static int message_size = 100;

        float defertime{0};
        unsigned receiver{0};
        bool consume{false};
        char message[message_size]{"Spoofed event."};

        int nsignals{1};
        // keypress
        int key{0}, scancode{0}, kaction{0}, kmods{0};
        // scroll
        double xoff{0}, yoff{0};
        // mouse move
        double xnew{0}, ynew{0}, xold{0}, yold{0};
        // mouse button
        int button{0}, maction{0}, mmods{0};
        // audio
        char soundpath[message_size]{};

        // hud mapping
        bool all{false};
        int componentID{-1}, oldGroupID{-1}, newGroupID{-1};
        // hud remove group
        int groupId{-1};

        static SignalReceiver * new_logger();
    };
    static editor_s_new_signal_config editor_new_signal_config;
};

