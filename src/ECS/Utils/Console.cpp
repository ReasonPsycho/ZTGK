//
// Created by cheily on 01.04.2024.
//

#include "Console.h"

Console::Console() {}

void Console::imguiWindow() {
    ImGui::Begin("Console", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::MenuItem("Clear")) {
            clear();
        }
        if (ImGui::MenuItem("Test")) {
            log(Entry{
                    "Test debug message.",
                    static_cast<spdlog::level::level_enum>(rand() % 7)
            });
        }
        if (ImGui::MenuItem("Flood")) {
            for (int i = 0; i < 10000; ++i) {
                log("Flood message.", spdlog::level::debug);
            }
        }

        ImGui::EndMenuBar();
    }


    // god bless the clipper for saving fps with high item counts
    clipper.Begin(entries.size());
    while (clipper.Step())
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i) {
            auto &entry = entries[i];
            ImVec4 clr;
            switch (entry.level) {
                case spdlog::level::n_levels: // default
                case spdlog::level::trace:
                    clr = {0.5, 0.5, 0.5, 1};
                    break;
                case spdlog::level::debug:
                    clr = {0, 0.58, 1, 1};
                    break;
                case spdlog::level::info:
                    clr = {0.8, 0.8, 0.8, 1};
                    break;
                case spdlog::level::warn:
                    clr = {1, 0.55, 0, 1};
                    break;
                case spdlog::level::err:
                    clr = {1, 0.3, 0.3, 1};
                    break;
                case spdlog::level::critical:
                    clr = {1, 0, 0, 1};
                    break;
                case spdlog::level::off:
                    clr = {0.61, 0, 1, 1};
                    break;
            }
            ImGui::TextColored(clr, "%s", entry.text.c_str());
        }

    ImGui::End();
}

void Console::log(const Entry &entry) {
    entries.push_back(entry);
}

void Console::log(const std::string &text, spdlog::level::level_enum severity) {
    log(Entry{text, severity});
}

void Console::clear() {
    entries.clear();
}
