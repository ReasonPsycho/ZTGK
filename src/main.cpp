
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

#pragma endregion Includes

#pragma region constants

Scene scene;
string modelPath = "res/models/asteroid/Asteroid.fbx";
string modelPathGabka = "res/models/gabka/pan_gabka_lower_poly.fbx";
string modelPathGabkaMove = "res/models/gabka/pan_gabka_move.fbx";
string modelPathGabkaIdle = "res/models/gabka/pan_gabka_idle.fbx";
string modelPathGabkaMine = "res/models/gabka/pan_gabka_mine.fbx";
string modelPathGabkaAttack = "res/models/gabka/pan_gabka_attack.fbx";
string modelPathZuczek = "res/models/zuczek/Zuczek.fbx";
string modelPathZuczekAttack = "res/models/zuczek/Zuczek_attack.fbx";
string modelPathZuczekIddle = "res/models/zuczek/Zuczek_iddle.fbx";
string modelPathZuczekMove = "res/models/zuczek/Zuczek_move.fbx";
string modelPathWall = "res/models/BathroomWall/BathroomWall.fbx";
string tileModelPath = "res/models/plane/Plane.fbx";
string washingMachinePath = "res/models/washingmachine/uhhhh.fbx";
string modelChestPath = "res/models/chest/chest.fbx";

ModelLoadingManager modelLoadingManager;
Model *tileModel;
Model *model;
Model *gabka;
Model *zuczek;
Model *wall;
Model *washingMachineModel;
Model *chestModel;
Model *cubeModel;
Model *quadModel;
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
Camera camera(glm::vec3(200.0f, 40.0f, 0.0f));

Primitives primitives;
PBRPrimitives pbrprimitives;

float lastY;
float lastX;

Entity *playerUnit;

std::vector<Vector2Int> selectedTiles;

bool captureMouse = false;
bool captureMouseButtonPressed = false;

ImGuiIO mouseio;
double mouseX;
double mouseY;

bool isLeftMouseButtonHeld = false;
glm::vec3 mouseHeldStartPos;
glm::vec3 mouseHeldEndPos;
float mouseHeldStartTime = 0.0f;
float mouseHeldReleaseTime = 0.0f;


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
        imgui_begin();
        imgui_render(); // edit this function to add your own ImGui controls
        imgui_end(); // this call effectively renders ImGui

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

    // Create window with graphics context
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dear ImGui GLFW+OpenGL4 example", NULL, NULL);
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

    ztgk::game::audioManager = new AudioManager();
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
        Signal::signal_types.mouse_button_signal,
        [](const Signal &signal) {
            auto data = std::dynamic_pointer_cast<MouseButtonSignalData>(signal.data);
            handle_picking(window, data->button, data->action, data->mods);
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
    ztgk::game::audioManager->setVolumeForGroup("ambient", 0);

    //intro music
    ztgk::game::audioManager->loadSound("res/sounds/intro_music.mp3", "intro_music");

    //lose music
    ztgk::game::audioManager->loadSound("res/sounds/lose.mp3", "lose");

    //win music
    ztgk::game::audioManager->loadSound("res/sounds/win.mp3", "win");

    //punch sounds
    ztgk::game::audioManager->loadSound("res/sounds/punch1.wav", "punch1");
    ztgk::game::audioManager->loadSound("res/sounds/punch2.wav", "punch2");
    ztgk::game::audioManager->loadSound("res/sounds/punch3.wav", "punch3");
    ztgk::game::audioManager->loadSound("res/sounds/punch4.wav", "punch4");
    ztgk::game::audioManager->loadSound("res/sounds/punch5.wav", "punch5");
    ztgk::game::audioManager->loadSound("res/sounds/punch6.wav", "punch6");
    ztgk::game::audioManager->loadSound("res/sounds/punch7.wav", "punch7");

    //bubble pop
    ztgk::game::audioManager->loadSound("res/sounds/bubble1.mp3", "bubble1");

    //bubbles bulbulbulbul
    ztgk::game::audioManager->loadSound("res/sounds/bubbles.mp3", "bubbles");

    //bug walking
    ztgk::game::audioManager->loadSound("res/sounds/bug1.mp3", "bug2");

    //clicks for UI
    ztgk::game::audioManager->loadSound("res/sounds/click1.mp3", "click1");
    ztgk::game::audioManager->loadSound("res/sounds/click2.mp3", "click2");

    //death sounds OOF
    ztgk::game::audioManager->loadSound("res/sounds/deathEnemy1.mp3", "deathEnemy1");
    ztgk::game::audioManager->loadSound("res/sounds/deathEnemy2.mp3", "deathEnemy2");
    ztgk::game::audioManager->loadSound("res/sounds/deathSponge1.wav", "deathSponge1");
    ztgk::game::audioManager->loadSound("res/sounds/deathSponge2.wav", "deathSponge2");
    ztgk::game::audioManager->loadSound("res/sounds/deathSponge3.mp3", "deathSponge3");

    //gabka walking
    ztgk::game::audioManager->loadSound("res/sounds/gabka1.mp3", "gabka1");
    ztgk::game::audioManager->loadSound("res/sounds/gabka2.mp3", "gabka2");
    ztgk::game::audioManager->loadSound("res/sounds/gabka3.mp3", "gabka3");
    ztgk::game::audioManager->loadSound("res/sounds/gabka4.mp3", "gabka4");
    ztgk::game::audioManager->loadSound("res/sounds/gabka5.mp3", "gabka5");

    //gabka celaning tiles
    ztgk::game::audioManager->loadSound("res/sounds/idle1.mp3", "idle1");
    ztgk::game::audioManager->loadSound("res/sounds/idle2.mp3", "idle2");

    //mining sound
    ztgk::game::audioManager->loadSound("res/sounds/mining1.mp3", "mining1");
    ztgk::game::audioManager->loadSound("res/sounds/mining2.mp3", "mining2");
    ztgk::game::audioManager->loadSound("res/sounds/mining3.mp3", "mining3");
    ztgk::game::audioManager->loadSound("res/sounds/mining4.mp3", "mining4");

    //pralka 1 - slow pralka sounds
    ztgk::game::audioManager->loadSound("res/sounds/pralka1.mp3", "pralka1");

    //pralka 2 - crazy fast pralka sounds
    ztgk::game::audioManager->loadSound("res/sounds/pralka2.mp3", "pralka2");

    //quack
    ztgk::game::audioManager->loadSound("res/sounds/rubberduck1.mp3", "rubberduck1");
    ztgk::game::audioManager->loadSound("res/sounds/rubberduck2.mp3", "rubberduck2");


}

