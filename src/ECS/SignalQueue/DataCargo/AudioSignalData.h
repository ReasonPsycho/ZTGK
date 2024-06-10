// 
// Created by cheily on 21.03.2024. 
// 
 
#pragma once 
 
 
#include <string> 
#include "SignalData.h" 
 
// todo as necessary for the audio system 
struct AudioSignalData : public SignalData { 
    std::string filepath; 
 
    explicit AudioSignalData(const std::string &filepath, const std::string & message = ""); 
 
    [[nodiscard]] std::string to_string() const override { 
        return std::format("{{message=\"{}\", filepath=\"{}\"}}", message, filepath); 
    } 
 
    static Signal signal(const std::string & filepath, const std::string & message = ""); 
}; 
