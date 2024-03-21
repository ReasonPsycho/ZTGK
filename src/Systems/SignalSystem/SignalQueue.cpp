//

#include "SignalQueue.h"
#include "Systems/Util.h"

//
// Created by cheily on 20.03.2024.
void SignalQueue::init() {
    update_delta();
}

long long SignalQueue::get_delta() {
    return ztgk_util::time() - timestamp;
}

long long SignalQueue::update_delta() {
    auto t = timestamp;
    timestamp = ztgk_util::time();
    return timestamp - t;
}

void SignalQueue::process_one(long long deltatime) {
    auto signal = queue.front();
    queue.pop_front();
    signal.time_to_live -= deltatime;
    if ( signal.time_to_live > 0 ) {
        queue.push_back(signal);
        return;
    }

    auto filtered = receivers | std::views::filter( [signal](SignalReceiver * receiver) {
        return ( signal.receiver_id == receiver->uid || (signal.stype & receiver->receive_type_mask) != 0 );
    } );

    for (auto & receiver : filtered) {
        receiver->receive(signal);
        if ( signal.consume ) break;
    }

    signal.callback();
}

void SignalQueue::process_all() {
    auto delta = update_delta();

    for (int i = 0; i < queue.size(); ++i) {
        process_one(delta);
    }
}

void SignalQueue::post(const Signal &signal) {
    queue.push_back(signal);
}

void SignalQueue::cancel(unsigned int signalId) {
    std::erase_if(queue, [signalId](const Signal &signal) { return signal.sid == signalId; });
}

std::vector<Signal> SignalQueue::peek(unsigned int signal_type) {
    auto filtered = queue | std::ranges::views::filter( [signal_type](const Signal& signal) {
        return signal_type == 0 || signal.stype == signal_type;
    });
    std::vector<Signal> ret;
    std::copy(filtered.begin(), filtered.end(), ret.begin());
    return ret;
}

SignalQueue &SignalQueue::operator+=(Signal &signal) {
    post(signal);
    return *this;
}

SignalQueue &SignalQueue::operator-=(Signal &signal) {
    cancel(signal.sid);
    return *this;
}

SignalQueue &SignalQueue::operator+=(SignalReceiver *receiver) {
    receivers.push_back(receiver);
    return *this;
}

SignalQueue &SignalQueue::operator-=(SignalReceiver *receiver) {
    std::erase(receivers, receiver);
    return *this;
}

void SignalQueue::addComponent(void *component) {
    receivers.push_back( (SignalReceiver*)component );
}
