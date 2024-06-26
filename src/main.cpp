
#pragma region Includes


#pragma region Tracy
#if defined( __clang__ ) || defined(__GNUC__)
# define TracyFunction __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
# define TracyFunction __FUNCSIG__
#endif

#include <tracy/Tracy.hpp >

#pragma endregion Tracy

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <ImGuizmo.h>
#include <cstdio>

#include "ECS/Utils/Cursor.h"
#include "ECS/SignalQueue/SignalQueue.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseMoveSignalData.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseButtonSignalData.h"
#include "ECS/SignalQueue/DataCargo/KeySignalData.h"
#include "ECS/Unit/Mining/MiningSystem.h"

//Instancing
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions
#include <spdlog/spdlog.h>
#include <iostream>
#include "spdlog/sinks/basic_file_sink.h"
#include "ECS/Light/LightSystem.h"
#include "ECS/Render/RenderSystem.h"
#include "ECS/Utils/Util.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Scene.h"
#include "ECS/Unit/Unit.h"
#include "ECS/Utils/RNG.h"


#define IMGUI_IMPL_OPENGL_LOADER_GLAD //THIS HAS TO BE RIGHT BEFORE THE PIPELINE
#define STB_IMAGE_IMPLEMENTATION

#include "ECS/Render/Pipelines/Phong/PhongPipeline.h"
#include "ECS/Render/Postprocessing/BloomPostProcess.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Entity.h"

#include "ECS/Grid/Grid.h"

#include "ECS/Render/Primitives/PBRPrimitives.h"
#include "ECS/Render/Primitives/Primitives.h"

#include "ECS/Utils/Time.h"

#include "ECS/HUD/TextRenderer.h"
#include "ECS/HUD/SpriteRenderer.h"

#include "ECS/Utils/ImGuiSpdlogSink.h"
#include "ECS/HUD/HUD.h"
#include "ECS/Raycasting/Colliders/BoxCollider.h"
#include "ECS/Raycasting/Ray.h"
#include "ECS/Render/WireRenderSystem.h"
#include "ECS/Raycasting/CollisionSystem.h"
#include "ECS/Render/InstanceRenderSystem.h"
#include "ECS/Unit/UnitAI/UnitAI.h"
#include "ECS/Unit/UnitAI/StateMachine/States/IdleState.h"
#include "ECS/Unit/UnitSystem.h"
#include "ECS/SaveSystem/LevelSaving.h"
#include "ECS/LevelGenerator/LevelGenerator.h"
#include "ECS/Unit/Equipment/InventoryManager.h"
#include "ECS/Unit/Mining/MineableChest.h"
#include "ECS/Gameplay/WashingMachine.h"
#include "ECS/Audio/AudioManager.h"
#include "ECS/Render/ModelLoading/ModelLoadingManager.h"
#include "ECS/Unit/Equipment/Projectile/ProjectileSystem.h"
#include "ECS/Render/ParticleSystem.h"

#include <filesystem>

namespace fs = std::filesystem;
#pragma endregion Includes

#pragma region constants

Scene scene;
string modelPath = "res/models/asteroid/Asteroid.fbx";
string modelPathGabka = "res/models/gabka/pan_gabka.fbx";
string modelPathGabkaMove = "res/models/gabka/pan_gabka_move.fbx";
string modelPathGabkaIdle = "res/models/gabka/pan_gabka_idle.fbx";
string modelPathGabkaMine = "res/models/gabka/pan_gabka_mine.fbx";
string modelPathGabkaAttack = "res/models/gabka/pan_gabka_attack_right.fbx";
string modelPathZuczek = "res/models/zuczek/Zuczek.fbx";
string modelPathZuczekTest = "res/models/zuczek/Zuczek_run - copia.fbx";
string modelPathZuczekAttack = "res/models/zuczek/Zuczek_attack - copia.fbx";
string modelPathZuczekIddle = "res/models/zuczek/Zuczek_sleep - copia.fbx";
string modelPathZuczekMove = "res/models/zuczek/Zuczek_run - copia.fbx";
string modelPathWall = "res/models/BathroomWall/BathroomWall.fbx";
string tileModelPath = "res/models/plane/Plane.fbx";
string washingMachinePath = "res/models/washingmachine/pralka.fbx";
string modelProjectilePath = "res/models/projectile/projectile.fbx";
string modelChestPath = "res/models/chest/chest.fbx";
string modelMopPath = "res/models/items/mop/mop.fbx";
string modelMopObrotowyPath = "res/models/items/mopObrotowy/mopObrotowy.fbx";
string modelTidyPodLauncherPath = "res/models/items/tideGun/tideGun.fbx";
string modelPraniumPath = "res/models/pranium/praniumTemp.fbx";
string modelPathShroom = "res/models/Mushroom/shroom.fbx";
string modelPathShroomMove = "res/models/Mushroom/shroom_move.fbx";
string modelPathShroomIdle = "res/models/Mushroom/shroom_idle.fbx";
string modelPathShroomSpit = "res/models/Mushroom/shroom_spit.fbx";

Model *tileModel;
Model *model;
Model *gabka;
Model *zuczek;
Model *zuczekTest;
Model *wall;
Model *washingMachineModel;
Model *chestModel;
Model *cubeModel;
Model *quadModel;
Model *projectileModel;
Model *mopModel;
Model *mopObrotowyModel;
Model *tidyPodLauncherModel;
Model *praniumModel;
Model *shroomModel;


unsigned bggroup, zmgroup;
Sprite *zmspr;
Text *zmtxt;
StateManager *stateManager;
Text text = {};
BloomPostProcess bloomSystem;

shared_ptr<spdlog::logger> file_logger;
#pragma endregion constants

//MY SHIT FOR DEBUGING, IF I FORGOT TO REMOVE FEEL FREE TO DO IT <3
bool isXpressed = false;
int radiusToRemove = 5;


#pragma region Function definitions

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool init();

void init_systems();

void load_enteties();

void init_managers();

void load_sounds();

void load_hud();

void load_units();

void init_imgui();

void init_camera();

void init_time();

void before_frame();

void input();

void update();

void render();

void wireFrameRender();

void imgui_begin();

void imgui_render();

void imgui_end();

void end_frame();

void cleanup();

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

void handle_picking(GLFWwindow *window, int button, int action, int mods);

void handleControls(int key, int scancode, int action, int mods);

void processInput(GLFWwindow *window);

void update_dragged_tiles();

void gen_and_load_lvl(bool gen_new_lvl = false);

#pragma endregion Function definitions

#pragma region Orginal set up

constexpr int32_t WINDOW_WIDTH = 1920;
constexpr int32_t WINDOW_HEIGHT = 1080;

GLFWwindow *window = nullptr;

// Change these to lower GL version like 4.5 if GL 4.6 can't be initialized on your machine
const char *glsl_version = "#version 460";
constexpr int32_t GL_VERSION_MAJOR = 4;
constexpr int32_t GL_VERSION_MINOR = 6;

//Not my things but I could probably change them

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

#pragma endregion Orginal set up

#pragma region My set up

//Camera set up
int display_w, display_h;
Camera camera(glm::vec3(90.0f, 40.0f, 90.0f), glm::vec3(0, 1.0f, 0), 30, -50, 0.1, 1000.0f);

Primitives primitives;

PBRPrimitives pbrprimitives;

float lastY;
float lastX;

Entity *playerUnit;

std::vector<Vector2Int> selectedTiles;
std::vector<Tile *> tilesSelectedToMine;
std::vector<Tile *> movementTargets;
std::vector<Tile *> combatTargets;

bool isLeftMouseButtonHeld = false;
float LmouseHeldStartTime = 0.0f;
float LmouseHeldReleaseTime = 0.0f;

bool isRightMouseButtonHeld = false;
float RmouseHeldStartTime = 0.0f;
float RmouseHeldReleaseTime = 0.0f;

glm::vec2 mouseHeldStartPosScr;

glm::vec3 mouseHeldStartPos;
glm::vec3 mouseHeldEndPos;

float lastLeftClickTime = 0.0f;
float lastRightClickTime = 0.0f;

// timing
double deltaTime = Time::Instance().DeltaTime();
int timeStep = 1;
bool timeStepKeyPressed = false;

#pragma endregion My set up

#pragma region ZTGK-Global

#pragma endregion


int main(int, char **) {

#pragma region Init

    if (!init()) {
        spdlog::error("Failed to initialize project!");
        return EXIT_FAILURE;
    }
    spdlog::info("Initialized OpenGL.");

    init_imgui();
    spdlog::info("Initialized ImGui.");

    init_time();
    spdlog::info("Initialized system timer.");

    spdlog::info("Initialized signal queue.");

    init_camera();
    spdlog::info("Initialized camera and viewport.");

    init_systems();
    spdlog::info("Initialized textures and vertices.");

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDepthFunc(GL_LEQUAL);

    glfwSwapInterval(1);

    init_managers();
    spdlog::info("Intialized non-system manager components.");

    load_hud();
    spdlog::info("Initialized HUD.");

    load_enteties();
    spdlog::info("Initialized entities.");

    scene.systemManager.FinishInnit();
#pragma endregion Init

    // Main loop
    while (!glfwWindowShouldClose(window)) {


        //Setting up things for the rest of functionalities (ex. update_delta time)
        before_frame();

        // Process I/O operations here
        input();

        // UpdateImpl game objects' state here
        update();

        // OpenGL rendering code here
        if (!ztgk::game::pause_render)
            render();

        // Draw ImGui
#ifdef DEBUG_BUILD
        imgui_begin();
        imgui_render(); // edit this function to add your own ImGui controls
        imgui_end(); // this call effectively renders ImGui
#endif

        // End frame and swap buffers (double buffering)
        end_frame();

    }

    file_logger->info("Cleanup");
    cleanup();
    // Cleanup
    return 0;
}


#pragma region Functions

void cleanup() {
    //Orginal clean up
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    *ztgk::game::signalQueue -= ztgk::game::selectionHandler;
    delete ztgk::game::selectionHandler;
    ztgk::game::audioManager->close();

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool init() {
    std::srand(std::time(0)); //Just to be sure
    spdlog::set_level(spdlog::level::trace);
    ztgk::console.level(spdlog::level::trace);

    // Get current date and time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

// Convert time to local time
    std::tm *local_time = std::localtime(&now_time);

// Create a filename with date
    std::ostringstream filename;
    filename << "res/logs/logs_"
             << (local_time->tm_year + 1900) // Year starts from 1900
             << "-" << (local_time->tm_mon + 1) // Month starts from 0
             << "-" << local_time->tm_mday  // Day of month
             << "-" << local_time->tm_hour  // hour
             << "-" << local_time->tm_min  // minute
             << ".txt";
    try {

        file_logger = spdlog::basic_logger_mt("file_logger", filename.str());
        file_logger->flush_on(spdlog::level::info);
        file_logger->info("Init log file");
    }
    catch (const spdlog::spdlog_ex &ex) {
        spdlog::error("File log initialization failed.");
    }

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        spdlog::error("Failed to initalize GLFW!");
        file_logger->error("Failed to initalize GLFW!");
        return false;
    }

    // GL 4.6 + GLSL 460
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#ifdef RELEASE_BUILD
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
#endif

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Scrub Squad", NULL, NULL);

    GLFWimage icons[1];
    int width, height, nrChannels;
    unsigned char *data = stbi_load("res/textures/icons/pick-me.png", &width, &height, &nrChannels, 0);
    if (data) {
        icons[0].pixels = data;   // Pixel data will be loaded from 'path_to_your_icon.png'
        icons[0].width = width;   // Width should be the exact width of the image
        icons[0].height = height; // Height should be the exact height of the image
        glfwSetWindowIcon(window, 1, icons);
        stbi_image_free(data);
    }

    // Create window with graphics context
    if (window == NULL) {
        spdlog::error("Failed to create GLFW Window!");
        file_logger->error("Failed to create GLFW Window!");
        return false;
    }


    glfwMakeContextCurrent(window);
    bool err = !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (err) {
        spdlog::error("Failed to initialize OpenGL loader!");
        file_logger->error("Failed to initialize OpenGL loader!");
        return false;
    }

    stbi_set_flip_vertically_on_load(true);
    return true;
}


