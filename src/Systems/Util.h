//
// Created by cheily on 21.03.2024.
//

#pragma once

#include <atomic>
#include <chrono>

namespace ztgk_util {
    static constexpr short ID_POOL_ENTITY = 0;
    static constexpr short ID_POOL_COMPONENT = 1;
    static constexpr short ID_POOL_SIGNAL = 2;

    template<int POOL>
    constexpr unsigned id();

    static constexpr short MASK_ID_POOL_SIGNAL_TYPE = 0;

    template<int POOL>
    constexpr unsigned mask_id();

    // in millis
    long long time();

}

template<int POOL>
constexpr unsigned ztgk_util::id() {
    static std::atomic<unsigned> _id{0};
    return ++_id;
}

template<int POOL>
constexpr unsigned ztgk_util::mask_id() {
    static std::atomic<unsigned> _id{1};
    auto ret = unsigned(_id);
    _id = _id << 1;
    return ret;
}