void load_enteties() {
    Color color = {255, 255, 255, 255}; // this is equivalent to white color

    int n = sizeof(pbrprimitives.quadIndices) / sizeof(pbrprimitives.quadIndices[0]);

    // Convert the array to a vector
    std::vector<unsigned int> vec(pbrprimitives.quadIndices, pbrprimitives.quadIndices + n);

    tileModel = modelLoadingManager.GetModel(tileModelPath);
    model = modelLoadingManager.GetModel(modelPath);
    gabka = modelLoadingManager.GetModel(modelPathGabka);
    zuczek = modelLoadingManager.GetModel(modelPathZuczek);
    wall = modelLoadingManager.GetModel(modelPathWall);
    washingMachineModel = modelLoadingManager.GetModel(washingMachinePath);
    chestModel = modelLoadingManager.GetModel(modelChestPath);
    modelLoadingManager.Innit();

    //quadModel = new Model(pbrprimitives.quadVAO, MaterialPhong(color), vec);
    quadModel = new Model(pbrprimitives.subdividedPlaneVAO[4], MaterialPhong(color), pbrprimitives.subdividedPlanesIndices[4]);

    ztgk::game::washingMachineModel = washingMachineModel;
    ztgk::game::playerModel = gabka;
    ztgk::game::bugModel = zuczek;
    ztgk::game::chestModel = chestModel;

    ztgk::game::scene->systemManager.getSystem<WashingMachine>()->createWashingMachine(washingMachineModel);


    Entity *gameObject;

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

//    gameObject = scene.addEntity("Dir light");
    //  gameObject->addComponent(make_unique<DirLight>(DirLightData(glm::vec4(glm::vec3(255), 1),glm::vec4(glm::vec3(255), 1), glm::vec4(1))));
    gameObject = scene.addEntity("Point Light");;
    gameObject->transform.setLocalPosition(glm::vec3(100, 4, 100));


    gameObject->addComponent(make_unique<PointLight>(
            PointLightData(glm::vec4(glm::vec3(1), 1), glm::vec4(glm::vec3(0.1), 1), glm::vec4(1, 1, 1, 1), 0.1f, 0.2f,
                           0.05f)));
    //  gameObject = scene.addEntity("Point Light 2");
    // gameObject->addComponent(make_unique<PointLight>(PointLightData(glm::vec4(glm::vec3(255),1),glm::vec4(glm::vec3(0),1),glm::vec4(0), 1.0f, 1.0f, 1.0f)));
    gameObject = scene.addEntity("Spot Light");
    gameObject->transform.setLocalPosition(glm::vec3(100, 4, 100));
    gameObject->addComponent(make_unique<SpotLight>(
            SpotLightData(glm::vec4(glm::vec3(5), 1), glm::vec4(glm::vec3(0), 1), glm::vec4(0), glm::vec4(1),
                          glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), 0.1f, 0.2f, 0.05f)));
    scene.systemManager.getSystem<LightSystem>()->Init();


    scene.systemManager.getSystem<InstanceRenderSystem>()->tileModel = quadModel;
    scene.systemManager.getSystem<Grid>()->LoadTileEntities(1.0f);

    //level gen and load___________________________________________________________________________________________________________________________________________________
    //comment it out if u want fast load for testing

//    gen_and_load_lvl(true);

    scene.systemManager.getSystem<InstanceRenderSystem>()->Innit();


//    auto ehud = scene.addEntity("HUD DEMO");
//
//    auto drag = scene.systemManager.getSystem<HUD>()->createButton(
//        "Drag\nme!",
//        {1000, 1000}, {100, 100}, ztgk::color.BLACK,
//        [](HUDHoverable * self){ self->collisionSprite->color = ztgk::color.GRAY * glm::vec4{0.85, 0.85, 0.85, 1}; },
//        [](HUDHoverable *self) {
//                                                       self->collisionSprite->color = ztgk::color.BLACK; },
//                                                       [](HUDButton * self){
//                                                   self->collisionSprite->color = ztgk::color.GRAY * glm::vec4{0.75, 0.75, 0.75, 1};
//            self->parentEntity->getComponent<SignalReceiver>()->receive_type_mask = Signal::signal_types.mouse_move_signal;
//        },
//        [](HUDButton *self) {
//                                                    self->collisionSprite->color = ztgk::color.GRAY * glm::vec4{0.85, 0.85, 0.85, 1};
//            self->parentEntity->getComponent<SignalReceiver>()->receive_type_mask = 0;
//        },
//        ehud
//   );
//    drag->addComponent(std::make_unique<SignalReceiver>(
//                                                       0,
//                                                       [drag](const Signal & signal) {
//    auto data = dynamic_pointer_cast<MouseMoveSignalData>(signal.data);
//            drag->getComponent<Sprite>()->pos = data->pos;
//                                                    drag->getComponent<Text>()->pos = data->pos;
//                                                }
//    ));
//
//    scene.systemManager.getSystem<HUD>()->createButton("Button text",
//                                                       {1750, 575}, {300, 100}, ztgk::color.CYAN, ztgk::color.TURQUOISE,
//                                                       ztgk::color.BLUE, []() { spdlog::info("Button pressed!"); },
//                                                       ehud);
//
//    scene.systemManager.getSystem<HUD>()->createButton(
//            {1750, 775}, {300, 300},
//            "res/textures/puni.png", "res/textures/container2.png",
//            []() { spdlog::info("2SPR Button pressed!"); },
//            ehud
//    );
//
//    scene.systemManager.getSystem<HUD>()->createButton(
//        "Func button textt", {1750, 1000}, {300, 150}, ztgk::color.BROWN,
//        [](HUDHoverable * self){ self->collisionSprite->color = ztgk::color.BROWN * glm::vec4{0.85, 0.85, 0.85, 1}; },
//        [](HUDHoverable * self){ self->collisionSprite->color = ztgk::color.BROWN; },
//        [](HUDButton * self){ self->collisionSprite->color = ztgk::color.BROWN * glm::vec4{0.75, 0.75, 0.75, 1}; },
//        [](HUDButton * self){ self->collisionSprite->color = ztgk::color.BROWN * glm::vec4{0.85, 0.85, 0.85, 1}; spdlog::info("Func Button pressed!"); },
//        ehud
//    );
//
//    scene.systemManager.getSystem<HUD>()->createSlider_Bar(
//        HORIZONTAL, {100, 100}, {1000, 100},
//        ztgk::color.CYAN * glm::vec4{0.8, 0.8, 0.8, 1}, ztgk::color.CYAN,
//        ehud
//    );
//    scene.systemManager.getSystem<HUD>()->createSlider_Bar(
//        HORIZONTAL, {100, 200}, {1000, 100},
//        ztgk::color.BLUE * glm::vec4{0.8, 0.8, 0.8, 1}, ztgk::color.BLUE,
//        ehud, 0,
//        true, 100
//        );
//
//    scene.systemManager.getSystem<HUD>()->createSlider_BarControllable(
//        HORIZONTAL, {100, 300}, {1000, 100},
//        ztgk::color.RED * glm::vec4{0.8, 0.8, 0.8, 1}, ztgk::color.RED,
//        ehud
//    );
//    scene.systemManager.getSystem<HUD>()->createSlider_BarControllable(
//        HORIZONTAL, {100, 400}, {1000, 100},
//        ztgk::color.ROSE * glm::vec4{0.8, 0.8, 0.8, 1}, ztgk::color.ROSE,
//        ehud, 0,
//        true, 100
//    );
//
//    scene.systemManager.getSystem<HUD>()->createSlider_SettingBar(HORIZONTAL, {100, 500}, {1000, 100}, ehud);
//    scene.systemManager.getSystem<HUD>()->createSlider_SettingBar(
//        HORIZONTAL, {100, 600}, {1000, 100},
//        ehud, 0,
//        1, 0, "{:.2f}/{:.2f}"
//    );
//
//
//    auto efg = scene.addEntity(ehud, "Foreground");
//    auto fgelem = scene.addEntity(efg, "Fixed");
//    fgelem->addComponent(make_unique<Text>("One line text", glm::vec2{100, 1000}));
//    zmgroup = scene.systemManager.getSystem<HUD>()->addGroup();
//    fgelem = scene.addEntity(efg, "Variable Text");
//    auto tx = Text("Multiline\ntext\nyea", glm::vec2(100, 800));
//    tx.groupID = zmgroup;
//    fgelem->addComponent(make_unique<Text>(tx));
//    zmtxt = fgelem->getComponent<Text>();
//
//    scene.systemManager.getSystem<HUD>()->getDefaultGroup()->setHidden(true);

    load_units();


}

