//
// Created by cheily on 01.04.2024.
//

#include "ImGuiSpdlogSink.h"
#include "Util.h"

void ImGuiSpdlogSink::sink_it_(const spdlog::details::log_msg &msg) {
    spdlog::memory_buf_t formatted;
    formatter_->format(msg, formatted);
    ztgk::console.log(fmt::to_string(formatted), msg.level);
}

void ImGuiSpdlogSink::flush_() {
    ztgk::console.clear();
}
