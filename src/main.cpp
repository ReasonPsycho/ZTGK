
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
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseScrollSignalData.h"
#include "ECS/SignalQueue/DataCargo/MouseEvents/MouseButtonSignalData.h"
#include "ECS/SignalQueue/DataCargo/KeySignalData.h"

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
#include "ECS/Render/FrustumCulling/Frustum.h"
#include "ECS/Raycasting/Colliders/BoxCollider.h"
#include "ECS/Raycasting/Ray.h"
#include "ECS/Render/WireRenderer.h"
#include "ECS/Raycasting/CollisionSystem.h"
#include "ECS/Render/InstanceRenderSystem.h"
#include "ECS/Unit/UnitAI/UnitAI.h"
#include "ECS/Unit/UnitAI/StateMachine/States/IdleState.h"
#include "ECS/Unit/UnitSystem.h"
#include "ECS/SaveSystem/LevelSaving.h"
#include "ECS/LevelGenerator/LevelGenerator.h"

#pragma endregion Includes

#pragma region constants

Scene scene;
string modelPath = "res/models/asteroid/Asteroid.fbx";
string modelPathGabka = "res/models/gabka/pan_gabka_lower_poly.fbx";
string modelPathWall = "res/models/BathroomWall/BathroomWall.fbx";
string tileModelPath = "res/models/plane/Plane.fbx";
Model tileModel = Model(&tileModelPath);
Model model = Model(&modelPath);
Model *quad;
Model gabka = Model(&modelPathGabka);
Model wall = Model(&modelPathWall);
Model *cubeModel;
Model *bathroomWAll;
Model *quadModel;
Entity *gridEntity;
HUD hud;
unsigned bggroup, zmgroup;
Sprite *zmspr;
Text *zmtxt;
StateManager* stateManager;

Entity *box1;
Entity *box2;
Text text = {};

BoxCollider *boxCollider;


shared_ptr<spdlog::logger> file_logger;
#pragma endregion constants

#pragma region Function definitions

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool init();

void init_systems();

void load_enteties();

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

void processInput(GLFWwindow *window);

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
float lastX = 0;
float lastY = 0;

Primitives primitives;
PBRPrimitives pbrprimitives;
LightSystem lightSystem(&camera, &scene);
PhongPipeline phongPipeline;
RenderSystem renderSystem;
InstanceRenderSystem instanceRenderSystem(&camera);
WireRenderer wireRenderer(&primitives, &camera);
BloomPostProcess bloomSystem;
CollisionSystem collisionSystem;
UnitSystem unitSystem;

Grid grid(&scene, 100, 100, 2.0f, Vector3(0, 0, 0));

Entity *playerUnit;

bool captureMouse = false;
bool captureMouseButtonPressed = false;

ImGuiIO mouseio;
double mouseX;
double mouseY;

// timing
double deltaTime = Time::Instance().DeltaTime();
int timeStep = 1;
bool timeStepKeyPressed = false;

#pragma endregion My set up

#pragma region ZTGK-Global

SignalQueue signalQueue = SignalQueue();

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

    init_camera();
    spdlog::info("Initialized camera and viewport.");

    init_systems();
    spdlog::info("Initialized textures and vertices.");

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDepthFunc(GL_LEQUAL);
    glfwSwapInterval(1); 

    signalQueue.init();
    spdlog::info("Initialized signal queue.");

    init_time();
    spdlog::info("Initialized system timer.");

    load_enteties();
    spdlog::info("Initialized entities.");

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


        //_______________________________NA POTRZEBY ZADANIA NA KARTY GRAFICZNE_______________________________
