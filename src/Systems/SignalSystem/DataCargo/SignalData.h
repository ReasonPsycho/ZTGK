//
// Created by cheily on 21.03.2024.
//

#pragma once

#include <string>
#include <format>
struct Signal;

struct SignalData {
    std::string message;

    explicit SignalData(const std::string &message = "");
    [[nodiscard]] virtual std::string to_string() const { return std::format("{{message=\"{}\"}}", message); }

    static Signal signal(const std::string & message = "");

    virtual ~SignalData() = default;
};