void load_units() {

    playerUnit = scene.addEntity("Gabka");
    playerUnit->addComponent(make_unique<Render>(gabka));
    playerUnit->addComponent(make_unique<ColorMask>());
    playerUnit->addComponent(make_unique<AnimationPlayer>());
    playerUnit->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaMove] = modelLoadingManager.GetAnimation(modelPathGabkaMove, gabka);
    playerUnit->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaIdle] = modelLoadingManager.GetAnimation(modelPathGabkaIdle, gabka);
    playerUnit->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaMine] = modelLoadingManager.GetAnimation(modelPathGabkaMine, gabka);
    playerUnit->getComponent<AnimationPlayer>()->animationMap[modelPathGabkaAttack] = modelLoadingManager.GetAnimation(modelPathGabkaAttack, gabka);
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalPosition(glm::vec3(100, 7, 100));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    playerUnit->updateSelfAndChild();

    playerUnit = scene.addEntity("Żuczek");
    playerUnit->addComponent(make_unique<Render>(zuczek));
    playerUnit->addComponent(make_unique<ColorMask>());
 //   playerUnit->addComponent(make_unique<AnimationPlayer>());
 //   playerUnit->getComponent<AnimationPlayer>()->animationMap[modelPathZuczekAttack] = modelLoadingManager.GetAnimation(modelPathZuczekAttack, zuczek);
 //   playerUnit->getComponent<AnimationPlayer>()->animationMap[modelPathZuczekMove] = modelLoadingManager.GetAnimation(modelPathZuczekMove, zuczek);
 //   playerUnit->getComponent<AnimationPlayer>()->animationMap[modelPathZuczekIddle] = modelLoadingManager.GetAnimation(modelPathZuczekIddle, zuczek);
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalPosition(glm::vec3(100, 7, 100));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    playerUnit->updateSelfAndChild();
    /*
playerUnit = scene.addEntity("Player1");
playerUnit->addComponent(make_unique<Render>(gabka));
playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
playerUnit->transform.setLocalPosition(glm::vec3(0, -1, 0));
playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
playerUnit->updateSelfAndChild();
playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(1, 1, 1)));
playerUnit->getComponent<BoxCollider>()->setCenter(playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5));
playerUnit->addComponent(make_unique<Unit>("Player1", scene.systemManager.getSystem<Grid>(), Vector2Int(50, 50), Unit::ALLY_BASE, true));
stateManager = new StateManager(playerUnit->getComponent<Unit>());
stateManager->currentState = new IdleState(scene.systemManager.getSystem<Grid>());
stateManager->currentState->unit = playerUnit->getComponent<Unit>();
playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));


playerUnit = scene.addEntity("Player2");
playerUnit->addComponent(make_unique<Render>(&gabka));
playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
playerUnit->transform.setLocalPosition(glm::vec3(0, -1, 0));
playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
playerUnit->updateSelfAndChild();
playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(1, 1, 1)));
playerUnit->getComponent<BoxCollider>()->setCenter(playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5));
playerUnit->addComponent(make_unique<Unit>("Player2", scene.systemManager.getSystem<Grid>(), Vector2Int(60, 50), Unit::ALLY_BASE, true));
stateManager = new StateManager(playerUnit->getComponent<Unit>());
stateManager->currentState = new IdleState(scene.systemManager.getSystem<Grid>());
stateManager->currentState->unit = playerUnit->getComponent<Unit>();
playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));

playerUnit = scene.addEntity("Player3");
playerUnit->addComponent(make_unique<Render>(&gabka));
playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
playerUnit->transform.setLocalPosition(glm::vec3(0, -1, 0));
playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
playerUnit->updateSelfAndChild();
playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(1, 1, 1)));
playerUnit->getComponent<BoxCollider>()->setCenter(playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5));
playerUnit->addComponent(make_unique<Unit>("Player3", scene.systemManager.getSystem<Grid>(), Vector2Int(60, 60), Unit::ALLY_BASE, true));
stateManager = new StateManager(playerUnit->getComponent<Unit>());
stateManager->currentState = new IdleState(scene.systemManager.getSystem<Grid>());
stateManager->currentState->unit = playerUnit->getComponent<Unit>();
playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));

    Entity *enemyUnit = scene.addEntity("Enemy1");
    enemyUnit->addComponent(make_unique<Render>(zuczek));
    enemyUnit->transform.setLocalScale(glm::vec3(2, 2, 2));
    enemyUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    enemyUnit->updateSelfAndChild();
    enemyUnit->addComponent(make_unique<BoxCollider>(enemyUnit, glm::vec3(1, 1, 1)));
    enemyUnit->getComponent<BoxCollider>()->setCenter(enemyUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5));
    enemyUnit->addComponent(make_unique<Unit>("Enemy1", scene.systemManager.getSystem<Grid>(), Vector2Int(50, 60), Unit::ENEMY_BASE, false));
    stateManager = new StateManager(enemyUnit->getComponent<Unit>());
    stateManager->currentState = new IdleState(scene.systemManager.getSystem<Grid>());
    stateManager->currentState->unit = enemyUnit->getComponent<Unit>();
    enemyUnit->addComponent(make_unique<UnitAI>(enemyUnit->getComponent<Unit>(), stateManager));
//    */

}