//        static bool bgup = true;
//        auto group = hud.getGroupOrDefault(bggroup);
//        if (group->offset.y == ztgk::config::window_size.y) {
//            bgup = false;
//        } else if (group->offset.y == 0) {
//            bgup = true;
//        }
//        if (bgup) {
//            group->offset.y++;
//        } else {
//            group->offset.y--;
//        }
//        zmtxt->content = std::format("Ten tekst jest zmienny! {}", Time::Instance().LastFrame());
//        auto s = sin(Time::Instance().LastFrame());
//        auto c = cos(Time::Instance().LastFrame());
//        static auto ogsprsize = zmspr->size;
//        zmspr->size = ogsprsize * glm::vec2(c,s);
//        zmtxt->color = { s, c, s + c / 2, 1.0f };
//        zmspr->color = { s, c, s + c / 2, 1.0f };
        //____________________________________________________________________________________________________


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

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool init() {
    spdlog::set_level(spdlog::level::trace);
//    spdlog::get("")->sinks()[0]->set_level(spdlog::level::debug);
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
    ztgk::game::signalQueue = &signalQueue;
    ztgk::game::cursor.init();

    scene.systemManager.addSystem(&lightSystem);
    scene.systemManager.addSystem(&renderSystem);
    scene.systemManager.addSystem(&instanceRenderSystem);
    scene.systemManager.addSystem(&signalQueue);
    scene.systemManager.addSystem(&wireRenderer);
    scene.systemManager.addSystem(&grid);
    scene.systemManager.addSystem(&collisionSystem);
    scene.systemManager.addSystem(&unitSystem);


    primitives.Init();
    phongPipeline.Init();
    bloomSystem.Init(camera.saved_display_w, camera.saved_display_h);
    Color myColor = {255, 32, 21, 0};  // This defines your color.
    pbrprimitives.Init();
    MaterialPhong materialPhong = MaterialPhong(myColor);
    cubeModel = new Model(pbrprimitives.cubeVAO, materialPhong,
                          vector<GLuint>(pbrprimitives.cubeIndices, pbrprimitives.cubeIndices + 36));
    ztgk::game::cube_model = cubeModel;
    wireRenderer.boxModel = cubeModel;
    wireRenderer.Innit();

    hud.init();
    scene.systemManager.addSystem(&hud);
}