void init_systems() {
    ztgk::game::scene = &scene;
    ztgk::game::camera = &camera;
    ztgk::game::window = window;
    scene.systemManager.addSystem(std::make_unique<AudioManager>());


    ztgk::game::audioManager = scene.systemManager.getSystem<AudioManager>();
    ztgk::game::audioManager->init();
    spdlog::info("Initialized audio manager.");
    load_sounds();
    spdlog::info("Loaded sounds.");


    primitives.Init();


    scene.systemManager.addSystem(std::make_unique<SignalQueue>());
    ztgk::game::signalQueue = scene.systemManager.getSystem<SignalQueue>(); //TODO gregori and ijgor just pls use scene to get systems
    scene.systemManager.getSystem<SignalQueue>()->init();
    ztgk::game::cursor.init();

    scene.systemManager.addSystem(std::make_unique<LightSystem>(&camera, &scene));
    scene.systemManager.addSystem(std::make_unique<RenderSystem>());
    scene.systemManager.addSystem(std::make_unique<InstanceRenderSystem>(&camera));
    scene.systemManager.addSystem(std::make_unique<WireRenderSystem>(&primitives, &camera));
    scene.systemManager.addSystem(std::make_unique<Grid>(&scene, 100, 100, 2.0f, Vector3(0, 0, 0)));
    scene.systemManager.addSystem(std::make_unique<CollisionSystem>());
    scene.systemManager.addSystem(std::make_unique<UnitSystem>());
    scene.systemManager.addSystem(std::make_unique<WashingMachine>(4, 10));
    scene.systemManager.addSystem(std::make_unique<PhongPipeline>());
    scene.systemManager.addSystem(std::make_unique<MiningSystem>());
    scene.systemManager.addSystem(std::make_unique<ProjectileSystem>());
    scene.systemManager.addSystem(std::make_unique<ParticleSystem>());
    scene.systemManager.getSystem<ParticleSystem>()->Innit();

    scene.systemManager.getSystem<PhongPipeline>()->Init(&camera, &primitives);
    bloomSystem.Init(camera.saved_display_w, camera.saved_display_h);
    Color myColor = {255, 32, 21, 0};  // This defines your color.
    pbrprimitives.Init();
    MaterialPhong materialPhong = MaterialPhong(myColor);
    cubeModel = new Model(pbrprimitives.cubeVAO, materialPhong,
                          vector<GLuint>(pbrprimitives.cubeIndices, pbrprimitives.cubeIndices + 36));
    ztgk::game::cube_model = cubeModel;
    scene.systemManager.getSystem<WireRenderSystem>()->boxModel = cubeModel;
    scene.systemManager.getSystem<WireRenderSystem>()->Innit();

    scene.systemManager.addSystem(std::make_unique<HUD>());
    scene.systemManager.getSystem<HUD>()->init();

    scene.systemManager.getSystem<UnitSystem>()->init();

    ztgk::game::selectionHandler = new SignalReceiver(
            Signal::signal_types.mouse_button_signal | Signal::signal_types.keyboard,
            [](const Signal &signal) {
                if (signal.stype == Signal::signal_types.mouse_button_signal) {
                    auto data = std::dynamic_pointer_cast<MouseButtonSignalData>(signal.data);
                    handle_picking(window, data->button, data->action, data->mods);
                } else if (signal.stype == Signal::signal_types.keyboard) {
                    auto data = std::dynamic_pointer_cast<KeySignalData>(signal.data);
                    handleControls(data->key, data->scancode, data->action, data->mods);
                }
            }
    );
    *ztgk::game::signalQueue += ztgk::game::selectionHandler;
}

void init_managers() {
    auto ent = scene.addEntity("Controllers");
    ent->addComponent(make_unique<InventoryManager>());
    ent->getComponent<InventoryManager>()->init();
}

void load_sounds() {
    //background music
    ztgk::game::audioManager->loadSound("res/sounds/ambient1.mp3", "ambient1");
    ztgk::game::audioManager->loadSound("res/sounds/ambient2.mp3", "ambient2");
    ztgk::game::audioManager->loadSound("res/sounds/ambient3.mp3", "ambient3");
    ztgk::game::audioManager->loadSound("res/sounds/ambient4.mp3", "ambient4");


    //SET TO 0 CUZ IM LISTENING TO MY OWN MUSIC, CHANGE LATER XD   vvvvvvvvvvvvv
    ztgk::game::audioManager->setVolumeForGroup("ambient", 5);

    //intro music
    ztgk::game::audioManager->loadSound("res/sounds/sfx_intro_music.mp3", "sfx_intro_music");

    //lose music
    ztgk::game::audioManager->loadSound("res/sounds/sfx_lose.mp3", "sfx_lose");

    //win music
    ztgk::game::audioManager->loadSound("res/sounds/sfx_win.mp3", "sfx_win");

    //punch sounds
    ztgk::game::audioManager->loadSound("res/sounds/sfx_punch1.wav", "sfx_punch1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_punch2.wav", "sfx_punch2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_punch3.wav", "sfx_punch3");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_punch4.wav", "sfx_punch4");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_punch5.wav", "sfx_punch5");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_punch6.wav", "sfx_punch6");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_punch7.wav", "sfx_punch7");

    //bubble pop
    ztgk::game::audioManager->loadSound("res/sounds/sfx_bubble1.mp3", "sfx_bubble1");

    //bubbles bulbulbulbul
    ztgk::game::audioManager->loadSound("res/sounds/sfx_bubbles.mp3", "sfx_bubbles");

    //bug walking
    ztgk::game::audioManager->loadSound("res/sounds/sfx_bug1.mp3", "sfx_bug2");

    //clicks for UI
    ztgk::game::audioManager->loadSound("res/sounds/sfx_click1.mp3", "sfx_click1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_click2.mp3", "sfx_click2");

    //death sounds OOF
    ztgk::game::audioManager->loadSound("res/sounds/sfx_deathEnemy1.mp3", "sfx_deathEnemy1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_deathEnemy2.mp3", "sfx_deathEnemy2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_deathSponge1.wav", "sfx_deathSponge1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_deathSponge2.wav", "sfx_deathSponge2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_deathSponge3.mp3", "sfx_deathSponge3");

    //gabka walking
    ztgk::game::audioManager->loadSound("res/sounds/sfx_gabka1.mp3", "sfx_gabka1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_gabka2.mp3", "sfx_gabka2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_gabka3.mp3", "sfx_gabka3");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_gabka4.mp3", "sfx_gabka4");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_gabka5.mp3", "sfx_gabka5");

    //gabka celaning tiles
    ztgk::game::audioManager->loadSound("res/sounds/sfx_idle1.mp3", "sfx_idle1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_idle2.mp3", "sfx_idle2");

    //mining sound
    ztgk::game::audioManager->loadSound("res/sounds/sfx_mining1.mp3", "sfx_mining1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_mining2.mp3", "sfx_mining2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_mining3.mp3", "sfx_mining3");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_mining4.mp3", "sfx_mining4");

    //pralka 1 - slow pralka sounds
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pralka1.mp3", "sfx_pralka1");

    //pralka 2 - crazy fast pralka sounds
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pralka2.mp3", "sfx_pralka2");

    ztgk::game::audioManager->setSoundVolume("sfx_pralka2", 100);
    ztgk::game::audioManager->setSoundVolume("sfx_pralka2", 50);

    //quack
    ztgk::game::audioManager->loadSound("res/sounds/sfx_rubberduck1.mp3", "sfx_rubberduck1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_rubberduck2.mp3", "sfx_rubberduck2");

    //pick
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_duty1.mp3", "sfx_pickUnit_duty1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_huhu1.mp3", "sfx_pickUnit_huhu1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_huhu2.mp3", "sfx_pickUnit_huhu2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_orders1.mp3", "sfx_pickUnit_orders1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_orders2.mp3", "sfx_pickUnit_orders2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_yessir1.mp3", "sfx_pickUnit_yessir1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_yessir2.mp3", "sfx_pickUnit_yessir2");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_yessir3.mp3", "sfx_pickUnit_yessir3");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_pickUnit_yessir4.mp3", "sfx_pickUnit_yessir4");



    //healing
    ztgk::game::audioManager->loadSound("res/sounds/sfx_heal1.mp3", "sfx_heal1");
    ztgk::game::audioManager->loadSound("res/sounds/sfx_heal2.mp3", "sfx_heal2");

    //click
    ztgk::game::audioManager->loadSound("res/sounds/click_click1.mp3", HUDButton::sound_light);
    ztgk::game::audioManager->loadSound("res/sounds/click_click2.mp3", HUDButton::sound_normal);
    ztgk::game::audioManager->setVolumeForGroup("click", 6);

}

