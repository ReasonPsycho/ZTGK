//
// Created by cheily on 08.04.2024.
//

#pragma once

#include <memory>
#include "ECS/Scene.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Audio/AudioManager.h"

struct Cursor;
class SignalQueue;
class SignalReceiver;
struct GLFWwindow;
class ModelLoadingManager;
struct Text;

namespace ztgk::game {
    enum EMOTES {
        BUBBLE_CUTE,
        BUBBLE_TONGUE,
        BUBBLE_HAPPY,
        P_BUBBLE_CUTE,
        P_BUBBLE_SAD,
        P_BUBBLE_TONGUE,
        P_BUBBLE_EEPY,
        Y_BUBBLE_SAD,
        Y_BUBBLE_ANGRY,
        Y_BUBBLE_SUS,
        CLEAN_BUBBLE1,
        CLEAN_BUBBLE2,
        PRANIUM
    };



    struct s_ui_data {
        enum class ui_phase {
            MAIN_MENU,
            GAME
        };

        ui_phase phase = ui_phase::MAIN_MENU;
        unsigned tracked_unit_id = -1;
        unsigned gr_game;
        unsigned gr_map;
        unsigned gr_middle;
        unsigned gr_actions;
        unsigned gr_top;
        unsigned gr_item;
        unsigned gr_pause;
        unsigned gr_settings;
        unsigned gr_menu;
        unsigned gr_credits;
        unsigned gr_loadScreen;
        unsigned gr_mainMenu;
        unsigned gr_w1_offensive;
        unsigned gr_w1_passive;
        unsigned gr_w2_offensive;
        unsigned gr_w2_passive;
        unsigned gr_game_won;
        unsigned gr_game_lost;

        Text * txt_time_display = nullptr;
        Text * txt_pranium_counter = nullptr;
        Text * txt_unit_counter = nullptr;

        float game_start_time = 0;
        float game_save_time = 0;
    };
    extern s_ui_data ui_data;

    extern GLFWwindow * window;
    extern Scene * scene;
    extern Model * cube_model;
    extern Camera * camera;
    extern SignalQueue * signalQueue;
    extern Model * washingMachineModel;
    extern Model * praniumModel;
    extern AudioManager * audioManager;
    extern ModelLoadingManager * modelLoadingManager;
    extern SignalReceiver * selectionHandler;

    extern Cursor cursor;

    extern int pranium_needed_to_win;
    extern std::atomic<bool> pause;
    extern std::atomic<bool> pause_render;

    extern glm::ivec2 window_size;
    extern float saturationMultiplayer;
    extern float lightMultiplayer;
    extern int toon_color_levels;
    extern bool fullscreen;
    extern Model * playerModel;
    extern Model* bugModel;
    extern Model* shroomModel;
    extern Model* oreModel;
    extern Model* chestModel;
    extern Model* projectileModel;

    //Items <33333
    extern Model* mopModel;
    extern Model* mopObrotowyModel;
    extern Model* tideGun;
    extern Model* superPlyn;
    extern Model* kulki;
    extern Model* healingo;
    extern Model* proszek;
    
    
    extern Model* tidyPodLauncherModel;
    extern Model* hangerMopModel;
    
    
    
    
    extern Model* hangerMopObrotowyModel;
    extern Model* hangerTidyPodLauncherModel;


    extern bool enableWashingMachineSwaying;


    extern bool gameStarted;
    extern bool gameWon;
    extern bool gameLost;

    extern std::unordered_map<EMOTES, std::shared_ptr<Texture>> emotes;

}