void load_enteties() {
    Color color = {255, 255, 255, 255}; // this is equivalent to white color

    int n = sizeof(pbrprimitives.quadIndices) / sizeof(pbrprimitives.quadIndices[0]);

    // Convert the array to a vector
    std::vector<unsigned int> vec(pbrprimitives.quadIndices, pbrprimitives.quadIndices + n);

    model.loadModel();
    wall.loadModel();
    
    quadModel = new Model(pbrprimitives.quadVAO, MaterialPhong(color), vec);
    //gabka.loadModel();
    tileModel.loadModel();
    Entity *gameObject;


    gameObject = scene.addEntity("Wall");;
    gameObject->transform.setLocalPosition(glm::vec3(100,50,0));
    gameObject->transform.setLocalScale(glm::vec3(100,50,10));
    gameObject->transform.setLocalRotation(glm::quat (glm::vec3(0,0,0)));
    gameObject->addComponent(make_unique<Render>(&wall));;

    gameObject = scene.addEntity("Wall1");;
    gameObject->transform.setLocalPosition(glm::vec3(100,50,200));
    gameObject->transform.setLocalScale(glm::vec3(100,50,10));
    gameObject->transform.setLocalRotation(glm::quat (glm::vec3(0,0,0)));
    gameObject->addComponent(make_unique<Render>(&wall));;
//
    gameObject = scene.addEntity("Wall2");;
    gameObject->transform.setLocalPosition(glm::vec3(0,50,100));
    gameObject->transform.setLocalScale(glm::vec3(100,50,10));
    gameObject->transform.setLocalRotation((glm::quat(glm::radians(glm::vec3(0, 90, 0)))));
    gameObject->addComponent(make_unique<Render>(&wall));;
//
    gameObject = scene.addEntity("Wall3");;
    gameObject->transform.setLocalPosition(glm::vec3(200,50,100));
    gameObject->transform.setLocalScale(glm::vec3(100,50,10));
    gameObject->transform.setLocalRotation((glm::quat(glm::radians(glm::vec3(0, 90, 0)))));
    gameObject->addComponent(make_unique<Render>(&wall));;
    
    
//    gameObject = scene.addEntity("Dir light");
  //  gameObject->addComponent(make_unique<DirLight>(DirLightData(glm::vec4(glm::vec3(255), 1),glm::vec4(glm::vec3(255), 1), glm::vec4(1))));
    gameObject = scene.addEntity("Point Light");;
    gameObject->addComponent(make_unique<PointLight>(
            PointLightData(glm::vec4(glm::vec3(5), 1), glm::vec4(glm::vec3(5), 1), glm::vec4(1, 1, 1, 1), 1.0f, 2,
                           0.032f)));
    //  gameObject = scene.addEntity("Point Light 2");
    // gameObject->addComponent(make_unique<PointLight>(PointLightData(glm::vec4(glm::vec3(255),1),glm::vec4(glm::vec3(0),1),glm::vec4(0), 1.0f, 1.0f, 1.0f)));
    gameObject = scene.addEntity("Spot Light");
    gameObject->addComponent(make_unique<SpotLight>(
            SpotLightData(glm::vec4(glm::vec3(5), 1), glm::vec4(glm::vec3(5), 1), glm::vec4(0), glm::vec4(1),
                          glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), 1.0f, 0.09f, 0.032f)));
    lightSystem.Init();

    //gameObject = scene.addEntity("Quad");
   // gameObject->addComponent(make_unique<Render>(quadModel));


    instanceRenderSystem.tileModel = quadModel;
    grid.LoadTileEntities(1.0f, &collisionSystem);
    instanceRenderSystem.Innit();

    hud.getDefaultGroup()->setHidden(true);
    auto ehud = scene.addEntity("HUD DEMO");
    auto ebg = scene.addEntity(ehud, "Background");
    bggroup = hud.addGroup(glm::vec3(0, 0, 10));
    hud.getGroupOrDefault(bggroup)->setHidden(true);
    auto bgelem = scene.addEntity(ebg, "Puni1");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(10, 0), glm::vec2(100, 100), ztgk::color.WHITE, bggroup,
                                             "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni2");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(100, 0), glm::vec2(100, 100), ztgk::color.WHITE, bggroup,
                                             "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni3");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(250, 0), glm::vec2(20, 100), ztgk::color.WHITE, bggroup,
                                             "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni4");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(600, 0), glm::vec2(500, 100), ztgk::color.WHITE, bggroup,
                                             "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni5");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(1500, 0), glm::vec2(100, 500), ztgk::color.WHITE, bggroup,
                                             "res/textures/puni.png"));

    auto efg = scene.addEntity(ehud, "Foreground");
    auto fgelem = scene.addEntity(efg, "Fixed");
    fgelem->addComponent(make_unique<Text>("Ten tekst jest staly!", ztgk::game::window_size / 5));
    zmgroup = hud.addGroup();
    hud.getGroupOrDefault(zmgroup)->setHidden(true);
    fgelem = scene.addEntity(efg, "Variable Text");
    auto tx = Text("Ten tekst jest zmienny!", glm::vec2(ztgk::game::window_size.x * 0.5 - 300,
                                                                                ztgk::game::window_size.y * 0.5));
    tx.groupID = zmgroup;
    fgelem->addComponent(make_unique<Text>( tx ));
    zmtxt = fgelem->getComponent<Text>();
    fgelem = scene.addEntity(efg, "Animated Sprite");
    auto spr = Sprite("res/textures/puni.png");
    spr.groupID = zmgroup;
    fgelem->addComponent(make_unique<Sprite>( spr ));
    zmspr = fgelem->getComponent<Sprite>();
    zmspr->groupID = zmgroup;

    load_units();



}

void load_units() {
    playerUnit = scene.addEntity("Player1");
    playerUnit->addComponent(make_unique<Render>(cubeModel));
    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
    playerUnit->updateSelfAndChild();
    playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(2, 2, 2), &collisionSystem));
    playerUnit->getComponent<BoxCollider>()->center = playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
    UnitStats stats = {100, 1, 1, 20, 3};
    playerUnit->addComponent(make_unique<Unit>("Player1", &grid, Vector2Int(50, 50), stats, true, &unitSystem));
    stateManager = new StateManager(playerUnit->getComponent<Unit>());
    stateManager->currentState = new IdleState(&grid);
    stateManager->currentState->unit = playerUnit->getComponent<Unit>();
    playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));