void load_enteties() {
    Color color = {255, 255, 255, 255}; // this is equivalent to white color

    int n = sizeof(pbrprimitives.quadIndices) / sizeof(pbrprimitives.quadIndices[0]);

    // Convert the array to a vector
    std::vector<unsigned int> vec(pbrprimitives.quadIndices, pbrprimitives.quadIndices + n);
    ztgk::game::modelLoadingManager = new ModelLoadingManager;
    ztgk::game::modelLoadingManager->Innit();
    tileModel = ztgk::game::modelLoadingManager->GetModel(tileModelPath);
    model = ztgk::game::modelLoadingManager->GetModel(modelPath);
    gabka = ztgk::game::modelLoadingManager->GetModel(modelPathGabka);
    zuczek = ztgk::game::modelLoadingManager->GetModel(modelPathZuczek);
    zuczekTest = ztgk::game::modelLoadingManager->GetModel(modelPathZuczekTest);
    wall = ztgk::game::modelLoadingManager->GetModel(modelPathWall);
    washingMachineModel = ztgk::game::modelLoadingManager->GetModel(washingMachinePath);
    chestModel = ztgk::game::modelLoadingManager->GetModel(modelChestPath);
    projectileModel = ztgk::game::modelLoadingManager->GetModel(modelProjectilePath);
    mopModel = ztgk::game::modelLoadingManager->GetModel(modelMopPath);
    mopObrotowyModel = ztgk::game::modelLoadingManager->GetModel(modelMopObrotowyPath);
    tidyPodLauncherModel = ztgk::game::modelLoadingManager->GetModel(modelTidyPodLauncherPath);
    praniumModel = ztgk::game::modelLoadingManager->GetModel(modelPraniumPath);

    //quadModel = new Model(pbrprimitives.quadVAO, MaterialPhong(color), vec);
    quadModel = new Model(pbrprimitives.subdividedPlaneVAO[0], MaterialPhong(color), pbrprimitives.subdividedPlanesIndices[0]);

    ztgk::game::washingMachineModel = washingMachineModel;
    ztgk::game::playerModel = gabka;
    ztgk::game::bugModel = zuczekTest;
    ztgk::game::chestModel = chestModel;
    ztgk::game::praniumModel = praniumModel;
    ztgk::game::projectileModel = projectileModel;
    ztgk::game::mopModel = mopModel;
    
    ztgk::game::mopObrotowyModel = mopObrotowyModel;
    ztgk::game::tidyPodLauncherModel = tidyPodLauncherModel;
    ztgk::game::tideGun= ztgk::game::modelLoadingManager->GetModel("res/models/items/tideGun/tideGun.fbx");;
    ztgk::game::superPlyn= ztgk::game::modelLoadingManager->GetModel("res/models/items/superPlyn/superPlyn.fbx");;
    ztgk::game::kulki= ztgk::game::modelLoadingManager->GetModel("res/models/items/kulki/kulki.fbx");;
    ztgk::game::healingo= ztgk::game::modelLoadingManager->GetModel("res/models/items/healingo/healingo.fbx");;
    ztgk::game::proszek= ztgk::game::modelLoadingManager->GetModel("res/models/items/proszek/proszek.fbx");;    
    
    
    ztgk::game::shroomModel = ztgk::game::modelLoadingManager->GetModel(modelPathShroom);


    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::BUBBLE_CUTE, std::make_shared<Texture>("res/textures/emotes/blue_3.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::BUBBLE_TONGUE, std::make_shared<Texture>("res/textures/emotes/blue_p.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::BUBBLE_HAPPY, std::make_shared<Texture>("res/textures/emotes/blue_c.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::P_BUBBLE_CUTE, std::make_shared<Texture>("res/textures/emotes/pink_3.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::P_BUBBLE_SAD, std::make_shared<Texture>("res/textures/emotes/pink_v.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::P_BUBBLE_TONGUE, std::make_shared<Texture>("res/textures/emotes/pink_p.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::P_BUBBLE_EEPY, std::make_shared<Texture>("res/textures/emotes/pink_eep.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::Y_BUBBLE_SAD, std::make_shared<Texture>("res/textures/emotes/yellow_v.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::Y_BUBBLE_ANGRY, std::make_shared<Texture>("res/textures/emotes/yellow_angy.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::Y_BUBBLE_SUS, std::make_shared<Texture>("res/textures/emotes/yellow_sus.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::CLEAN_BUBBLE1, std::make_shared<Texture>("res/textures/emotes/clean_bubble1.png", "")));
    //ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::CLEAN_BUBBLE1, new Texture({255,0,0,50})));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::CLEAN_BUBBLE2, std::make_shared<Texture>("res/textures/emotes/clean_bubble2.png", "")));
    ztgk::game::emotes.insert(std::make_pair(ztgk::game::EMOTES::PRANIUM, std::make_shared<Texture>("res/textures/emotes/pranium_cut.png", "")));


    ztgk::game::scene->systemManager.getSystem<WashingMachine>()->createWashingMachine(washingMachineModel);


    Entity *gameObject;

    /*
       gameObject = scene.addEntity("Wall");;
       gameObject->transform.setLocalPosition(glm::vec3(100, 50, 0));
       gameObject->transform.setLocalScale(glm::vec3(100, 50, 10));
       gameObject->transform.setLocalRotation(glm::quat(glm::vec3(0, 0, 0)));
       gameObject->addComponent(make_unique<Render>(wall));;
   
       gameObject = scene.addEntity("Wall1");;
       gameObject->transform.setLocalPosition(glm::vec3(100, 50, 200));
       gameObject->transform.setLocalScale(glm::vec3(100, 50, 10));
       gameObject->transform.setLocalRotation(glm::quat(glm::vec3(0, 0, 0)));
       gameObject->addComponent(make_unique<Render>(wall));;
   //
       gameObject = scene.addEntity("Wall2");;
       gameObject->transform.setLocalPosition(glm::vec3(0, 50, 100));
       gameObject->transform.setLocalScale(glm::vec3(100, 50, 10));
       gameObject->transform.setLocalRotation((glm::quat(glm::radians(glm::vec3(0, 90, 0)))));
       gameObject->addComponent(make_unique<Render>(wall));;
   //
       gameObject = scene.addEntity("Wall3");;
       gameObject->transform.setLocalPosition(glm::vec3(200, 50, 100));
       gameObject->transform.setLocalScale(glm::vec3(100, 50, 10));
       gameObject->transform.setLocalRotation((glm::quat(glm::radians(glm::vec3(0, 90, 0)))));
       gameObject->addComponent(make_unique<Render>(wall));;

   */

    scene.systemManager.getSystem<LightSystem>()->Init();
    scene.systemManager.getSystem<InstanceRenderSystem>()->tileModel = quadModel;
    scene.systemManager.getSystem<RenderSystem>()->tileModel = quadModel;
    scene.systemManager.getSystem<Grid>()->LoadTileEntities(1.0f);


    scene.systemManager.getSystem<InstanceRenderSystem>()->Innit();

    load_units();


}

void load_units() {
    playerUnit = scene.addEntity("Particle emiter");
    playerUnit->addComponent(make_unique<ParticleEmiter>());
    playerUnit->transform.setLocalPosition(glm::vec3(100, 12, 100));
   
    /*
    playerUnit = scene.addEntity("Mop");
    playerUnit->addComponent(make_unique<Render>(mopModel));
    playerUnit->addComponent(make_unique<ColorMask>());
    playerUnit->addComponent(make_unique<AnimationPlayer>());
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathGabkaMove,ztgk::game::modelLoadingManager ->GetAnimation(modelPathGabkaMove, gabka));
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathGabkaIdle,ztgk::game::modelLoadingManager ->GetAnimation(modelPathGabkaIdle, gabka));
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathGabkaMine,ztgk::game::modelLoadingManager ->GetAnimation(modelPathGabkaMine, gabka));
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathGabkaAttack,ztgk::game::modelLoadingManager ->GetAnimation(modelPathGabkaAttack, gabka));
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalPosition(glm::vec3(100, 12, 100));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));


    playerUnit = scene.addEntity("Żuczek");
    playerUnit->addComponent(make_unique<Render>(zuczekTest));
    playerUnit->addComponent(make_unique<ColorMask>());
    playerUnit->addComponent(make_unique<AnimationPlayer>());
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathZuczekAttack,ztgk::game::modelLoadingManager ->GetAnimation(modelPathZuczekAttack, zuczekTest));
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathZuczekIddle,ztgk::game::modelLoadingManager ->GetAnimation(modelPathZuczekIddle, zuczekTest));
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathZuczekMove,ztgk::game::modelLoadingManager ->GetAnimation(modelPathZuczekMove, zuczekTest));
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalPosition(glm::vec3(100, 7, 100));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    playerUnit->updateSelfAndChild();

    playerUnit = scene.addEntity("Shroom");
    playerUnit->addComponent(make_unique<Render>(ztgk::game::shroomModel));
    playerUnit->addComponent(make_unique<ColorMask>());
    playerUnit->addComponent(make_unique<AnimationPlayer>());
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathShroomIdle,ztgk::game::modelLoadingManager ->GetAnimation(modelPathShroomIdle, shroomModel));
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathShroomSpit,ztgk::game::modelLoadingManager ->GetAnimation(modelPathShroomSpit, shroomModel));
    playerUnit->getComponent<AnimationPlayer>()->AddAnimation(modelPathShroomMove,ztgk::game::modelLoadingManager ->GetAnimation(modelPathZuczekMove, shroomModel));
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalPosition(glm::vec3(100, 7, 100));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    playerUnit->updateSelfAndChild();
    */
}

void load_hud() {
    auto hud = scene.systemManager.getSystem<HUD>();
    auto ehud = scene.addEntity("HUD");

    ztgk::game::ui_data.gr_game = hud->addGroup(0, "Game");
    ztgk::game::ui_data.gr_map = hud->addGroup(ztgk::game::ui_data.gr_game, "Map");
    ztgk::game::ui_data.gr_middle = hud->addGroup(ztgk::game::ui_data.gr_game, "Unit Details");
    ztgk::game::ui_data.gr_actions = hud->addGroup(ztgk::game::ui_data.gr_game, "Action Panel");
    ztgk::game::ui_data.gr_top = hud->addGroup(ztgk::game::ui_data.gr_game, "Top Panel");

    ztgk::game::ui_data.gr_item = hud->addGroup(ztgk::game::ui_data.gr_middle, "Item Details");

    ztgk::game::ui_data.gr_w1_offensive = hud->addGroup(ztgk::game::ui_data.gr_item, "Weapon 1 Offensive");
    ztgk::game::ui_data.gr_w1_passive = hud->addGroup(ztgk::game::ui_data.gr_item, "Weapon 1 Passive");
    ztgk::game::ui_data.gr_w2_offensive = hud->addGroup(ztgk::game::ui_data.gr_item, "Weapon 2 Offensive");
    ztgk::game::ui_data.gr_w2_passive = hud->addGroup(ztgk::game::ui_data.gr_item, "Weapon 2 Passive");


    ztgk::game::ui_data.gr_pause = hud->addGroup(0, "Pause");

    ztgk::game::ui_data.gr_settings = hud->addGroup(0, "Settings");
    ztgk::game::ui_data.gr_menu = hud->addGroup(0, "Menu");
    ztgk::game::ui_data.gr_credits = hud->addGroup(0, "Credits");

    ztgk::game::ui_data.gr_loadScreen = hud->addGroup(ztgk::game::ui_data.gr_menu, "Load Screen");
    ztgk::game::ui_data.gr_mainMenu = hud->addGroup(ztgk::game::ui_data.gr_menu, "Main Menu");

    ztgk::game::ui_data.gr_game_won = hud->addGroup(ztgk::game::ui_data.gr_menu, "Game Won");
    ztgk::game::ui_data.gr_game_lost = hud->addGroup(ztgk::game::ui_data.gr_menu, "Game Lost");

    hud->getGroupOrDefault(ztgk::game::ui_data.gr_item)->offset.x = 70;

#pragma region menu
    auto emenu = scene.addEntity(ehud, "Menu");

    emenu->addComponent(make_unique<Sprite>(glm::vec2{0, 0}, ztgk::game::window_size, ztgk::color.WHITE, ztgk::game::ui_data.gr_mainMenu, "res/textures/title_screen.png"));
    auto etitle = scene.addEntity(emenu, "Title");
    float ystep = (ztgk::game::window_size.y - 3 * 200) / 4.0f;
    glm::vec2 btn_pos = {ztgk::game::window_size.x * 4 / 5, ztgk::game::window_size.y - 400};
    hud->createButton(
            "START", btn_pos, glm::vec2{200, 80},
            ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
            [hud]() {
                gen_and_load_lvl(true);
                hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true);
            },
            emenu, ztgk::game::ui_data.gr_mainMenu
    );
    auto bspr = emenu->getChild("Button - START")->getComponent<Sprite>();
    bspr->roundingRadius = 0.2;
    bspr->frameColor = ztgk::color.ROSE * glm::vec4{0.5, 0.5, 0.5, 1};
    bspr->frameSize = 5;
    bspr->frameRoundedInside = true;
    btn_pos.y -= ystep;
    hud->createButton(
            "LOAD", btn_pos, glm::vec2{200, 80},
            ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
            [hud]() {
                gen_and_load_lvl(false);
                hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true);
            },
            emenu, ztgk::game::ui_data.gr_mainMenu
    );
    bspr = emenu->getChild("Button - LOAD")->getComponent<Sprite>();
    bspr->roundingRadius = 0.2;
    bspr->frameColor = ztgk::color.ROSE * glm::vec4{0.5, 0.5, 0.5, 1};
    bspr->frameSize = 5;
    bspr->frameRoundedInside = true;
    btn_pos.y -= ystep;
    hud->createButton(
            "Settings", btn_pos, glm::vec2{200, 80},
            ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
            [hud]() {
                hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true);
                hud->getGroupOrDefault(ztgk::game::ui_data.gr_settings)->setHidden(false);
            },
            emenu, ztgk::game::ui_data.gr_mainMenu
    );
    bspr = emenu->getChild("Button - Settings")->getComponent<Sprite>();
    bspr->roundingRadius = 0.2;
    bspr->frameColor = ztgk::color.ROSE * glm::vec4{0.5, 0.5, 0.5, 1};
    bspr->frameSize = 5;
    bspr->frameRoundedInside = true;
    btn_pos.y -= ystep;
    hud->createButton(
            "Credits", btn_pos, glm::vec2{200, 80},
            ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
            [hud]() {
                hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true);
                hud->getGroupOrDefault(ztgk::game::ui_data.gr_credits)->setHidden(false);
            },
            emenu, ztgk::game::ui_data.gr_mainMenu
    );
    bspr = emenu->getChild("Button - Credits")->getComponent<Sprite>();
    bspr->roundingRadius = 0.2;
    bspr->frameColor = ztgk::color.ROSE * glm::vec4{0.5, 0.5, 0.5, 1};
    bspr->frameSize = 5;
    bspr->frameRoundedInside = true;
    btn_pos.y -= ystep;
    hud->createButton(
            "Quit", btn_pos, glm::vec2{200, 80},
            ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
            []() { glfwSetWindowShouldClose(window, true); },
            emenu, ztgk::game::ui_data.gr_mainMenu
    );
    bspr = emenu->getChild("Button - Quit")->getComponent<Sprite>();
    bspr->roundingRadius = 0.2;
    bspr->frameColor = ztgk::color.ROSE * glm::vec4{0.5, 0.5, 0.5, 1};
    bspr->frameSize = 5;
    bspr->frameRoundedInside = true;
#pragma endregion

#pragma region loadscreen
// load/save screen
    auto eload = scene.addEntity(emenu, "Load Screen");
    eload->addComponent(make_unique<Sprite>(glm::vec2{0, 0}, ztgk::game::window_size, ztgk::color.WHITE, ztgk::game::ui_data.gr_loadScreen));
    eload->addComponent(make_unique<Text>("Loading...", glm::vec2{ztgk::game::window_size.x / 5, ztgk::game::window_size.y * 8 / 10}, glm::vec2(1), ztgk::color.PLUM, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_loadScreen));
    eload->getComponent<Text>()->mode = CENTER;
#pragma endregion

#pragma region game
// game
    auto egame = scene.addEntity(ehud, "Game");
    auto emap = scene.addEntity(egame, "Map");
//    emap->addComponent(make_unique<Sprite>(glm::vec2{0,0}, glm::vec2{400,400}, ztgk::color.GRAY * 0.75f, ztgk::game::ui_data.gr_map));
    emap->addComponent(make_unique<Text>("Map", glm::vec2{200, 200}, glm::vec2(1), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.italic, NONE, ztgk::game::ui_data.gr_map));
    emap->getComponent<Text>()->mode = CENTER;
    emap->addComponent(make_unique<Minimap>(glm::vec2{0, 0}, glm::vec2{400, 400}, ztgk::game::ui_data.gr_map));