void load_hud() {
    auto hud = scene.systemManager.getSystem<HUD>();
    auto ehud = scene.addEntity("HUD");

    ztgk::game::ui_data.gr_game = hud->addGroup(0, "Game");
    ztgk::game::ui_data.gr_map = hud->addGroup(ztgk::game::ui_data.gr_game, "Map");
    ztgk::game::ui_data.gr_middle = hud->addGroup(ztgk::game::ui_data.gr_game, "Unit Details");
    ztgk::game::ui_data.gr_actions = hud->addGroup(ztgk::game::ui_data.gr_game, "Action Panel");
    ztgk::game::ui_data.gr_top = hud->addGroup(ztgk::game::ui_data.gr_game, "Top Panel");
    ztgk::game::ui_data.gr_item = hud->addGroup(ztgk::game::ui_data.gr_game, "Item Details");

    ztgk::game::ui_data.gr_pause = hud->addGroup(0, "Pause");

    ztgk::game::ui_data.gr_settings = hud->addGroup(0, "Settings");
    ztgk::game::ui_data.gr_menu = hud->addGroup(0, "Menu");
    ztgk::game::ui_data.gr_credits = hud->addGroup(0, "Credits");

    ztgk::game::ui_data.gr_loadScreen = hud->addGroup(ztgk::game::ui_data.gr_menu, "Load Screen");
    ztgk::game::ui_data.gr_mainMenu = hud->addGroup(ztgk::game::ui_data.gr_menu, "Main Menu");

// menu
    auto emenu = scene.addEntity(ehud, "Menu");

    emenu->addComponent(make_unique<Sprite>(glm::vec2{0,0}, ztgk::game::window_size, ztgk::color.WHITE, ztgk::game::ui_data.gr_mainMenu, "res/textures/title_screen.png"));
    float ystep = (ztgk::game::window_size.y - 2*200) / 4.0f;
    glm::vec2 btn_pos = {ztgk::game::window_size.x*4/5, ztgk::game::window_size.y - 200};
    hud->createButton(
        "START", btn_pos, glm::vec2{200, 80},
        ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        [hud]() { gen_and_load_lvl(true); hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true); },
        emenu, ztgk::game::ui_data.gr_mainMenu
    );
    btn_pos.y -= ystep;
    hud->createButton(
        "LOAD", btn_pos, glm::vec2{200, 80},
        ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        [hud]() { gen_and_load_lvl(false); hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true); },
        emenu, ztgk::game::ui_data.gr_mainMenu
    );
    btn_pos.y -= ystep;
    hud->createButton(
        "Settings", btn_pos, glm::vec2{200, 80},
        ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        [hud]() { hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true); hud->getGroupOrDefault(ztgk::game::ui_data.gr_settings)->setHidden(false); },
        emenu, ztgk::game::ui_data.gr_mainMenu
    );
    btn_pos.y -= ystep;
    hud->createButton(
        "Credits", btn_pos, glm::vec2{200, 80},
        ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        [hud]() { hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(true); hud->getGroupOrDefault(ztgk::game::ui_data.gr_credits)->setHidden(false); },
        emenu, ztgk::game::ui_data.gr_mainMenu
    );
    btn_pos.y -= ystep;
    hud->createButton(
        "Quit", btn_pos, glm::vec2{200, 80},
        ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        []() { glfwSetWindowShouldClose(window, true); },
        emenu, ztgk::game::ui_data.gr_mainMenu
    );

// load/save screen
    auto eload = scene.addEntity(emenu, "Load Screen");
    eload->addComponent(make_unique<Sprite>(glm::vec2{0,0}, ztgk::game::window_size, ztgk::color.WHITE, ztgk::game::ui_data.gr_loadScreen));
    eload->addComponent(make_unique<Text>("Loading...", glm::vec2{ztgk::game::window_size.x/5, ztgk::game::window_size.y*8/10}, glm::vec2(1), ztgk::color.PLUM, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_loadScreen));
    eload->getComponent<Text>()->mode = CENTER;