//    Entity* enemyUnit = scene.addEntity("Enemy1");
//    enemyUnit->addComponent(make_unique<Render>(cubeModel));
//    enemyUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
//    enemyUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
//    enemyUnit->updateSelfAndChild();
//    enemyUnit->addComponent(make_unique<BoxCollider>(enemyUnit, glm::vec3(2, 2, 2), &collisionSystem));
//    enemyUnit->getComponent<BoxCollider>()->center = enemyUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
//    stats = {100, 1, 1, 20, 3};
//    enemyUnit->addComponent(make_unique<Unit>("Enemy1", &grid, Vector2Int(50, 70), stats, false, &unitSystem));
//    stateManager = new StateManager(enemyUnit->getComponent<Unit>());
//    stateManager->currentState = new IdleState(&grid);
//    stateManager->currentState->unit = enemyUnit->getComponent<Unit>();
//    enemyUnit->addComponent(make_unique<UnitAI>(enemyUnit->getComponent<Unit>(), stateManager));



//    playerUnit = scene.addEntity("Player2");
//    playerUnit->addComponent(make_unique<Render>(cube_model));
//    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
//    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
//    playerUnit->updateSelfAndChild();
//    playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(2, 2, 2), &collisionSystem));
//    playerUnit->getComponent<BoxCollider>()->center = playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
//    stats = {100, 1, 1, 30, 1};
//    playerUnit->addComponent(make_unique<Unit>("Player2", &grid, Vector2Int(60, 60), stats, true, &unitSystem));
//    stateManager = new StateManager(playerUnit->getComponent<Unit>());
//    stateManager->currentState = new idleState();
//    stateManager->currentState->unit = playerUnit->getComponent<Unit>();
//    playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));
//
//    playerUnit = scene.addEntity("Player3");
//    playerUnit->addComponent(make_unique<Render>(cube_model));
//    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
//    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
//    playerUnit->updateSelfAndChild();
//    playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(2, 2, 2), &collisionSystem));
//    playerUnit->getComponent<BoxCollider>()->center = playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
//    stats = {100, 1, 1, 10, 1};
//    playerUnit->addComponent(make_unique<Unit>("Player3", &grid, Vector2Int(70, 60), stats, true, &unitSystem));
//    stateManager = new StateManager(playerUnit->getComponent<Unit>());
//    stateManager->currentState = new idleState();
//    stateManager->currentState->unit = playerUnit->getComponent<Unit>();
//    playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));
//
//    playerUnit = scene.addEntity("Player4");
//    playerUnit->addComponent(make_unique<Render>(cube_model));
//    playerUnit->transform.setLocalScale(glm::vec3(1, 1, 1));
//    playerUnit->transform.setLocalRotation(glm::vec3(0, 0, 0));
//    playerUnit->updateSelfAndChild();
//    playerUnit->addComponent(make_unique<BoxCollider>(playerUnit, glm::vec3(2, 2, 2), &collisionSystem));
//    playerUnit->getComponent<BoxCollider>()->center = playerUnit->transform.getGlobalPosition() + glm::vec3(0, 0, 0.5);
//    stats = {100, 1, 1, 100, 1};
//    playerUnit->addComponent(make_unique<Unit>("Player4", &grid, Vector2Int(60, 70), stats, true, &unitSystem));
//    stateManager = new StateManager(playerUnit->getComponent<Unit>());
//    stateManager->currentState = new idleState();
//    stateManager->currentState->unit = playerUnit->getComponent<Unit>();
//    playerUnit->addComponent(make_unique<UnitAI>(playerUnit->getComponent<Unit>(), stateManager));

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

    //UpdateImpl mouse position
    mouseX = mouseio.MousePos.x;
    mouseY = mouseio.MousePos.y;

    scene.updateScene();
    lightSystem.Update();
    instanceRenderSystem.Update();
    wireRenderer.Update();

    signalQueue.Update();

    unitSystem.Update();
}

