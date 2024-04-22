//
// Created by cheily on 01.04.2024.
//

#include "Console.h"
#include "Util.h"

Console::Console(const std::string & name) : name(name) {}

Console::Console(const custom_menus_t & custom_menus, const std::string & name)
: name(name), custom_menus(custom_menus) {}

void Console::imguiWindow() {
    ImGui::Begin(std::format("{0}##Console_{0}", name).c_str(), nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
        for ( auto & cmenu : custom_menus ) {
            if (ImGui::MenuItem(cmenu.first.c_str())) {
                cmenu.second();
            }
        }
        if ( !custom_menus.empty() )
            ImGui::Separator();

        if (ImGui::MenuItem("Clear##DefClear")) {
            clear();
        }
        if (ImGui::MenuItem("Test##DefTest")) {
            log(Entry{
                    "Test debug message.",
                    static_cast<spdlog::level::level_enum>(rand() % 7)
            });
        }
        if (ImGui::MenuItem("Flood##DefFlood")) {
            for (int i = 0; i < 10000; ++i) {
                log("Flood message.", spdlog::level::debug);
            }
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Top##DefTop")) {
            ImGui::SetScrollFromPosY(clipper.StartPosY - ImGui::GetWindowPos().y);
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("This will not stop auto-scroll when logging fast. Scroll up once to break it and then press this.");
        if (ImGui::MenuItem("Bottom##DefBottom")) {
            float item_pos_y = clipper.StartPosY + clipper.ItemsHeight * (entries.size());
            ImGui::SetScrollFromPosY(item_pos_y - ImGui::GetWindowPos().y);
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

    if (scroll_down && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
        scroll_down = false;
    }
    ImGui::End();
}

void Console::log(const Entry &entry) {
    entries.push_back(entry);
    scroll_down = true;
}

void Console::log(const std::string &text, spdlog::level::level_enum severity) {
    log(Entry{text, severity});
    scroll_down = true;
}

void Console::clear() {
    entries.clear();
}