#pragma region unit details
    auto emiddle = scene.addEntity(egame, "Unit Details");
    emiddle->addComponent(make_unique<Sprite>(glm::vec2{400, 0}, glm::vec2{1120, 250}, ztgk::color.GRAY * 0.75f, ztgk::game::ui_data.gr_middle));
    auto ebar = hud->createSlider_Bar(HORIZONTAL, glm::vec2{400, 275}, glm::vec2{1120, 50}, ztgk::color.GREEN * glm::vec4{0.5, 0.5, 0.5, 1}, ztgk::color.GREEN, emiddle, ztgk::game::ui_data.gr_middle, true, 100);
    ebar->getComponent<Sprite>()->frame(2, ztgk::color.GREEN * glm::vec4{0.3, 0.3, 0.3, 1})->round(0.1);
    ebar->getChild("Background")->getComponent<Sprite>()->frame(2, ztgk::color.GREEN * glm::vec4{0.2, 0.2, 0.2, 1});

    auto eportrait = scene.addEntity(emiddle, "Portrait");
    eportrait->addComponent(make_unique<Sprite>(glm::vec2{400, 0}, glm::vec2{250, 250}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/gabka_cool.png"));
    eportrait->getComponent<Sprite>()->frame(3, ztgk::color.BLACK);

    auto ename = scene.addEntity(emiddle, "Name");
    ename->addComponent(make_unique<Text>("SPONGE", glm::vec2{700, 240}, glm::vec2(1.5), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_middle));
    ename->getComponent<Text>()->mode = TOP_LEFT;

    auto emodstip = scene.addEntity(emiddle, "Modstip");
    emodstip->addComponent(make_unique<Text>("Total added:", glm::vec2{700, 175}, glm::vec2(0.5), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.italic, NONE, ztgk::game::ui_data.gr_middle));
    emodstip->getComponent<Text>()->mode = TOP_LEFT;

    auto emods = scene.addEntity(emiddle, "Mods");
    auto ent = scene.addEntity(emods, "ATK");
    ent->addComponent(make_unique<Sprite>(glm::vec2{680, 125}, glm::vec2{50, 50}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/stat/atk.png"));
    ent->getComponent<Sprite>()->mode = CENTER;
    ent->addComponent(make_unique<Text>("0.05 + 10", glm::vec2{710, 125}, glm::vec2(0.6), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "DEF");
    ent->addComponent(make_unique<Sprite>(glm::vec2{680, 75}, glm::vec2{50, 50}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/stat/def.png"));
    ent->getComponent<Sprite>()->mode = CENTER;
    ent->addComponent(make_unique<Text>("0.30 + 10", glm::vec2{710, 75}, glm::vec2(0.6), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "CD");
    ent->addComponent(make_unique<Sprite>(glm::vec2{680, 25}, glm::vec2{50, 50}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/stat/aspd.png"));
    ent->getComponent<Sprite>()->mode = CENTER;
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{710, 25}, glm::vec2(0.6), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "RNG");
    ent->addComponent(make_unique<Sprite>(glm::vec2{860, 125}, glm::vec2{50, 50}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/stat/rng.png"));
    ent->getComponent<Sprite>()->mode = CENTER;
    ent->addComponent(make_unique<Text>("4", glm::vec2{890, 125}, glm::vec2(0.6), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "MNSP");
    ent->addComponent(make_unique<Sprite>(glm::vec2{860, 75}, glm::vec2{50, 50}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/stat/mnspd.png"));
    ent->getComponent<Sprite>()->mode = CENTER;
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{890, 75}, glm::vec2(0.6), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "MVSP");
    ent->addComponent(make_unique<Sprite>(glm::vec2{860, 25}, glm::vec2{50, 50}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/stat/mvspd.png"));
    ent->getComponent<Sprite>()->mode = CENTER;
    ent->addComponent(make_unique<Text>("5", glm::vec2{890, 25}, glm::vec2(0.6), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;
#pragma endregion

#pragma region weapon details
// WEAPON 1
    auto eweapPortrait = scene.addEntity(emiddle, "Weapon Portrait #1");
    eweapPortrait->addComponent(make_unique<Sprite>(glm::vec2{1050, 135}, glm::vec2{100, 100}, ztgk::color.WHITE, ztgk::game::ui_data.gr_item, "res/textures/icons/item_mop.png"));
    eweapPortrait->addComponent(make_unique<Text>("Mop", glm::vec2{1295, 235}, glm::vec2(0.5), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_item));
    eweapPortrait->getComponent<Text>()->mode = TOP_CENTER;
    eweapPortrait->getComponent<Sprite>()->frame(3, ztgk::color.BLACK);

    auto eoffstat = scene.addEntity(eweapPortrait, "Offensive Stats");
    ent = scene.addEntity(eoffstat, "ATK");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1170, 190}, glm::vec2{37, 37}, ztgk::color.WHITE, ztgk::game::ui_data.gr_w1_offensive, "res/textures/icons/stat/atk.png"));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("0.05 + 10", glm::vec2{1220, 190}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_w1_offensive));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(eoffstat, "RNG");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1300, 190}, glm::vec2{37, 37}, ztgk::color.WHITE, ztgk::game::ui_data.gr_w1_offensive, "res/textures/icons/stat/rng.png"));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("4", glm::vec2{1350, 190}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_w1_offensive));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(eoffstat, "CD");
    auto eslider = hud->createSlider_Bar(HORIZONTAL, glm::vec2{1170, 150}, glm::vec2{280, 25}, ztgk::color.BLUE * glm::vec4{0.5, 0.5, 0.5, 1}, ztgk::color.BLUE, ent, ztgk::game::ui_data.gr_w1_offensive, true, 100);
    eslider->getComponent<HUDSlider>()->displayFormat = "{:.1f}s / {:.1f}s";
    eslider->getComponent<Sprite>()->frame(2, ztgk::color.BLUE * glm::vec4{0.3, 0.3, 0.3, 1})->round(0.1);
    eslider->getChild("Background")->getComponent<Sprite>()->frame(2, ztgk::color.BLUE * glm::vec4{0.2, 0.2, 0.2, 1});

    auto epassstat = scene.addEntity(eweapPortrait, "Passive Stats");
    auto gr = hud->addGroup(ztgk::game::ui_data.gr_w1_passive, "Weapon 1 STAT 1");
    ent = scene.addEntity(epassstat, "STAT1");
    // + 18 - 6
    ent->addComponent(make_unique<Sprite>(glm::vec2{1170, 190}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("0.05 + 10", glm::vec2{1220, 190}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(epassstat, "STAT2");
    gr = hud->addGroup(ztgk::game::ui_data.gr_w1_passive, "Weapon 1 STAT 2");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1170, 155}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("4", glm::vec2{1220, 155}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(epassstat, "STAT3");
    gr = hud->addGroup(ztgk::game::ui_data.gr_w1_passive, "Weapon 1 STAT 3");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1300, 190}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{1350, 190}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(epassstat, "STAT4");
    gr = hud->addGroup(ztgk::game::ui_data.gr_w1_passive, "Weapon 1 STAT 4");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1300, 155}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{1350, 155}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

// WEAPON 2
    eweapPortrait = scene.addEntity(emiddle, "Weapon Portrait #2");
    eweapPortrait->addComponent(make_unique<Sprite>(glm::vec2{1050, 15}, glm::vec2{100, 100}, ztgk::color.WHITE, ztgk::game::ui_data.gr_item, "res/textures/icons/item_superMop.png"));
    eweapPortrait->addComponent(make_unique<Text>("Mop", glm::vec2{1295, 115}, glm::vec2(0.5), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_item));
    eweapPortrait->getComponent<Text>()->mode = TOP_CENTER;
    eweapPortrait->getComponent<Sprite>()->frame(3, ztgk::color.BLACK);

    eoffstat = scene.addEntity(eweapPortrait, "Offensive Stats");
    ent = scene.addEntity(eoffstat, "ATK");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1170, 68}, glm::vec2{37, 37}, ztgk::color.WHITE, ztgk::game::ui_data.gr_w2_offensive, "res/textures/icons/stat/atk.png"));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("0.05 + 10", glm::vec2{1220, 68}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_w2_offensive));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(eoffstat, "RNG");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1300, 68}, glm::vec2{37, 37}, ztgk::color.WHITE, ztgk::game::ui_data.gr_w2_offensive, "res/textures/icons/stat/rng.png"));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("4", glm::vec2{1350, 68}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_w2_offensive));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(eoffstat, "CD");
    eslider = hud->createSlider_Bar(HORIZONTAL, glm::vec2{1170, 30}, glm::vec2{250, 25}, ztgk::color.BLUE * glm::vec4{0.5, 0.5, 0.5, 1}, ztgk::color.BLUE, ent, ztgk::game::ui_data.gr_w2_offensive, true, 100);
    eslider->getComponent<HUDSlider>()->displayFormat = "{:.1f}s / {:.1f}s";
    eslider->getComponent<Sprite>()->frame(2, ztgk::color.BLUE * glm::vec4{0.3, 0.3, 0.3, 1})->round(0.1);
    eslider->getChild("Background")->getComponent<Sprite>()->frame(2, ztgk::color.BLUE * glm::vec4{0.2, 0.2, 0.2, 1});

    epassstat = scene.addEntity(eweapPortrait, "Passive Stats");
    gr = hud->addGroup(ztgk::game::ui_data.gr_w2_passive, "Weapon 2 STAT 1");
    ent = scene.addEntity(epassstat, "STAT1");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1170, 68}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("0.05 + 10", glm::vec2{1220, 68}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(epassstat, "STAT2");
    gr = hud->addGroup(ztgk::game::ui_data.gr_w2_passive, "Weapon 2 STAT 2");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1170, 31}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("4", glm::vec2{1220, 31}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(epassstat, "STAT3");
    gr = hud->addGroup(ztgk::game::ui_data.gr_w2_passive, "Weapon 2 STAT 3");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1300, 68}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{1350, 68}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(epassstat, "STAT4");
    gr = hud->addGroup(ztgk::game::ui_data.gr_w2_passive, "Weapon 2 STAT 4");
    ent->addComponent(make_unique<Sprite>(glm::vec2{1300, 31}, glm::vec2{37, 37}, ztgk::color.WHITE, gr));
    ent->getComponent<Sprite>()->mode = MIDDLE_LEFT;
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{1350, 31}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;
#pragma endregion

#pragma region actions
// ACTIONS
    auto eactions = scene.addEntity(egame, "Action Panel");
    eactions->addComponent(make_unique<Sprite>(glm::vec2{1520, 0}, glm::vec2{400, 400}, ztgk::color.GRAY * 0.75f, ztgk::game::ui_data.gr_actions));
    ent = hud->createButton(
            glm::vec2{1595, 325}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png",
            []() {
                auto mods = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ? GLFW_MOD_CONTROL : 0;
                mods |= glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS ? GLFW_MOD_ALT : 0;
                *ztgk::game::signalQueue += KeySignalData::signal(GLFW_KEY_1, glfwGetKeyScancode(GLFW_KEY_1), GLFW_PRESS, mods, "Passing selection of unit 1 via action menu to handle_controls func.");
            },
            eactions, ztgk::game::ui_data.gr_actions, false
    );
    ent->getChild("Background")->getComponent<Sprite>()->frame(1, ztgk::color.BLACK);
    ent->addComponent(make_unique<Text>("1", glm::vec2{1595, 390}, glm::vec2(0.4), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_actions));
    ent->getComponent<Text>()->mode = CENTER;
    ebar = hud->createSlider_Bar(HORIZONTAL, glm::vec2{1545, 270}, glm::vec2{100, 10}, ztgk::color.GREEN * glm::vec4{0.5, 0.5, 0.5, 1}, ztgk::color.GREEN, ent, ztgk::game::ui_data.gr_actions);
    ebar->getComponent<Sprite>()->frame(1, ztgk::color.GREEN * glm::vec4{0.3, 0.3, 0.3, 1})->round(0.1);
    ebar->getChild("Background")->getComponent<Sprite>()->frame(1, ztgk::color.GREEN * glm::vec4{0.2, 0.2, 0.2, 1});

    ent = hud->createButton(
            glm::vec2{1720, 325}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png",
            []() {
                auto mods = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ? GLFW_MOD_CONTROL : 0;
                mods |= glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS ? GLFW_MOD_ALT : 0;
                *ztgk::game::signalQueue += KeySignalData::signal(GLFW_KEY_2, glfwGetKeyScancode(GLFW_KEY_2), GLFW_PRESS, mods, "Passing selection of unit 2 via action menu to handle_controls func.");
            },
            eactions, ztgk::game::ui_data.gr_actions, false
    );
    ent->getChild("Background")->getComponent<Sprite>()->frame(1, ztgk::color.BLACK);
    ent->addComponent(make_unique<Text>("2", glm::vec2{1720, 390}, glm::vec2(0.4), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_actions));
    ent->getComponent<Text>()->mode = CENTER;
    ebar = hud->createSlider_Bar(HORIZONTAL, glm::vec2{1670, 270}, glm::vec2{100, 10}, ztgk::color.GREEN * glm::vec4{0.5, 0.5, 0.5, 1}, ztgk::color.GREEN, ent, ztgk::game::ui_data.gr_actions);
    ebar->getComponent<Sprite>()->frame(1, ztgk::color.GREEN * glm::vec4{0.3, 0.3, 0.3, 1})->round(0.1);
    ebar->getChild("Background")->getComponent<Sprite>()->frame(1, ztgk::color.GREEN * glm::vec4{0.2, 0.2, 0.2, 1});

    ent = hud->createButton(glm::vec2{1845, 325}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png",
                            []() {
                                auto mods = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS ? GLFW_MOD_CONTROL : 0;
                                mods |= glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS ? GLFW_MOD_ALT : 0;
                                *ztgk::game::signalQueue += KeySignalData::signal(GLFW_KEY_3, glfwGetKeyScancode(GLFW_KEY_3), GLFW_PRESS, mods, "Passing selection of unit 3 via action menu to handle_controls func.");
                            },
                            eactions, ztgk::game::ui_data.gr_actions, false
    );
    ent->getChild("Background")->getComponent<Sprite>()->frame(1, ztgk::color.BLACK);
    ent->addComponent(make_unique<Text>("3", glm::vec2{1845, 390}, glm::vec2(0.4), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_actions));
    ent->getComponent<Text>()->mode = CENTER;
    ebar = hud->createSlider_Bar(HORIZONTAL, glm::vec2{1795, 270}, glm::vec2{100, 10}, ztgk::color.GREEN * glm::vec4{0.5, 0.5, 0.5, 1}, ztgk::color.GREEN, ent, ztgk::game::ui_data.gr_actions);
    ebar->getComponent<Sprite>()->frame(1, ztgk::color.GREEN * glm::vec4{0.3, 0.3, 0.3, 1})->round(0.1);
    ebar->getChild("Background")->getComponent<Sprite>()->frame(1, ztgk::color.GREEN * glm::vec4{0.2, 0.2, 0.2, 1});

    hud->createButton(glm::vec2{1595, 200}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", []() {}, eactions, ztgk::game::ui_data.gr_actions, false);
    hud->createButton(glm::vec2{1720, 200}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", []() {}, eactions, ztgk::game::ui_data.gr_actions, false);
    hud->createButton(glm::vec2{1845, 200}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", []() {}, eactions, ztgk::game::ui_data.gr_actions, false);
    hud->createButton(glm::vec2{1595, 75}, glm::vec2{100, 100}, "res/textures/icons/action_drop_1.png", "res/textures/transparent.png", []() {
        if (ztgk::game::ui_data.tracked_unit_id == -1) return;
        auto unit = std::find_if(scene.systemManager.getSystem<UnitSystem>()->unitComponents.begin(),
                                 scene.systemManager.getSystem<UnitSystem>()->unitComponents.end(), [](Unit *unit) { return unit->uniqueID == ztgk::game::ui_data.tracked_unit_id; });
        if (unit == scene.systemManager.getSystem<UnitSystem>()->unitComponents.end()) return;

        auto item = (*unit)->equipment[1];
        if (item == nullptr) return;
        InventoryManager::instance->unassign_item(*unit, item);
        InventoryManager::instance->spawn_item_on_map(item, (*unit)->pathfinding.GetNearestVacantTileAround((*unit)->gridPosition, {(*unit)->gridPosition}));
        ztgk::update_weapon_hud(*unit);
    }, eactions, ztgk::game::ui_data.gr_actions, false);
    hud->createButton(glm::vec2{1720, 75}, glm::vec2{100, 100}, "res/textures/icons/action_drop_2.png", "res/textures/transparent.png", []() {
        if (ztgk::game::ui_data.tracked_unit_id == -1) return;
        auto unit = std::find_if(scene.systemManager.getSystem<UnitSystem>()->unitComponents.begin(),
                                 scene.systemManager.getSystem<UnitSystem>()->unitComponents.end(), [](Unit *unit) { return unit->uniqueID == ztgk::game::ui_data.tracked_unit_id; });
        if (unit == scene.systemManager.getSystem<UnitSystem>()->unitComponents.end()) return;

        auto item = (*unit)->equipment[2];
        if (item == nullptr) return;
        InventoryManager::instance->unassign_item(*unit, item);
        InventoryManager::instance->spawn_item_on_map(item, (*unit)->pathfinding.GetNearestVacantTileAround((*unit)->gridPosition, {(*unit)->gridPosition}));
        ztgk::update_weapon_hud(*unit);
    }, eactions, ztgk::game::ui_data.gr_actions, false);
    hud->createButton(glm::vec2{1845, 75}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", []() {}, eactions, ztgk::game::ui_data.gr_actions, false);
#pragma endregion

#pragma region top panel
// TOP PANEL
    auto etop = scene.addEntity(egame, "Top Panel");
    glm::vec2 top_anchor = {ztgk::game::window_size.x / 2, ztgk::game::window_size.y - 50};
//    ent = hud->createButton(
//        "||", top_anchor - glm::vec2{0, 50}, glm::vec2{35, 35},
//        ztgk::color.GRAY * glm::vec4{1, 1, 1, 0.75f}, ztgk::color.GRAY * glm::vec4{0.9, 0.9, 0.9, 0.75}, ztgk::color.GRAY * glm::vec4{0.8, 0.8, 0.8, 0.75},
//        [hud](){
//            hud->getGroupOrDefault(ztgk::game::ui_data.gr_pause)->setHidden(false);
//        },
//        etop, ztgk::game::ui_data.gr_top
//    );
    ent = hud->createButton(
            top_anchor - glm::vec2{0, 15}, glm::vec2{30, 30},
            "res/textures/icons/pause.png", "res/textures/transparent.png",
            [hud]() {
                hud->getGroupOrDefault(ztgk::game::ui_data.gr_pause)->setHidden(false);
            },
            etop, ztgk::game::ui_data.gr_top
    );
    ent->getChild("Background")->getComponent<Sprite>()->round(0.2f)->frame(2, ztgk::color.BLACK);
//    ent->getComponent<Text>()->pos.x -= 1;
//    ent->getComponent<Text>()->pos.y += 5;

    etop->addComponent(make_unique<Sprite>(top_anchor, glm::vec2{450, 70}, ztgk::color.GRAY * 0.75f, ztgk::game::ui_data.gr_top));
    etop->getComponent<Sprite>()->from(CENTER)->round(0.2f)->frame(2, glm::vec4{0, 0, 0.75, 0.8});

    auto etime = scene.addEntity(etop, "Time");
    etime->addComponent(make_unique<Text>("00:00", glm::vec2{top_anchor.x, 1045}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.default_font, NONE, ztgk::game::ui_data.gr_top));
    etime->getComponent<Text>()->mode = CENTER;
    ztgk::game::ui_data.txt_time_display = etime->getComponent<Text>();

    auto epraniumCounter = scene.addEntity(etop, "Pranium Counter");
    epraniumCounter->addComponent(make_unique<Sprite>(top_anchor - glm::vec2{190, 0}, glm::vec2{60, 80}, ztgk::color.WHITE, ztgk::game::ui_data.gr_top, "res/textures/icons/pranium.png"));
    epraniumCounter->getComponent<Sprite>()->mode = CENTER;
    epraniumCounter->addComponent(make_unique<Text>("00", top_anchor - glm::vec2{150, 0}, glm::vec2(0.7), ztgk::color.KHAKI, ztgk::font.default_font, NONE, ztgk::game::ui_data.gr_top));
    epraniumCounter->getComponent<Text>()->mode = MIDDLE_LEFT;
    ztgk::game::ui_data.txt_pranium_counter = epraniumCounter->getComponent<Text>();

    auto eunitCounter = scene.addEntity(etop, "Unit Counter");
    eunitCounter->addComponent(make_unique<Sprite>(top_anchor + glm::vec2{190, 0}, glm::vec2{60, 60}, ztgk::color.WHITE, ztgk::game::ui_data.gr_top, "res/textures/icons/pick-me.png"));
    eunitCounter->getComponent<Sprite>()->mode = CENTER;
    eunitCounter->addComponent(make_unique<Text>("00", top_anchor + glm::vec2{155, 0}, glm::vec2(0.7), ztgk::color.KHAKI, ztgk::font.default_font, NONE, ztgk::game::ui_data.gr_top));
    eunitCounter->getComponent<Text>()->mode = MIDDLE_RIGHT;
    ztgk::game::ui_data.txt_unit_counter = eunitCounter->getComponent<Text>();
#pragma endregion
#pragma endregion

#pragma region settings
    auto gr_concreteSettings = hud->addGroup(ztgk::game::ui_data.gr_settings, "Concrete Settings");
    auto gr_settingHeaders = hud->addGroup(gr_concreteSettings, "Setting Headers");
    auto gr_settingSliders = hud->addGroup(gr_concreteSettings, "Setting Sliders");

    hud->getGroupOrAddDefault(gr_concreteSettings)->offset.x = 50;
    hud->getGroupOrAddDefault(gr_concreteSettings)->offset.y = -30;
    hud->getGroupOrAddDefault(gr_settingHeaders)->offset.y = 5; // centering the texts to sliders because text rendering SUCKSSSSSS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    hud->getGroupOrAddDefault(gr_settingSliders)->offset.x = 50;

// settings
    auto esettings = scene.addEntity(ehud, "Settings");
    esettings->addComponent(make_unique<Sprite>(glm::vec2{0, 0}, ztgk::game::window_size, ztgk::color.LAVENDER, ztgk::game::ui_data.gr_settings));
    esettings->addComponent(make_unique<Text>("Settings", glm::vec2{ztgk::game::window_size.x / 2, ztgk::game::window_size.y - 100}, glm::vec2(1.5), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_settings));
    esettings->getComponent<Text>()->mode = TOP_CENTER;

    auto eslider_gamma = scene.addEntity(esettings, "Gamma ");
    eslider_gamma->addComponent(make_unique<Text>("Gamma", glm::vec2{(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 300}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr_settingHeaders));
    eslider_gamma->getComponent<Text>()->mode = MIDDLE_RIGHT;
    hud->createSlider_SettingBar(HORIZONTAL, {(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 300}, {1000, 50}, eslider_gamma, gr_settingSliders, 3, 0.75, "{:.2f}");
    eslider_gamma->getChild("Setting Slider")->getComponent<HUDSlider>()->set_in_display_range(scene.systemManager.getSystem<PhongPipeline>()->getGamma());

    auto eslider_master = scene.addEntity(esettings, "Master Volume ");
    eslider_master->addComponent(make_unique<Text>("Master Volume", glm::vec2{(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 400}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr_settingHeaders));
    eslider_master->getComponent<Text>()->mode = MIDDLE_RIGHT;
    hud->createSlider_SettingBar(HORIZONTAL, {(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 400}, {1000, 50}, eslider_master, gr_settingSliders, 100, 0, "{:.0f}%");

    auto eslider_ambient = scene.addEntity(esettings, "Music Volume ");
    eslider_ambient->addComponent(make_unique<Text>("Music Volume", glm::vec2{(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 500}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr_settingHeaders));
    eslider_ambient->getComponent<Text>()->mode = MIDDLE_RIGHT;
    hud->createSlider_SettingBar(HORIZONTAL, {(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 500}, {1000, 50}, eslider_ambient, gr_settingSliders, 100, 0, "{:.0f}%");

    auto eslider_sfx = scene.addEntity(esettings, "SFX Volume ");
    eslider_sfx->addComponent(make_unique<Text>("SFX Volume", glm::vec2{(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 600}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr_settingHeaders));
    eslider_sfx->getComponent<Text>()->mode = MIDDLE_RIGHT;
    hud->createSlider_SettingBar(HORIZONTAL, {(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 600}, {1000, 50}, eslider_sfx, gr_settingSliders, 100, 0, "{:.0f}%");

    auto eslider_click = scene.addEntity(esettings, "Click Volume ");
    eslider_click->addComponent(make_unique<Text>("Click Volume", glm::vec2{(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 700}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, gr_settingHeaders));
    eslider_click->getComponent<Text>()->mode = MIDDLE_RIGHT;
    hud->createSlider_SettingBar(HORIZONTAL, {(ztgk::game::window_size.x - 1000) / 2, ztgk::game::window_size.y - 700}, {1000, 50}, eslider_click, gr_settingSliders, 100, 0, "{:.0f}%");
    eslider_click->getChild("Setting Slider")->getComponent<HUDSlider>()->set_in_display_range(6);

    ent = hud->createButton("Save", {ztgk::game::window_size.x / 2, 100}, {200, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
                            [eslider_master, eslider_ambient, eslider_sfx, eslider_click, eslider_gamma]() {
                                ztgk::game::audioManager->setGlobalVolume(eslider_master->getChild("Setting Slider")->getComponent<HUDSlider>()->get_in_display_range() * 1.28f);
                                ztgk::game::audioManager->setVolumeForGroup("ambient", eslider_ambient->getChild("Setting Slider")->getComponent<HUDSlider>()->get_in_display_range() * 1.28f);
                                ztgk::game::audioManager->setVolumeForGroup("sfx", eslider_sfx->getChild("Setting Slider")->getComponent<HUDSlider>()->get_in_display_range() * 1.28f);
                                ztgk::game::audioManager->setVolumeForGroup("click", eslider_click->getChild("Setting Slider")->getComponent<HUDSlider>()->get_in_display_range() * 1.28f);
                                ztgk::game::scene->systemManager.getSystem<PhongPipeline>()->setGamma(eslider_gamma->getChild("Setting Slider")->getComponent<HUDSlider>()->get_in_display_range());
                            },
                            esettings, ztgk::game::ui_data.gr_settings
    );

    hud->createButton("<Back", {200, 125}, {200, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
                      [hud]() {
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_settings)->setHidden(true);
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false);
                      },
                      esettings, ztgk::game::ui_data.gr_settings
    );
#pragma endregion

#pragma region credits
// credits
    auto ecredits = scene.addEntity(ehud, "Credits");
    ecredits->addComponent(make_unique<Sprite>(glm::vec2{0, 0}, ztgk::game::window_size, ztgk::color.LAVENDER, ztgk::game::ui_data.gr_credits));

    std::string licenses;
    std::ifstream file("res/sounds/CREDITS.txt");
    std::string line;
    while (std::getline(file, line)) {
        licenses += line + "\n";
    }
    auto eteam = scene.addEntity(ecredits, "Team Credits");
    eteam->addComponent(make_unique<Text>(
            "Bubble Bliss Games\n\nGrzegorz Ludziejewski\nIgor Kusidel\nKrzysztof Czerwinski\nAmelia Kwasniewska\nJan Filipowicz",
            glm::vec2{100, ztgk::game::window_size.y - 100}, glm::vec2(1), glm::vec4{36, 54, 110, 255} / 255.0f, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_credits
    ));
    eteam->getComponent<Text>()->mode = TOP_LEFT;
    eteam->addComponent(make_unique<Sprite>(glm::vec2{100, 400}, glm::vec2{400, 225}, ztgk::color.WHITE, ztgk::game::ui_data.gr_credits, "res/textures/credits.png"));
    eteam->getComponent<Sprite>()->mode = MIDDLE_LEFT;

    auto elicenses = scene.addEntity(ecredits, "Licenses");
    elicenses->addComponent(make_unique<Text>(
            licenses,
            glm::vec2{ztgk::game::window_size.x - 100, ztgk::game::window_size.y - 100}, glm::vec2(0.5), glm::vec4{36, 54, 110, 255} / 255.0f, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_credits
    ));
    elicenses->getComponent<Text>()->mode = TOP_RIGHT;

    hud->createButton("<Back", {200, 125}, {200, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
                      [hud]() {
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_credits)->setHidden(true);
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false);
                      },
                      ecredits, ztgk::game::ui_data.gr_credits
    );
#pragma endregion

#pragma region win-lose screen
    // Game Won -> 4 pranium delivered to Washing Machine
    auto egamewon = scene.addEntity(emenu, "Win Screen");
    egamewon->addComponent(make_unique<Sprite>(glm::vec2{0, 0}, ztgk::game::window_size, ztgk::color.LAVENDER, ztgk::game::ui_data.gr_game_won));
    egamewon->addComponent(make_unique<Text>("VICTORY", glm::vec2{ztgk::game::window_size.x / 2, ztgk::game::window_size.y - 200}, glm::vec2(2), ztgk::color.GOLD, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_game_won));
    egamewon->getComponent<Text>()->mode = CENTER;
    auto egamewon_desc = scene.addEntity(egamewon, "Win Screen Flavor");
    egamewon_desc->addComponent(make_unique<Text>("The world is now a cleaner place.", glm::vec2{ztgk::game::window_size.x / 2, ztgk::game::window_size.y / 2}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_game_won));
    egamewon_desc->getComponent<Text>()->mode = CENTER;
    hud->createButton("Return to main menu", {ztgk::game::window_size.x / 2, 200}, {400, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
                      [hud]() {
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_game_won)->setHidden(true);
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false);
                      },
                      egamewon, ztgk::game::ui_data.gr_game_won
    );

    // Game Lost -> All Gompkas are dead
    auto egamelost = scene.addEntity(emenu, "Lose Screen");
    egamelost->addComponent(make_unique<Sprite>(glm::vec2{0, 0}, ztgk::game::window_size, ztgk::color.LAVENDER, ztgk::game::ui_data.gr_game_lost));
    egamelost->addComponent(make_unique<Text>("DEFEAT", glm::vec2{ztgk::game::window_size.x / 2, ztgk::game::window_size.y - 200}, glm::vec2(1.5), ztgk::color.RED, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_game_lost));
    egamelost->getComponent<Text>()->mode = CENTER;
    auto egamelost_desc = scene.addEntity(egamelost, "Lose Screen Flavor");
    egamelost_desc->addComponent(make_unique<Text>("As The Flith emerges, entropy increases...", glm::vec2{ztgk::game::window_size.x / 2, ztgk::game::window_size.y / 2}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_game_lost));
    egamelost_desc->getComponent<Text>()->mode = CENTER;
    hud->createButton("Return to main menu", {ztgk::game::window_size.x / 2, 200}, {400, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
                      [hud]() {
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_game_lost)->setHidden(true);
                          hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false);
                      },
                      egamelost, ztgk::game::ui_data.gr_game_lost
    );
#pragma endregion

    // groups
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_menu)->setHidden(false);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false);

    hud->getGroupOrDefault(ztgk::game::ui_data.gr_game)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_settings)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_middle)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_pause)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_loadScreen)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_credits)->setHidden(true);

    hud->getGroupOrDefault(ztgk::game::ui_data.gr_w1_passive)->setHidden(true);
//    hud->getGroupOrDefault(ztgk::game::ui_data.gr_w2_passive)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_game_won)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_game_lost)->setHidden(true);
}

void init_imgui() {
    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
}

void before_frame() {
    // Setting up update_delta time
    ZoneScopedN("Before frame");
    Time::Instance().Update();
    deltaTime = Time::Instance().DeltaTime();
}


void input() {
    ZoneScopedN("Input");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#ifdef DEBUG_BUILD
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#elif defined(RELEASE_BUILD)
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#endif
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    processInput(window);
}

void update() {
    ZoneScopedN("Update");
    scene.systemManager.getSystem<SignalQueue>()->Update();

    //no need to check every frame, every 5 sec is good enough
    if ((int) glfwGetTime() % 5 == 0 && glfwGetTime() - (int) glfwGetTime() < 0.02) {
        ztgk::game::audioManager->playAmbientMusic();
    }

    ztgk::game::cursor.update();
    scene.systemManager.Update();
    scene.updateScene();
    
    scene.systemManager.getSystem<ParticleSystem>()->Update();
    scene.systemManager.getSystem<InstanceRenderSystem>()->Update();
    scene.systemManager.getSystem<LightSystem>()->Update();
    scene.systemManager.getSystem<WireRenderSystem>()->Update();
    scene.systemManager.getSystem<UnitSystem>()->Update();
    scene.systemManager.getSystem<WashingMachine>()->Update();

    for (auto tile : tilesSelectedToMine) {
        tile->setHighlight(CLEAR);
        tile->setHighlightPresetFromState();
    }
    tilesSelectedToMine.clear();
    for (auto tile : combatTargets) {
        tile->setHighlight(CLEAR);
        tile->setHighlightPresetFromState();
    }
    combatTargets.clear();
    for (auto tile : movementTargets) {
        tile->setHighlight(CLEAR);
        tile->setHighlightPresetFromState();
    }
    movementTargets.clear();
    update_dragged_tiles();
    auto grid = scene.systemManager.getSystem<Grid>();
    for (auto sponge : scene.systemManager.getSystem<UnitSystem>()->allies) {
        for (auto mineable : sponge->miningTargets)
            tilesSelectedToMine.push_back(grid->getTileAt(mineable->gridPosition));
        if (sponge->hasCombatTarget)
            combatTargets.push_back(grid->getTileAt(sponge->combatTarget->gridPosition));
        if (sponge->hasMovementTarget) {
            if (sponge->ForcedMovementState) {
                auto tile = grid->getTileAt(sponge->forcedMovementTarget);
//            if (tile->state == FLOOR)
                if (tile)
                    movementTargets.push_back(grid->getTileAt(sponge->forcedMovementTarget));
            } else {
                auto tile = grid->getTileAt(sponge->forcedMovementTarget);
                if (tile)
//            if (tile->state == FLOOR)
                    movementTargets.push_back(grid->getTileAt(sponge->movementTarget));
            }
        }
    }
    for (auto tile: tilesSelectedToMine) {
        tile->setHighlight(TileHighlightState::SELECTION_RMB_BLUE);
    }
    for (auto tile: combatTargets) {
        tile->setHighlight(TileHighlightState::HIGHLIGHT_ENEMY_RED);
    }
    for (auto tile: movementTargets) {
        tile->setHighlight(TileHighlightState::MOVE_ORDER_YELLOW);
    }

    scene.systemManager.getSystem<CollisionSystem>()->Update();
    scene.systemManager.getSystem<RenderSystem>()->Update();
    scene.systemManager.getSystem<MiningSystem>()->Update();
    scene.systemManager.getSystem<HUD>()->Update();
    scene.systemManager.getSystem<ProjectileSystem>()->Update();
    scene.systemManager.getSystem<Grid>()->Update();
    scene.systemManager.getSystem<AudioManager>()->Update();
//
//    for(auto u : scene.systemManager.getSystem<UnitSystem>()->unitComponents) {
//        if(u->isAlly)
//            spdlog::info("Unit: {} -- State: {}  -- currentMinTarg {} {}", u->name, u->currentState->name, u->currentMiningTarget == nullptr ? 0 : u->currentMiningTarget->gridPosition.x, u->currentMiningTarget == nullptr ? 0 : u->currentMiningTarget->gridPosition.z);
//    }


}

void render() {
    ZoneScopedN("Render");

    scene.systemManager.getSystem<LightSystem>()->PushDepthMapsToShader(&scene.systemManager.getSystem<PhongPipeline>()->phongShader);
    scene.systemManager.getSystem<LightSystem>()->PushDepthMapsToShader(&scene.systemManager.getSystem<PhongPipeline>()->phongInstanceShader);

    glViewport(0, 0, camera.saved_display_w, camera.saved_display_h); // Needed after light generation

    // bloomSystem.BindBuffer();
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    file_logger->info("Cleared.");

    file_logger->info("Set up PBR.");

    scene.systemManager.getSystem<PhongPipeline>()->PrepareFoamMap(&camera);

    scene.systemManager.getSystem<PhongPipeline>()->PrebindPipeline(&camera);

    scene.systemManager.getSystem<InstanceRenderSystem>()->DrawTiles(&scene.systemManager.getSystem<PhongPipeline>()->phongInstanceShader, &camera);
    scene.systemManager.getSystem<InstanceRenderSystem>()->DrawParticles(&scene.systemManager.getSystem<PhongPipeline>()->particleShader, &camera);
    scene.systemManager.getSystem<RenderSystem>()->DrawScene(&scene.systemManager.getSystem<PhongPipeline>()->phongShader, &camera);
    scene.systemManager.getSystem<InstanceRenderSystem>()->DrawLights(&scene.systemManager.getSystem<PhongPipeline>()->phongInstanceLightShader, &camera);


    scene.systemManager.getSystem<PhongPipeline>()->WriteToBackBuffer(&camera);

    scene.systemManager.getSystem<WireRenderSystem>()->DrawColliders();
    scene.systemManager.getSystem<WireRenderSystem>()->DrawRays();
    file_logger->info("Rendered AsteroidsSystem.");


    scene.systemManager.getSystem<HUD>()->draw();
}

void imgui_begin() {
    ZoneScopedN("Imgui begin");

#ifdef DEBUG_BUILD
    ImGuiIO &io = ImGui::GetIO();
    if (ztgk::game::cursor.config.capture_move) {
        io.MouseDrawCursor = true;
    } else {
        io.MouseDrawCursor = false;
    }
#endif

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();


}

void imgui_render() {
    ZoneScopedN("Imgui render");

    scene.showImGuiDetails(&camera);

    static double fps_max = -1;
    static double max_timestamp;
    static double fps_min = 1000000;
    static double min_timestamp;
    auto fps = 1.0f / deltaTime;
    if (fps > fps_max) {
        fps_max = fps;
        max_timestamp = Time::Instance().LastFrame();
    }
    if (fps < fps_min) {
        fps_min = fps;
        min_timestamp = Time::Instance().LastFrame();
    }
    ImGui::Begin(format("FPS: {:.2f} H: {:.2f} L: {:.2f}###FPS_COUNTER", fps, fps_max, fps_min).c_str());
    ImGui::Text("%s", std::format("Time: {:.3f}", Time::Instance().LastFrame()).c_str());
    ImGui::Text("%s", std::format("High @ {:.3f}", max_timestamp).c_str());
    ImGui::Text("%s", std::format("Low @ {:.3f}", min_timestamp).c_str());
    if (ImGui::Button("Clear")) {
        fps_max = -1;
        max_timestamp = 0;
        fps_min = 1000000;
        min_timestamp = 0;
    }
    ImGui::End();

    static LevelGenerator::Config levelGenConfig{
            .seed {},
            .size {100, 100},
            .wallThickness = 1.f,
            .baseRadius = 4.5f,
            .keyRadius = 4.f,
            .pocketRadius = 2.5f,
            .noiseImpact = 1.f,
            .keyDistances {20.f, 20.f, 30.f, 30.f, 40.f},
            .extraPocketAttempts = 10000,
            .keyEnemies = 3,
            .minEnemies = 0,
            .maxEnemies = 2,
            .unitCount = 3,
            .chestCount = 10,
            .lootTable = {
                    {0, 1.f,  0.f},
                    {1, 0.5f, 0.5f},
                    {2, 0.f,  1.f},
            },
            .encounterTable = {
                {'x', 1.f, 1.f},
                {'s', 0.f, 2.f},
            },
    };
    static char seedString[64] = "";
    ImGui::Begin("Level generator");
    ImGui::InputText("Seed (empty = random)", seedString, std::size(seedString));
    ImGui::SliderFloat("Wall thickness", &levelGenConfig.wallThickness, 0.f, 20.f);
    ImGui::SliderFloat("Base radius", &levelGenConfig.baseRadius, 1.f, 20.f);
    ImGui::SliderFloat("Ore room radius", &levelGenConfig.keyRadius, 1.f, 20.f);
    ImGui::SliderFloat("Generic room radius", &levelGenConfig.pocketRadius, 1.f, 20.f);
    ImGui::SliderFloat("Noise impact", &levelGenConfig.noiseImpact, 0.f, 10.f);
    ImGui::SliderInt("Enemies in ore room", &levelGenConfig.keyEnemies, 0, 20);
    ImGui::SliderInt("Min enemies in generic room", &levelGenConfig.minEnemies, 0, 20);
    ImGui::SliderInt("Max enemies in generic room", &levelGenConfig.maxEnemies, 0, 20);
    ImGui::SliderInt("Unit count", &levelGenConfig.unitCount, 0, 10);
    ImGui::SliderInt("Chest count", &levelGenConfig.chestCount, 0, 30);
    if (ImGui::Button("Generate")) {
        spdlog::trace("Generating level");
        std::string_view sv = seedString;
        if (sv.empty()) {
            levelGenConfig.seed = pcgRandomSeed();
        } else {
            bool isRealSeed = sv.size() == 32 && std::all_of(sv.begin(), sv.end(), [](char c) {
                return std::isxdigit(static_cast<unsigned char>(c));
            });
            if (isRealSeed) {
                std::from_chars(sv.data(), sv.data() + 16, levelGenConfig.seed.first, 16);
                std::from_chars(sv.data() + 16, sv.data() + 32, levelGenConfig.seed.second, 16);
            } else {
                std::hash<std::string_view> hash;
                levelGenConfig.seed = {hash(sv), hash(sv.substr(1))};
            }
        }
        auto level = generateLevel(levelGenConfig);
        std::ofstream("save.txt") << level;
        spdlog::trace("New level saved to save.txt");
    }
    ImGui::End();

    ImGui::Begin("Chest Test");
    static glm::ivec2 chestpos;
    static int chestitem = 1;
    ImGui::DragInt2("Chest pos", glm::value_ptr(chestpos));
    ImGui::InputInt("Item Type ID", &chestitem);
    if (ImGui::Button("Add chest")) {
        auto tile = scene.systemManager.getSystem<Grid>()->getTileAt(chestpos.x, chestpos.y);
        if (tile->state == WALL) {
            tile->state = CHEST;
            tile->getEntity()->getComponent<IMineable>()->Remove();
            tile->getEntity()->addComponent(make_unique<MineableChest>(Vector2Int(chestpos.x, chestpos.y),
                                                                       scene.systemManager.getSystem<Grid>(),
                                                                       chestitem));
            tile->getEntity()->addComponent(make_unique<PointLight>());
            tile->getEntity()->getComponent<PointLight>()->data.diffuse = ztgk::color.YELLOW;
            tile->getEntity()->getComponent<PointLight>()->data.specular = ztgk::color.YELLOW;
            scene.stopRenderingImgui = true;
        } else if (tile->state == FLOOR) {
            tile->state = WALL;
            scene.systemManager.getSystem<Grid>()->SetUpWall(tile);
            tile->state = CHEST;
            tile->getEntity()->addComponent(make_unique<MineableChest>(Vector2Int(chestpos.x, chestpos.y),
                                                                       scene.systemManager.getSystem<Grid>(),
                                                                       chestitem));
            tile->getEntity()->addComponent(make_unique<PointLight>());
            tile->getEntity()->getComponent<PointLight>()->data.diffuse = ztgk::color.YELLOW;
            tile->getEntity()->getComponent<PointLight>()->data.specular = ztgk::color.YELLOW;
            scene.stopRenderingImgui = true;
        }
    }
    static Tile *peektile = nullptr;
    if (ImGui::Button("Peek tile")) {
        peektile = scene.systemManager.getSystem<Grid>()->getTileAt(chestpos.x, chestpos.y);
    }
    if (peektile != nullptr) {
        if (ImGui::TreeNode("Tile")) {
            peektile->showImGuiDetails(&camera);
            ImGui::TreePop();
        }
    }
    ImGui::End();

    //lightSystem.showLightTree();
    ztgk::console.imguiWindow();
    // bloomSystem .showImguiOptions();
}

void imgui_end() {
    ZoneScopedN("Imgui end");

    ImGui::End();
    ImGuiIO &io = ImGui::GetIO();

    if (io.MouseDrawCursor) {
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    } else {
        ImGui::EndFrame();
    }

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

// put things here that need continuous input handling and cannot work with events; otherwise use the SignalQueue
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {

    if (ztgk::game::gameStarted) {
        camera.MoveCamera(window);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!timeStepKeyPressed) {
            if (timeStep == 0) {
                timeStep = 1;
            } else {
                timeStep = 0;
            }
        }
        timeStepKeyPressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        timeStepKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !isXpressed) {
        ztgk::game::scene->systemManager.getSystem<WashingMachine>()->onPraniumDelivered();
        spdlog::debug("clearing tiles in radius");
        isXpressed = true;
//        radiusToRemove +=1;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
        isXpressed = false;
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    display_h = height;
    display_w = width;
    ztgk::game::window_size = {width, height};
    camera.UpdateCamera(width, height);
    bloomSystem.SetUpBuffers(width, height);
    scene.systemManager.getSystem<PhongPipeline>()->SetUpTextureBuffers(width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    ztgk::game::cursor.move({xposIn, yposIn});

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (ztgk::game::gameStarted) {

        ztgk::game::cursor.scroll({xoffset, yoffset});
        camera.MoveCamera(yoffset);
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    ztgk::game::cursor.click(button, action, mods);
//    if (ztgk::game::cursor.config.capture_click)
//        handle_picking(window, button, action, mods);

}

void update_dragged_tiles() {
    ZoneScopedN("Update dragged tiles");

    glm::vec3 worldPressCoords = camera.getDirFromCameraToCursor(ztgk::game::cursor.raw_pos.x, ztgk::game::cursor.raw_pos.y, camera.saved_display_w,
                                                                 camera.saved_display_h);
    std::unique_ptr<Ray> ray = make_unique<Ray>(camera.Position, worldPressCoords, scene.systemManager.getSystem<CollisionSystem>());

    if ((isLeftMouseButtonHeld || isRightMouseButtonHeld) && ray != nullptr && ray->getHitEntity() != nullptr) {
        Vector2Int mouseHeldStartGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldStartPos));
        mouseHeldEndPos = ray->getHitEntity()->transform.getGlobalPosition();
        Vector2Int mouseHeldEndGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldEndPos));
        std::vector<Vector2Int> tilesInArea = VectorUtils::getAllTilesBetween(mouseHeldStartGridPos, mouseHeldEndGridPos);
        if (!selectedTiles.empty()) {
            for (auto tile: selectedTiles) {
                auto cTile = scene.systemManager.getSystem<Grid>()->getTileAt(tile);
                cTile->setHighlight(CLEAR);
                cTile->setHighlightPresetFromState();
            }
        }
        selectedTiles = tilesInArea;
        for(auto tile : tilesInArea){
            auto cTile = scene.systemManager.getSystem<Grid>()->getTileAt(tile);
            if (isLeftMouseButtonHeld)
                cTile->setHighlight(SELECTION_LMB_GREEN);
            else if (isRightMouseButtonHeld) {
                if (cTile->state == BUG || cTile->state == SHROOM)
                    cTile->setHighlight(HIGHLIGHT_ENEMY_RED);
                else if (cTile->state != CHEST && cTile->state != ORE)
                    cTile->setHighlight(SELECTION_RMB_BLUE);
            }
        }

    }

}

void handle_picking(GLFWwindow *window, int button, int action, int mods) {

    //calculate ray every mouse press and release
    glm::vec3 worldPressCoords = camera.getDirFromCameraToCursor(ztgk::game::cursor.raw_pos.x, ztgk::game::cursor.raw_pos.y, display_w,
                                                                 display_h);
    std::unique_ptr<Ray> ray = make_unique<Ray>(camera.Position, worldPressCoords, scene.systemManager.getSystem<CollisionSystem>());

    std::vector<Vector2Int> tilesInArea;
    if ((isLeftMouseButtonHeld || isRightMouseButtonHeld) && ray->getHitEntity() != nullptr) {
//        spdlog::info("Mouse held");
        Vector2Int mouseHeldStartGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldStartPos));
        mouseHeldEndPos = ray->getHitEntity()->transform.getGlobalPosition();
        Vector2Int mouseHeldEndGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldEndPos));
        tilesInArea = VectorUtils::getAllTilesBetween(mouseHeldStartGridPos, mouseHeldEndGridPos);
    }

    //if left mouse button is pressed, start timer and save position of the mouse press
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        LmouseHeldStartTime = glfwGetTime();
        mouseHeldStartPosScr = ztgk::game::cursor.raw_pos;
        isLeftMouseButtonHeld = true;
        if (ray->getHitEntity() != nullptr) {
            mouseHeldStartPos = ray->getHitEntity()->transform.getGlobalPosition();
        }
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        RmouseHeldStartTime = glfwGetTime();
        mouseHeldStartPosScr = ztgk::game::cursor.raw_pos;
        isRightMouseButtonHeld = true;
        if (ray->getHitEntity() != nullptr) {
            mouseHeldStartPos = ray->getHitEntity()->transform.getGlobalPosition();
        }
    }

    //if left mouse button is released, check if it was a click or a drag
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        LmouseHeldReleaseTime = glfwGetTime();
        isLeftMouseButtonHeld = false;

        //if mouse was held for less than 0.1 seconds, consider it a click
        if (LmouseHeldReleaseTime - LmouseHeldStartTime < 0.2f && glm::length(mouseHeldStartPosScr - ztgk::game::cursor.raw_pos) < 10) {

            //check for double click
            if (glfwGetTime() - lastLeftClickTime < 0.2f) {
//                spdlog::debug("Left double click detected");
                //deselect all units
                scene.systemManager.getSystem<UnitSystem>()->deselectAllUnits();
                ztgk::game::ui_data.tracked_unit_id = -1;
            }
            lastLeftClickTime = glfwGetTime();
            // if ray hits an allied unit
            Unit *hitAlly = nullptr;
            if (ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Unit>() != nullptr && ray->getHitEntity()->getComponent<Unit>()->isAlly) {
                hitAlly = ray->getHitEntity()->getComponent<Unit>();
            } else if (ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Tile>() != nullptr
                       && ray->getHitEntity()->getComponent<Tile>()->unit != nullptr
                       && ray->getHitEntity()->getComponent<Tile>()->unit->isAlly) {
                hitAlly = ray->getHitEntity()->getComponent<Tile>()->unit;
            }

            if (hitAlly && hitAlly->isAlive) {
                // todo handle selection with mods for unified controls, rework shortcuts
                // do not update tile highlight here -> unit update will take care of this
                //if it is already selected, deselect it
                if (hitAlly->isSelected) {
                    scene.systemManager.getSystem<UnitSystem>()->deselectUnit(hitAlly);
                    if (ztgk::game::ui_data.tracked_unit_id == hitAlly->uniqueID)
                        ztgk::game::ui_data.tracked_unit_id = -1;
                }
                    //if it is not selected, select it
                else {
                    scene.systemManager.getSystem<UnitSystem>()->selectUnit(hitAlly);
                    ztgk::game::ui_data.tracked_unit_id = hitAlly->uniqueID;
                }
            }

            Unit *hitEnemy = nullptr;
            if (ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Unit>() != nullptr && !ray->getHitEntity()->getComponent<Unit>()->isAlly) {
                hitEnemy = ray->getHitEntity()->getComponent<Unit>();
            } else if (ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Tile>() != nullptr
                       && ray->getHitEntity()->getComponent<Tile>()->unit != nullptr
                       && !ray->getHitEntity()->getComponent<Tile>()->unit->isAlly) {
                hitEnemy = ray->getHitEntity()->getComponent<Tile>()->unit;
            }

            // unit update will take care of highlight under self
            if (hitEnemy)
                ztgk::game::ui_data.tracked_unit_id = hitEnemy->uniqueID;
        }
            //if mouse was held for more than 0.1 seconds, consider it a drag
        else {
            if (ray->getHitEntity() != nullptr) {
                mouseHeldEndPos = ray->getHitEntity()->transform.getGlobalPosition();
                Vector2Int mouseHeldStartGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldStartPos));
                Vector2Int mouseHeldEndGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldEndPos));

                for (auto tile: selectedTiles) {
                    scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setHighlight(CLEAR);
                    scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setHighlightPresetFromState();
                }

                tilesInArea = VectorUtils::getAllTilesBetween(mouseHeldStartGridPos, mouseHeldEndGridPos);
                selectedTiles = tilesInArea;
                std::vector<Tile *> cTilesInArea;

                //get all cTilesInArea in the area
                for (auto tile: tilesInArea) {
                    cTilesInArea.push_back(scene.systemManager.getSystem<Grid>()->getTileAt(tile));
                }
                std::vector<Unit *> Sponges;
                std::vector<Unit *> enemies;
                //get all units and mineables in the area
                for (auto tile: cTilesInArea) {
                    if (tile->unit != nullptr) {
                        if (tile->unit->isAlly) {
                            Sponges.push_back(tile->unit);
                        } else {
                            enemies.push_back(tile->unit);
                        }
                    }
                }

                // this will highlight allies
                //select all Sponges in the area
                if (!Sponges.empty()) {
                    for (auto sponge: Sponges) {
                        scene.systemManager.getSystem<UnitSystem>()->selectUnit(sponge);
                    }
                } else if (!enemies.empty()) {
                    // if there is group preview for enemies, select them here
                    ztgk::game::ui_data.tracked_unit_id = enemies.at(0)->uniqueID;
                }

            }
        }

    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        RmouseHeldReleaseTime = glfwGetTime();
        isRightMouseButtonHeld = false;

        Entity *hit = ray->getHitEntity();
        if (hit == nullptr) {
            return;
        }


        //if mouse was held for less than 0.2 seconds, consider it a click
        if (RmouseHeldReleaseTime - RmouseHeldStartTime < 0.2f && glm::length(mouseHeldStartPosScr - ztgk::game::cursor.raw_pos) < 10) {
            if (glfwGetTime() - lastRightClickTime < 0.2f) {
//                spdlog::debug("Right double click detected");
            }
            lastRightClickTime = glfwGetTime();

            std::vector<Unit *> selectedSponges = scene.systemManager.getSystem<UnitSystem>()->selectedUnits;

            if (!selectedSponges.empty()) {
                auto kiddo = hit->getChild("OnMapItem");
                PickupubleItem *pickupableItem = nullptr;
                if (kiddo != nullptr) {
                    pickupableItem = hit->getChild("OnMapItem")->getComponent<PickupubleItem>();
                } else {
                    pickupableItem = hit->getComponent<PickupubleItem>();
                }
                if (pickupableItem != nullptr) {
                    //sort sponges by distance to pickupable item ascending using pickupableItem->getEntity()->transform.getLocalPosition()
                    std::sort(selectedSponges.begin(), selectedSponges.end(), [pickupableItem](Unit *a, Unit *b) {
                        return VectorUtils::Distance(VectorUtils::GlmVec3ToVector3(a->getEntity()->transform.getGlobalPosition()), VectorUtils::GlmVec3ToVector3(pickupableItem->getEntity()->transform.getGlobalPosition())) <
                               VectorUtils::Distance(VectorUtils::GlmVec3ToVector3(b->getEntity()->transform.getGlobalPosition()), VectorUtils::GlmVec3ToVector3(pickupableItem->getEntity()->transform.getGlobalPosition()));
                    });

                    selectedSponges[0]->pickupTarget = pickupableItem;
                    selectedSponges[0]->hasPickupTarget = true;
                    selectedSponges[0]->movementTarget = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(
                            VectorUtils::GlmVec3ToVector3(hit->transform.getGlobalPosition()));
                    selectedSponges[0]->hasMovementTarget = true;

                    return;

                }
                Entity *hitWashingMachine = nullptr;
                if (hit->getComponent<BoxCollider>()->collisionType == CollisionType::WASHING_MACHINE) {
                    hitWashingMachine = hit;
                }
                auto hitMineable = hit->getMineableComponent<IMineable>(hit);
                if (hitMineable == nullptr) {
                    Entity *chestChild = hit->getChild("ChestChild");
                    if (chestChild != nullptr) {
                        hitMineable = chestChild->getMineableComponent<IMineable>(chestChild);
                    }
                }

                auto hitTile = hit->getComponent<Tile>();
                auto hitUnit = hit->getComponent<Unit>();
                if (hitUnit == nullptr && hitTile != nullptr) {
                    if (!hitUnit && hitTile && (hitTile->state == SPONGE || hitTile->state == BUG || hitTile->state == SHROOM)) {
                        hitUnit = hitTile->unit;
                    }
                }

                for (auto sponge: selectedSponges) {
                    sponge->hasMovementTarget = false;
                    sponge->miningTargets.clear();
                    sponge->currentMiningTarget = nullptr;
                    sponge->hasMiningTarget = false;
                    sponge->combatTarget = nullptr;
                    sponge->hasCombatTarget = false;
                    sponge->pathfinding.path.clear();

                    if (hitWashingMachine != nullptr) {
                        sponge->ForcedMovementState = true;
                        sponge->forcedMovementTarget = sponge->pathfinding.GetNearestVacantTile(scene.systemManager.getSystem<Grid>()->GetNearestWashingMachineTile(sponge->gridPosition), sponge->gridPosition);

                        sponge->hasMiningTarget = false;
                        sponge->miningTargets.clear();
                        sponge->hasCombatTarget = false;
                        sponge->combatTarget = nullptr;
                        sponge->currentMiningTarget = nullptr;

                        sponge->hasMovementTarget = true;
                        sponge->pathfinding.path.clear();
                        sponge->movementTarget = sponge->forcedMovementTarget;

                    }


                    if (hitUnit != nullptr) {
                        if (hitUnit->isAlly) {} //do nothing
                        else {
                            sponge->hasCombatTarget = true;
                            sponge->combatTarget = hitUnit;
                            continue;
                        }
                    }

                    if (hitMineable != nullptr) {
                        if (!hitMineable->isMined) {
                            sponge->miningTargets.clear();
                            sponge->miningTargets.emplace_back(hitMineable);
                            sponge->hasMiningTarget = true;
                            continue;
                        }
                    }

                    if (hitTile != nullptr) {
                        sponge->ForcedMovementState = true;
                        sponge->forcedMovementTarget = hitTile->index;

                        sponge->hasMiningTarget = false;
                        sponge->miningTargets.clear();
                        sponge->hasCombatTarget = false;
                        sponge->combatTarget = nullptr;

                        sponge->hasMovementTarget = true;
                        sponge->pathfinding.path.clear();
                        sponge->movementTarget = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(
                                VectorUtils::GlmVec3ToVector3(hit->transform.getGlobalPosition()));

                    }
                }


            }
        }
            //if mouse was held for more, consider it a drag
        else {
            if (ray->getHitEntity() != nullptr) {
                mouseHeldEndPos = ray->getHitEntity()->transform.getGlobalPosition();
                Vector2Int mouseHeldStartGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(
                        VectorUtils::GlmVec3ToVector3(mouseHeldStartPos));
                Vector2Int mouseHeldEndGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(
                        VectorUtils::GlmVec3ToVector3(mouseHeldEndPos));

                for (auto tile: selectedTiles) {
                    scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setHighlight(CLEAR);
                    scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setHighlightPresetFromState();
                }

                tilesInArea = VectorUtils::getAllTilesBetween(mouseHeldStartGridPos, mouseHeldEndGridPos);
                selectedTiles = tilesInArea;
                update_dragged_tiles();
                std::vector<Tile *> cTilesInArea;

                std::vector<IMineable *> Mineables = {};
                std::vector<Unit *> Enemies = {};

                for (auto tile: tilesInArea) {
                    cTilesInArea.push_back(scene.systemManager.getSystem<Grid>()->getTileAt(tile));
                }

                for (auto tile: cTilesInArea) {
                    auto possibleMineable = tile->getEntity()->getMineableComponent<IMineable>(tile->getEntity());
                    if (possibleMineable != nullptr) {
                        Mineables.push_back(possibleMineable);
                    }

                    if (tile->unit != nullptr) {
                        if (!tile->unit->isAlly) {
                            Enemies.push_back(tile->unit);
                        }
                    }
                }
                if (!Enemies.empty()) {
                    if (!scene.systemManager.getSystem<UnitSystem>()->selectedUnits.empty()) {
                        for (auto Sponge: scene.systemManager.getSystem<UnitSystem>()->selectedUnits) {
                            //sort enemies by distance to sponge ascending
                            std::sort(Enemies.begin(), Enemies.end(), [Sponge](Unit *a, Unit *b) {
                                return VectorUtils::Distance(Sponge->gridPosition, a->gridPosition) < VectorUtils::Distance(Sponge->gridPosition, b->gridPosition);
                            });

                            for (auto enemy: Enemies) {
                                if (Sponge->canPathToAttackTarget(enemy)) {
                                    Sponge->hasCombatTarget = true;
                                    Sponge->combatTarget = enemy;
                                    break;
                                }
                            }

                        }
                    }
                } else if (!Mineables.empty()) {
                    if (!scene.systemManager.getSystem<UnitSystem>()->selectedUnits.empty()) {
                        for (auto Sponge: scene.systemManager.getSystem<UnitSystem>()->selectedUnits) {
                            Sponge->miningTargets.clear();
                            for (auto mineable: Mineables) {
                                if (!mineable->isMined) {
                                    Sponge->miningTargets.emplace_back(mineable);
                                    Sponge->hasMiningTarget = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    scene.systemManager.getSystem<WireRenderSystem>()->rayComponents.push_back(std::move(ray));

}

void handleControls(int key, int scancode, int action, int mods) {
    if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9 && mods == 0 && action == GLFW_PRESS) {
        scene.systemManager.getSystem<UnitSystem>()->deselectAllUnits();
        auto allies = scene.systemManager.getSystem<UnitSystem>()->unitComponents | std::views::filter([](auto unit) { return unit->isAlly; });
        auto idx = key - GLFW_KEY_1;
        for (auto ally: allies) {
            if (idx == 0) {
                scene.systemManager.getSystem<UnitSystem>()->selectUnit(ally);
                ztgk::game::ui_data.tracked_unit_id = ally->uniqueID;
                break;
            }
            --idx;
        }
    }
    if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9 && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS) {
        auto allies = scene.systemManager.getSystem<UnitSystem>()->unitComponents | std::views::filter([](auto unit) { return unit->isAlly; });
        auto idx = key - GLFW_KEY_1;
        for (auto ally: allies) {
            if (idx == 0) {
                scene.systemManager.getSystem<UnitSystem>()->selectUnit(ally);
                break;
            }
            --idx;
        }
        ztgk::game::ui_data.tracked_unit_id = -1;
    }
    if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9 && mods == GLFW_MOD_ALT && action == GLFW_PRESS) {
        auto allies = scene.systemManager.getSystem<UnitSystem>()->unitComponents | std::views::filter([](auto unit) { return unit->isAlly; });
        auto idx = key - GLFW_KEY_1;
        for (auto ally: allies) {
            if (idx == 0) {
                scene.systemManager.getSystem<UnitSystem>()->deselectUnit(ally);
                if (ztgk::game::ui_data.tracked_unit_id == ally->uniqueID)
                    ztgk::game::ui_data.tracked_unit_id = -1;
                break;
            }
            --idx;
        }
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        auto pause = scene.systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_pause);
        if (!pause->isHidden()) {
            auto settings = scene.systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_settings);
        }
        pause->setHidden(!pause->isHidden());
    }
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key == GLFW_KEY_A && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS) {
        for (auto unit: scene.systemManager.getSystem<UnitSystem>()->unitComponents | std::views::filter([](auto unit) { return unit->isAlly; })) {
            scene.systemManager.getSystem<UnitSystem>()->selectUnit(unit);
        }
    }
    if (key == GLFW_KEY_A && mods == GLFW_MOD_ALT && action == GLFW_PRESS) {
        scene.systemManager.getSystem<UnitSystem>()->deselectAllUnits();
        ztgk::game::ui_data.tracked_unit_id = -1;
    }
    if (key == GLFW_KEY_A && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT) && action == GLFW_PRESS) {
        auto old_selection = scene.systemManager.getSystem<UnitSystem>()->selectedUnits;
        for (auto unit: scene.systemManager.getSystem<UnitSystem>()->unitComponents | std::views::filter([](auto unit) { return unit->isAlly; })) {
            scene.systemManager.getSystem<UnitSystem>()->selectUnit(unit);
        }
        for (auto unit: old_selection) {
            scene.systemManager.getSystem<UnitSystem>()->deselectUnit(unit);
        }
        ztgk::game::ui_data.tracked_unit_id = -1;
    }
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    *ztgk::game::signalQueue += KeySignalData::signal(key, scancode, action, mods, "Forwarding GLFW event.");
#ifdef DEBUG_BUILD
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
#endif
}

