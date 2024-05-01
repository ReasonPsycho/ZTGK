//
// Created by cheily on 01.04.2024.
//

#pragma once

#include "spdlog/sinks/base_sink.h"
#include <mutex>

class Console;

class ImGuiSpdlogSink : public spdlog::sinks::base_sink <std::mutex> {
public:
    Console * console;

protected:
    void sink_it_(const spdlog::details::log_msg &msg) override;
    void flush_() override;
};