// game
    auto egame = scene.addEntity(ehud, "Game");
    auto emap = scene.addEntity(egame, "Map");
    emap->addComponent(make_unique<Sprite>(glm::vec2{0,0}, glm::vec2{400,400}, ztgk::color.GRAY * 0.75f, ztgk::game::ui_data.gr_map));
    emap->addComponent(make_unique<Text>("Map", glm::vec2{200, 200}, glm::vec2(1), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.italic, NONE, ztgk::game::ui_data.gr_map));
    emap->getComponent<Text>()->mode = CENTER;

    auto emiddle = scene.addEntity(egame, "Unit Details");
    emiddle->addComponent(make_unique<Sprite>(glm::vec2{400,0}, glm::vec2{1120,250}, ztgk::color.GRAY * 0.75f, ztgk::game::ui_data.gr_middle));
    hud->createSlider_Bar(HORIZONTAL, glm::vec2{400, 275}, glm::vec2{1120, 50}, ztgk::color.GREEN * glm::vec4{0.5, 0.5, 0.5, 1}, ztgk::color.GREEN, emiddle, ztgk::game::ui_data.gr_middle, true, 100);

    auto eportrait = scene.addEntity(emiddle, "Portrait");
    eportrait->addComponent(make_unique<Sprite>(glm::vec2{400,0}, glm::vec2{250,250}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/gabka_cool.png"));

    auto ename = scene.addEntity(emiddle, "Name");
    ename->addComponent(make_unique<Text>("SPONGE", glm::vec2{700, 240}, glm::vec2(1.5), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_middle));
    ename->getComponent<Text>()->mode = TOP_LEFT;

    auto emodstip = scene.addEntity(emiddle, "Modstip");
    emodstip->addComponent(make_unique<Text>("Total stats:", glm::vec2{700, 175}, glm::vec2(0.5), ztgk::color.BLACK, ztgk::font.Fam_Nunito + ztgk::font.italic, NONE, ztgk::game::ui_data.gr_middle));
    emodstip->getComponent<Text>()->mode = TOP_LEFT;

    auto emods = scene.addEntity(emiddle, "Mods");
    auto ent = scene.addEntity(emods, "ATK");
    hud->createButton("ATK", glm::vec2{680, 137}, glm::vec2{25, 25}, ztgk::color.GRAY, ztgk::color.GRAY, ztgk::color.GRAY, [](){}, ent, ztgk::game::ui_data.gr_middle);
    ent->addComponent(make_unique<Text>("0.05 + 10", glm::vec2{710, 137}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "DEF");
    hud->createButton("DEF", glm::vec2{680, 112}, glm::vec2{25, 25}, ztgk::color.GRAY, ztgk::color.GRAY, ztgk::color.GRAY, [](){}, ent, ztgk::game::ui_data.gr_middle);
    ent->addComponent(make_unique<Text>("0.30 + 10", glm::vec2{710, 112}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "CD");
    hud->createButton("CD", glm::vec2{680, 87}, glm::vec2{25, 25}, ztgk::color.GRAY, ztgk::color.GRAY, ztgk::color.GRAY, [](){}, ent, ztgk::game::ui_data.gr_middle);
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{710, 87}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "RNG");
    hud->createButton("RNG", glm::vec2{680, 62}, glm::vec2{25, 25}, ztgk::color.GRAY, ztgk::color.GRAY, ztgk::color.GRAY, [](){}, ent, ztgk::game::ui_data.gr_middle);
    ent->addComponent(make_unique<Text>("4", glm::vec2{710, 62}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "MNSP");
    hud->createButton("MNSP", glm::vec2{680, 37}, glm::vec2{25, 25}, ztgk::color.GRAY, ztgk::color.GRAY, ztgk::color.GRAY, [](){}, ent, ztgk::game::ui_data.gr_middle);
    ent->addComponent(make_unique<Text>("1.00", glm::vec2{710, 37}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    ent = scene.addEntity(emods, "MVSP");
    hud->createButton("MVSP", glm::vec2{680, 12}, glm::vec2{25, 25}, ztgk::color.GRAY, ztgk::color.GRAY, ztgk::color.GRAY, [](){}, ent, ztgk::game::ui_data.gr_middle);
    ent->addComponent(make_unique<Text>("5", glm::vec2{710, 12}, glm::vec2(0.5), ztgk::color.WHITE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_middle));
    ent->getComponent<Text>()->mode = MIDDLE_LEFT;

    auto eweapPortrait = scene.addEntity(emiddle, "Weapon Portrait #1");
    eweapPortrait->addComponent(make_unique<Sprite>(glm::vec2{1050,135}, glm::vec2{100,100}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/item_mop.png"));

    eweapPortrait = scene.addEntity(emiddle, "Weapon Portrait #2");
    eweapPortrait->addComponent(make_unique<Sprite>(glm::vec2{1050,15}, glm::vec2{100,100}, ztgk::color.WHITE, ztgk::game::ui_data.gr_middle, "res/textures/icons/item_superMop.png"));
    //todo weapon stats

    auto eactions = scene.addEntity(egame, "Action Panel");
    eactions->addComponent(make_unique<Sprite>(glm::vec2{1520,0}, glm::vec2{400,400}, ztgk::color.GRAY * 0.75f, ztgk::game::ui_data.gr_actions));
    hud->createButton(
        glm::vec2{1595, 325}, glm::vec2{100, 100}, "res/textures/icons/pick-me.png", "res/textures/transparent.png",
        [eactions](){
            static std::string spr_on = "res/textures/icons/pick-me.png";
            static std::string spr_off = "res/textures/icons/gabka_shy.png";

            ztgk::game::cursor.dragMode = DRAG_UNIT;
            eactions->children[0]->getComponent<Sprite>()->load(spr_on);
            eactions->children[1]->getComponent<Sprite>()->load(spr_off);
        },
        eactions, ztgk::game::ui_data.gr_actions
    );
    hud->createButton(
        glm::vec2{1720, 325}, glm::vec2{100, 100}, "res/textures/icons/gabka_shy.png", "res/textures/transparent.png",
        [eactions](){
            static std::string spr_on = "res/textures/icons/pickAXE.png";
            static std::string spr_off = "res/textures/icons/gabka_shy.png";

            ztgk::game::cursor.dragMode = DRAG_TILE;
            eactions->children[1]->getComponent<Sprite>()->load(spr_on);
            eactions->children[0]->getComponent<Sprite>()->load(spr_off);
        },
        eactions, ztgk::game::ui_data.gr_actions
    );
    hud->createButton(glm::vec2{1845, 325}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", [](){}, eactions, ztgk::game::ui_data.gr_actions);
    hud->createButton(glm::vec2{1595, 200}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", [](){}, eactions, ztgk::game::ui_data.gr_actions);
    hud->createButton(glm::vec2{1720, 200}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", [](){}, eactions, ztgk::game::ui_data.gr_actions);
    hud->createButton(glm::vec2{1845, 200}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", [](){}, eactions, ztgk::game::ui_data.gr_actions);
    hud->createButton(glm::vec2{1595, 75}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", [](){}, eactions, ztgk::game::ui_data.gr_actions);
    hud->createButton(glm::vec2{1720, 75}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", [](){}, eactions, ztgk::game::ui_data.gr_actions);
    hud->createButton(glm::vec2{1845, 75}, glm::vec2{100, 100}, "res/textures/transparent.png", "res/textures/transparent.png", [](){}, eactions, ztgk::game::ui_data.gr_actions);

// settings
    auto esettings = scene.addEntity(ehud, "Settings");
    esettings->addComponent(make_unique<Sprite>(glm::vec2{0,0}, ztgk::game::window_size, ztgk::color.LAVENDER, ztgk::game::ui_data.gr_settings));
    esettings->addComponent(make_unique<Text>("Settings", glm::vec2{ztgk::game::window_size.x/2, ztgk::game::window_size.y - 100}, glm::vec2(1.5), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_settings));
    esettings->getComponent<Text>()->mode = TOP_CENTER;

    auto eslider_master = scene.addEntity(esettings, "Master Volume ");
    eslider_master->addComponent(make_unique<Text>("Master Volume", glm::vec2{(ztgk::game::window_size.x-1000)/2, ztgk::game::window_size.y - 400}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_settings));
    eslider_master->getComponent<Text>()->mode = MIDDLE_RIGHT;
    hud->createSlider_SettingBar(HORIZONTAL, {(ztgk::game::window_size.x-1000)/2, ztgk::game::window_size.y - 400}, {1000, 80}, eslider_master, ztgk::game::ui_data.gr_settings, 128, 0, "{:.0f}/{:.0f}");

    auto eslider_ambient = scene.addEntity(esettings, "Ambient Volume ");
    eslider_ambient->addComponent(make_unique<Text>("Ambient Volume", glm::vec2{(ztgk::game::window_size.x-1000)/2, ztgk::game::window_size.y - 600}, glm::vec2(1), ztgk::color.ROSE, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_settings));
    eslider_ambient->getComponent<Text>()->mode = MIDDLE_RIGHT;
    hud->createSlider_SettingBar(HORIZONTAL, {(ztgk::game::window_size.x-1000)/2, ztgk::game::window_size.y - 600}, {1000, 80}, eslider_ambient, ztgk::game::ui_data.gr_settings, 128, 0, "{:.0f}/{:.0f}");

    hud->createButton("Save", {ztgk::game::window_size.x/2, 100}, {200, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        [eslider_master, eslider_ambient]() {
            ztgk::game::audioManager->setGlobalVolume(eslider_master->getChild("Setting Slider")->getComponent<HUDSlider>()->get_in_display_range());
            ztgk::game::audioManager->setVolumeForGroup("ambient", eslider_ambient->getChild("Setting Slider")->getComponent<HUDSlider>()->get_in_display_range());
        },
        esettings, ztgk::game::ui_data.gr_settings
    );

    hud->createButton("<Back", {200, 125}, {200, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        [hud]() { hud->getGroupOrDefault(ztgk::game::ui_data.gr_settings)->setHidden(true); hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false); },
        esettings, ztgk::game::ui_data.gr_settings
    );

// credits
    auto ecredits = scene.addEntity(ehud, "Credits");
    ecredits->addComponent(make_unique<Sprite>(glm::vec2{0,0}, ztgk::game::window_size, ztgk::color.LAVENDER, ztgk::game::ui_data.gr_credits));

    std::string licenses;
    std::ifstream file("res/sounds/CREDITS.txt");
    std::string line;
    while (std::getline(file, line)) {
        licenses += line + "\n";
    }
    auto eteam = scene.addEntity(ecredits, "Team Credits");
    eteam->addComponent(make_unique<Text>(
        "Bubble Bliss Games\n\nGrzegorz Ludziejewski\nIgor Kusidel\nKrzysztof Czerwinski\nAmelia Kwasniewska\nJan Filipowicz",
        glm::vec2{100, ztgk::game::window_size.y - 100}, glm::vec2(1), glm::vec4{36, 54, 110, 255}/255.0f, ztgk::font.Fam_Nunito + ztgk::font.bold, NONE, ztgk::game::ui_data.gr_credits
    ));
    eteam->getComponent<Text>()->mode = TOP_LEFT;
    eteam->addComponent(make_unique<Sprite>(glm::vec2{100,400}, glm::vec2{400, 225}, ztgk::color.WHITE, ztgk::game::ui_data.gr_credits, "res/textures/credits.jpg"));
    eteam->getComponent<Sprite>()->mode = MIDDLE_LEFT;

    auto elicenses = scene.addEntity(ecredits, "Licenses");
    elicenses->addComponent(make_unique<Text>(
        licenses,
        glm::vec2{ztgk::game::window_size.x - 100, ztgk::game::window_size.y - 100}, glm::vec2(0.5), glm::vec4{36, 54, 110, 255}/255.0f, ztgk::font.Fam_Nunito + ztgk::font.regular, NONE, ztgk::game::ui_data.gr_credits
    ));
    elicenses->getComponent<Text>()->mode = TOP_RIGHT;

    hud->createButton("<Back", {200, 125}, {200, 80}, ztgk::color.ROSE, ztgk::color.ROSE - glm::vec4{0.1, 0.1, 0.1, 0}, ztgk::color.ROSE - glm::vec4{0.2, 0.2, 0.2, 0},
        [hud]() { hud->getGroupOrDefault(ztgk::game::ui_data.gr_credits)->setHidden(true); hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false); },
        ecredits, ztgk::game::ui_data.gr_credits
    );

    // groups
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_menu)->setHidden(false);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_mainMenu)->setHidden(false);

    hud->getGroupOrDefault(ztgk::game::ui_data.gr_game)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_settings)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_middle)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_pause)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_loadScreen)->setHidden(true);
    hud->getGroupOrDefault(ztgk::game::ui_data.gr_credits)->setHidden(true);

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    processInput(window);
}

void update() {
    ZoneScopedN("Update");

    //no need to check every frame, every 5 sec is good enough
    if ((int) glfwGetTime() % 5 == 0 && glfwGetTime() - (int) glfwGetTime() < 0.02) {
        ztgk::game::audioManager->playAmbientMusic();
    }

    //UpdateImpl mouse position
    mouseX = mouseio.MousePos.x;
    mouseY = mouseio.MousePos.y;

    scene.systemManager.Update();
    scene.updateScene();

    scene.systemManager.getSystem<LightSystem>()->Update();
    scene.systemManager.getSystem<InstanceRenderSystem>()->Update();
    scene.systemManager.getSystem<InstanceRenderSystem>()->PushToSSBO(&camera);
    scene.systemManager.getSystem<WireRenderSystem>()->Update();

    scene.systemManager.getSystem<SignalQueue>()->Update();

    scene.systemManager.getSystem<UnitSystem>()->Update();
    scene.systemManager.getSystem<WashingMachine>()->Update();

    update_dragged_tiles();
    for (auto tile: selectedTiles) {
        scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setTileSelectionState(TileSelectionState::POINTED_AT);
    }

    scene.systemManager.getSystem<CollisionSystem>()->Update();
    scene.systemManager.getSystem<RenderSystem>()->Update();
    scene.systemManager.getSystem<MiningSystem>()->Update();

//    for(auto u : scene.systemManager.getSystem<UnitSystem>()->unitComponents) {
//        if(u->isAlly)
//            spdlog::info("Unit: {} -- State: {}", u->name, u->currentState->name);
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

    ImGuiIO &io = ImGui::GetIO();
    mouseio = io;
    // Start the Dear ImGui frame
    if (!captureMouse) {
        io.MouseDrawCursor = true;
    } else {
        io.MouseDrawCursor = false;
    }

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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(UPWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWNWARD, deltaTime);


    if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS) {
        if (!captureMouseButtonPressed) {
            captureMouse = !captureMouse;
        }
        captureMouseButtonPressed = true;
    }

    if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE) {
        captureMouseButtonPressed = false;
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

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        ImGui::GetIO().MousePos = ImVec2(0, 0);
    }

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        ztgk::game::cursor.dragMode = dragSelectionMode::DRAG_UNIT;
        spdlog::info("Drag mode set to DRAG_UNIT");

    } else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        ztgk::game::cursor.dragMode = dragSelectionMode::DRAG_TILE;
        spdlog::info("Drag mode set to DRAG_TILE");
    }

    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !isXpressed){
        ztgk::game::scene->systemManager.getSystem<WashingMachine>()->onPraniumDelivered();
        spdlog::debug("clearing tiles in radius");
        isXpressed = true;
//        radiusToRemove +=1;
    }
    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE){
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
    ztgk::game::cursor.scroll({xoffset, yoffset});
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    ztgk::game::cursor.click(button, action, mods);
//    if (ztgk::game::cursor.config.capture_click)
//        handle_picking(window, button, action, mods);

}

void update_dragged_tiles() {

    glm::vec3 worldPressCoords = camera.getDirFromCameraToCursor(mouseX - 10, mouseY - 10, display_w,
                                                                 display_h);
    std::unique_ptr<Ray> ray = make_unique<Ray>(camera.Position, worldPressCoords, scene.systemManager.getSystem<CollisionSystem>());

    if (isLeftMouseButtonHeld && ray != nullptr && ray->getHitEntity() != nullptr) {
        Vector2Int mouseHeldStartGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldStartPos));
        mouseHeldEndPos = ray->getHitEntity()->transform.getGlobalPosition();
        Vector2Int mouseHeldEndGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldEndPos));
        std::vector<Vector2Int> tilesInArea = VectorUtils::getAllTilesBetween(mouseHeldStartGridPos, mouseHeldEndGridPos);
        if (!selectedTiles.empty()) {
            for (auto tile: selectedTiles) {
                scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setTileSelectionState(NOT_SELECTED);
            }
        }
        selectedTiles = tilesInArea;