void end_frame() {
    ZoneScopedN("End frame");

    // Poll and handle events (inputs, window reinitWithSize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
    {
        ZoneScopedN("VSync buffer");
        glfwSwapBuffers(window);
    }
    FrameMark;
}

void init_camera() {
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    lastX = display_w / 2.0f;
    lastY = display_h / 2.0f;
}

void init_time() {
    Time::Instance().SetLastFrame(glfwGetTime());
}

void gen_and_load_lvl(bool gen_new_lvl) {
    if (!gen_new_lvl) {
        std::ifstream file("save.txt");
        if (file.good()) {
            LevelSaving::load();
            return;
        }
    }

    static LevelGenerator::Config levelGenConfig{
            .seed {},
            .size {100, 100},
            .wallThickness = 1.f,
            .baseRadius = RNG::RandomFloat(8.f, 12.f),
            .keyRadius = RNG::RandomFloat(5.f, 8.f),
            .pocketRadius = RNG::RandomFloat(3.f, 8.f),
            .noiseImpact = RNG::RandomFloat(0.1f, 0.3f),
            .keyDistances {20.f, 20.f, 30.f, 30.f, 40.f},
            .extraPocketAttempts = 10000,
            .keyEnemies = RNG::RandomInt(3, 4),
            .minEnemies = 2,                       //0        <--- if those values are different from those in comments, I forgot to change them after debugging
            .maxEnemies = 5,                       //4        <---
            .unitCount = 3,                        //3        <---
            .chestCount = RNG::RandomInt(20, 30),  //20, 30    <---
            .lootTable = {
                    {static_cast<int>(Item::item_types.mop),       1.f,  0.f},
                    {static_cast<int>(Item::item_types.super_mop), 0.5f, 0.5f},
                    {static_cast<int>(Item::item_types.water_gun), 0.f,  1.f},
                    {static_cast<int>(Item::item_types.beacon),    10.f, 0.f, 2},
                    {static_cast<int>(Item::item_types.detergent), 0.5f, 0.5f},
                    {static_cast<int>(Item::item_types.pendant),   0.5f, 1.5f},
            },
            .encounterTable = {
                {'x', 1.f, 1.f},
                {'s', 0.f, 2.f},
            },
    };

    static char seedString[64] = "";
    std::string_view sv = seedString;
    if (sv.empty()) {
        levelGenConfig.seed = pcgRandomSeed();
    } else {
        bool isRealSeed = sv.size() == 32 && std::all_of(sv.begin(), sv.end(), [](char c) {
            return std::isxdigit(static_cast<unsigned char>(c));
        });
        if (isRealSeed) {
            std::from_chars(sv.data(), sv.data() + 16, levelGenConfig.seed.first, 16);
            std::from_chars(sv.data() + 16, sv.data() + 32, levelGenConfig.seed.second, 16);
        } else {
            std::hash<std::string_view> hash;
            levelGenConfig.seed = {hash(sv), hash(sv.substr(1))};
        }
    }
    auto level = generateLevel(levelGenConfig);
    std::ofstream("save.txt") << level;
    spdlog::trace("New level saved to save.txt");


    LevelSaving::load();

}

#pragma endregion Functions