void render() {
    ZoneScopedN("Render");

    lightSystem.PushDepthMapsToShader(&phongPipeline.phongShader);
    lightSystem.PushDepthMapsToShader(&phongPipeline.phongInstanceShader);

    glViewport(0, 0, camera.saved_display_w, camera.saved_display_h); // Needed after light generation

    bloomSystem.BindBuffer();
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    file_logger->info("Cleared.");


    file_logger->info("Set up PBR.");
    phongPipeline.PrebindPipeline(&camera);

    renderSystem.DrawScene(&phongPipeline.phongShader, &camera);
    instanceRenderSystem.DrawTiles(&phongPipeline.phongInstanceShader,&camera);
    wireRenderer.DrawColliders();
    wireRenderer.DrawRays();
    file_logger->info("Rendered AsteroidsSystem.");

    bloomSystem.BlurBuffer();
    bloomSystem.Render();

    hud.draw();
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

    static LevelGenerator::Config levelGenConfig {
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

    //lightSystem.showLightTree();
    ztgk::console.imguiWindow();
    // bloomSystem .showImguiOptions();
}

void imgui_end() {
    ZoneScopedN("Imgui end");

    ImGui::End();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO &io = ImGui::GetIO();
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    display_h = height;
    display_w = width;
    camera.UpdateCamera(width, height);
    bloomSystem.SetUpBuffers(width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    signalQueue += MouseMoveSignalData::signal(
            {xposIn, yposIn}, {lastX, lastY},
            "Forwarding GLFW event."
    );

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    static float uixpos{1920 / 2};
    static float uiypos{1080 / 2};

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (captureMouse) {
        if (timeStep != 0) {
            camera.ProcessMouseMovement(xoffset, yoffset, true, deltaTime);
        } else {
            camera.ProcessMouseMovement(xoffset, yoffset, true, 0.01f);
        }
    } else {
        uixpos += xoffset;
        uiypos -= yoffset;
        ImGuiIO &io = ImGui::GetIO();
        io.MousePos = ImVec2(uixpos, uiypos);
    }

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    ztgk::game::cursor.scroll({xoffset, yoffset});

//    signalQueue += MouseScrollSignalData::signal({xoffset, yoffset}, "Forwarding GLFW event.");
//
//    camera.ProcessMouseScroll(static_cast<float>(yoffset), deltaTime);
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    signalQueue += MouseButtonSignalData::signal(button, action, mods, "Forwarding GLFW event.");
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glm::vec3 worldPressCoords = camera.getDirFromCameraToCursor(mouseX - 10, mouseY - 10, display_w, display_h);

        std::unique_ptr<Ray> ray = make_unique<Ray>(camera.Position, worldPressCoords, &collisionSystem);
        if (ray->getHitEntity() != nullptr&& ray->getHitEntity()->getComponent<Unit>() != nullptr && ray->getHitEntity()->getComponent<Unit>()->isAlly){
            if(ray->getHitEntity()->getComponent<Unit>()->isSelected){
                unitSystem.deselectUnit(ray->getHitEntity()->getComponent<Unit>() );
            } else {
                unitSystem.selectUnit(ray->getHitEntity()->getComponent<Unit>());
        } }else if(ray->getHitEntity() != nullptr && ray->getHitEntity()->getComponent<Unit>() == nullptr){
            unitSystem.deselectAllUnits();
        }

        wireRenderer.rayComponents.push_back(std::move(ray));
    }
    if(!unitSystem.selectedUnits.empty() && button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        glm::vec3 worldPressCoords = camera.getDirFromCameraToCursor(mouseX - 10, mouseY - 10, display_w, display_h);
        std::unique_ptr<Ray> ray = make_unique<Ray>(camera.Position, worldPressCoords, &collisionSystem);
        Entity * hit = ray->getHitEntity();
        if(hit != nullptr){
            for(auto unit : unitSystem.selectedUnits){
                if(hit->getComponent<IMineable>()!=nullptr){
                    unit->miningTarget = hit->getComponent<IMineable>();
                    unit->hasMiningTarget = true;
                    spdlog::info("Mining target set at {}, {}", hit->getComponent<IMineable>()->gridPosition.x, hit->getComponent<IMineable>()->gridPosition.z);
                }
                else{
                    unit->hasMiningTarget = false;
                    unit->miningTarget = nullptr;
                    unit->hasCombatTarget = false;
                    unit->combatTarget = nullptr;
                    unit->hasMovementTarget = true;
                    unit->pathfinding.path.clear();
                    unit->movementTarget = grid.WorldToGridPosition( VectorUtils::GlmVec3ToVector3(hit->transform.getGlobalPosition()));
                }
            }
        }
        wireRenderer.rayComponents.push_back(std::move(ray));
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    signalQueue += KeySignalData::signal(key, scancode, action, mods, "Forwarding GLFW event.");
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


#pragma endregion Functions
