// 
// Created by cheily on 01.04.2024. 
// 
 
#include "ImGuiSpdlogSink.h" 
#include "Util.h" 
#include "Console.h" 
 
void ImGuiSpdlogSink::sink_it_(const spdlog::details::log_msg &msg) { 
    if (console == nullptr) return; 
 
    spdlog::memory_buf_t formatted; 
    formatter_->format(msg, formatted); 
    console->log(fmt::to_string(formatted), msg.level); 
} 
 
void ImGuiSpdlogSink::flush_() { 
    console->clear(); 
} 