//        for(auto tile : tilesInArea){
//            scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setTileSelectionState(POINTED_AT);
//        }

    }

}

void handle_picking(GLFWwindow *window, int button, int action, int mods) {

    //calculate ray every mouse press
    glm::vec3 worldPressCoords = camera.getDirFromCameraToCursor(mouseX - 10, mouseY - 10, display_w,
                                                                 display_h);
    std::unique_ptr<Ray> ray = make_unique<Ray>(camera.Position, worldPressCoords, scene.systemManager.getSystem<CollisionSystem>());
    if (ray->getHitEntity() != nullptr) {
        spdlog::info("Ray hit entity: {}", ray->getHitEntity()->name);
    } else {
        spdlog::info("Ray hit nothing");
    }

    if (isLeftMouseButtonHeld && ray->getHitEntity() != nullptr) {
        spdlog::info("Mouse held");
        Vector2Int mouseHeldStartGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldStartPos));
        mouseHeldEndPos = ray->getHitEntity()->transform.getGlobalPosition();
        Vector2Int mouseHeldEndGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldEndPos));
        std::vector<Vector2Int> tilesInArea = VectorUtils::getAllTilesBetween(mouseHeldStartGridPos, mouseHeldEndGridPos);
        for (auto tile: tilesInArea) {
            scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setTileSelectionState(POINTED_AT);
        }
    }

    //if left mouse button is pressed, start timer and save position of the mouse press
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        mouseHeldStartTime = glfwGetTime();
        isLeftMouseButtonHeld = true;
        if (ray->getHitEntity() != nullptr) {
            mouseHeldStartPos = ray->getHitEntity()->transform.getGlobalPosition();
        }
    }

    //if left mouse button is released, check if it was a click or a drag
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouseHeldReleaseTime = glfwGetTime();
        isLeftMouseButtonHeld = false;

        //if mouse was held for less than 0.2 seconds, consider it a click
        if (mouseHeldReleaseTime - mouseHeldStartTime < 0.2f) {

            // if ray hits an allied unit
            if (ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Unit>() != nullptr &&
                ray->getHitEntity()->getComponent<Unit>()->isAlly) {

                //if it is already selected, deselect it
                if (ray->getHitEntity()->getComponent<Unit>()->isSelected) {
                    scene.systemManager.getSystem<UnitSystem>()->deselectUnit(ray->getHitEntity()->getComponent<Unit>());
                }

                    //if it is not selected, select it
                else {
                    scene.systemManager.getSystem<UnitSystem>()->selectUnit(ray->getHitEntity()->getComponent<Unit>());
                }
            }

                // if ray hits anyting else than a unit, deselect all units
            else if (ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Unit>() == nullptr) {
                scene.systemManager.getSystem<UnitSystem>()->deselectAllUnits();
            }
        }

            //if mouse was held for more than 0.2 seconds, consider it a drag
        else {
            if (ray->getHitEntity() != nullptr) {
                dragSelectionMode dsm = ztgk::game::cursor.dragMode;
                mouseHeldEndPos = ray->getHitEntity()->transform.getGlobalPosition();
                Vector2Int mouseHeldStartGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldStartPos));
                Vector2Int mouseHeldEndGridPos = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(mouseHeldEndPos));

                for (auto tile: selectedTiles) {
                    scene.systemManager.getSystem<Grid>()->getTileAt(tile)->setTileSelectionState(NOT_SELECTED);
                }

                std::vector<Vector2Int> tilesInArea = VectorUtils::getAllTilesBetween(mouseHeldStartGridPos, mouseHeldEndGridPos);
                selectedTiles = tilesInArea;

                if (!scene.systemManager.getSystem<UnitSystem>()->selectedUnits.empty() && dsm == dragSelectionMode::DRAG_TILE) {
                    for (auto unit: scene.systemManager.getSystem<UnitSystem>()->selectedUnits) {
                        unit->miningTargets.clear();
                        for (auto tile: tilesInArea) {
                            auto mineable = scene.systemManager.getSystem<Grid>()->getTileAt(tile)->getEntity()->getComponent<IMineable>();
                            if (mineable != nullptr && !mineable->isMined) {
                                unit->miningTargets.push_back(mineable);
                            }
                        }
                    }

                } else if (dsm == dragSelectionMode::DRAG_UNIT) {
                    scene.systemManager.getSystem<UnitSystem>()->deselectAllUnits();
                    for (auto tile: tilesInArea) {
                        Unit *unitptr = scene.systemManager.getSystem<Grid>()->getTileAt(tile)->unit;
                        if (unitptr != nullptr) {
                            if (unitptr->isAlly && !unitptr->isSelected) {
                                scene.systemManager.getSystem<UnitSystem>()->selectUnit(unitptr);
                            }
                        }
                    }
                }
            } else {
                isLeftMouseButtonHeld = false;
                return;
            }
        }

        scene.systemManager.getSystem<WireRenderSystem>()->rayComponents.push_back(std::move(ray));
    }


    //if there are selected units and right mouse button is pressed, set target for selected units
    if (!scene.systemManager.getSystem<UnitSystem>()->selectedUnits.empty() && button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {

        Entity *hit = ray->getHitEntity();

        //if something was hit
        if (hit != nullptr) {
            for (auto unit: scene.systemManager.getSystem<UnitSystem>()->selectedUnits) {
                IMineable *mineable = hit->getMineableComponent<IMineable>(hit);

                //if hit entity is mineable, set it as mining target
                if (mineable != nullptr && !mineable->isMined) {
                    unit->miningTargets.clear();
                    unit->miningTargets.emplace_back(hit->getMineableComponent<IMineable>(hit));
                    Tile *hitTile = hit->getComponent<Tile>();
                    hitTile->setTileSelectionState(SELECTED);
                    unit->hasMiningTarget = true;
//                    unit->ForcedMiningState = true;
//                    unit->forcedMiningTarget = mineable;
                    spdlog::info("Mining target set at {}, {}", mineable->gridPosition.x, mineable->gridPosition.z);
                }

                    //if hit entity is a tile, stop doing anything and set movement target
                else if (hit->getComponent<Tile>() != nullptr) {
                    unit->ForcedMovementState = true;
                    unit->forcedMovementTarget = hit->getComponent<Tile>()->index;

                    unit->hasMiningTarget = false;
                    unit->miningTargets.clear();
                    unit->hasCombatTarget = false;
                    unit->combatTarget = nullptr;
                    unit->hasMovementTarget = true;
                    unit->pathfinding.path.clear();
                    unit->hasPickupTarget = false;
                    unit->pickupTarget = nullptr;
                    unit->movementTarget = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(hit->transform.getGlobalPosition()));
                }

                    //if hit an item model, set it as the pickup & movement target
                else if (hit->getComponent<PickupubleItem>() != nullptr) {
                    unit->ForcedMovementState = true;

                    unit->hasMiningTarget = false;
                    unit->miningTargets.clear();
                    unit->hasCombatTarget = false;
                    unit->combatTarget = nullptr;
                    unit->hasMovementTarget = true;
                    unit->pathfinding.path.clear();
                    unit->movementTarget = scene.systemManager.getSystem<Grid>()->WorldToGridPosition(VectorUtils::GlmVec3ToVector3(hit->transform.getGlobalPosition()));
                    unit->hasPickupTarget = true;
                    unit->pickupTarget = hit->getComponent<PickupubleItem>();
                }
            }
        }
        scene.systemManager.getSystem<WireRenderSystem>()->rayComponents.push_back(std::move(ray));
    }

    if (!scene.systemManager.getSystem<UnitSystem>()->selectedUnits.empty()) {
        scene.systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_middle)->setHidden(false);
        auto unit = scene.systemManager.getSystem<UnitSystem>()->selectedUnits[0];
        auto emods = scene.getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Mods");
        emods->getChild("ATK")->getComponent<Text>()->content = std::format("{} + {}", unit->stats.added.dmg_perc, unit->stats.added.dmg_flat);
        emods->getChild("DEF")->getComponent<Text>()->content = std::format("{} + {}", unit->stats.added.def_perc, unit->stats.added.def_flat);
        emods->getChild("CD")->getComponent<Text>()->content = std::format("{}", unit->stats.added.atk_speed);
        emods->getChild("RNG")->getComponent<Text>()->content = std::format("{}", unit->stats.added.rng_add);
        emods->getChild("MNSP")->getComponent<Text>()->content = std::format("{}", unit->stats.mine_spd + unit->stats.added.mine_speed);
        emods->getChild("MVSP")->getComponent<Text>()->content = std::format("{}", unit->stats.move_spd + unit->stats.added.move_speed);

        scene.getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Display Bar")->getComponent<HUDSlider>()->displayMax = unit->stats.max_hp + unit->stats.added.max_hp;
        scene.getChild("HUD")->getChild("Game")->getChild("Unit Details")->getChild("Display Bar")->getComponent<HUDSlider>()->set_in_display_range(unit->stats.hp);

        ztgk::game::ui_data.tracked_unit_id = unit->uniqueID;
        //hud/game/unit details/mods/mod
    } else {
        scene.systemManager.getSystem<HUD>()->getGroupOrDefault(ztgk::game::ui_data.gr_middle)->setHidden(true);
    }

}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    *ztgk::game::signalQueue += KeySignalData::signal(key, scancode, action, mods, "Forwarding GLFW event.");
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
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
            .baseRadius = RNG::RandomFloat(6.f, 10.f),
            .keyRadius = RNG::RandomFloat(3.f, 5.f),
            .pocketRadius = RNG::RandomFloat(6.f, 10.f),
            .noiseImpact = RNG::RandomFloat(0.1f, 0.3f),
            .keyDistances {20.f, 20.f, 30.f, 30.f, 40.f},
            .extraPocketAttempts = 10000,
            .keyEnemies = RNG::RandomInt(2, 3),
            .minEnemies = 5,  //0        <--- if those values are different from those in comments, I forgot to change them after debugging
            .maxEnemies = 5,  //4        <---
            .unitCount = 1,   //3        <---
            .chestCount = RNG::RandomInt(8, 15),
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
