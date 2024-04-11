
#pragma region Includes
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <ImGuizmo.h>
#include <cstdio>

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
#include "Utils/Util.h"
#include "ECS/Render/Components/Render.h"
#include "ECS/Scene.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD //THIS HAS TO BE RIGHT BEFORE THE PIPELINE
#define STB_IMAGE_IMPLEMENTATION

#include "ECS/Render/Pipelines/PBRPipeline.h"
#include "ECS/Render/Postprocessing/BloomPostProcess.h"
#include "ECS/Render/ModelLoading/Model.h"
#include "ECS/Entity.h"

#include "ECS/Grid/Grid.h"

#include "ECS/Render/Primitives/PBRPrimitives.h"
#include "ECS/Render/Primitives/Primitives.h"

#include "Utils/Time.h"

#include "ECS/HUD/TextRenderer.h"
#include "ECS/HUD/SpriteRenderer.h"

#include "Utils/ImGuiSpdlogSink.h"
#include "ECS/HUD/HUD.h"
#include "ECS/Render/FrustumCulling/Frustum.h"
#include "Raycasting/Colliders/BoxCollider.h"
#include "Raycasting/Ray.h"


#pragma endregion Includes

#pragma region constants

Scene scene;
string modelPath = "res/models/asteroid/Asteroid.fbx";
string tileModelPath = "res/models/Tile/Tile.fbx";
Model tileModel = Model(&tileModelPath);
Model model = Model(&modelPath);
Model* cubeModel;
Model* quadModel;
Entity *gridEntity;
HUD hud;
unsigned bggroup, zmgroup;
Sprite * zmspr;
Text * zmtxt;

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

void init_imgui();

void init_camera();

void init_time();

void before_frame();

void input();

void update();

void render();

void imgui_begin();

void imgui_render();

void imgui_end();

void end_frame();

void cleanup();

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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
PBRPrimitives PBRPrimitives;
LightSystem lightSystem(&camera,&scene);
PBRPipeline pbrSystem(&camera,&primitives);
RenderSystem renderSystem;
BloomPostProcess bloomSystem;


bool captureMouse = false;
bool captureMouseButtonPressed = false;

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

    init_systems();
    spdlog::info("Initialized textures and vertices.");

    init_imgui();
    spdlog::info("Initialized ImGui.");

    init_camera();
    spdlog::info("Initialized camera and viewport.");

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDepthFunc(GL_LEQUAL);

    signalQueue.init();
    spdlog::info("Initialized signal queue.");

    init_time();
    spdlog::info("Initialized system timer.");

    load_enteties();
    spdlog::info("Initialized entities.");

#pragma endregion Init

//____________________________________________________________________________________________________
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        //Setting up things for the rest of functionalities (ex. update_delta time)
        before_frame();

        // Process I/O operations here
        input();

        // Update game objects' state here
        update();

        // OpenGL rendering code here
        render();
  /*
        Ray r = Ray(camera.Position, camera.Front, &scene);
        std::cout<< "Raycast: " << r.RayHitPoint().x << " " << r.RayHitPoint().y << " " << r.RayHitPoint().z << std::endl;
        */

        // Draw ImGui
        imgui_begin();
        imgui_render(); // edit this function to add your own ImGui controls
        imgui_end(); // this call effectively renders ImGui

        //_______________________________NA POTRZEBY ZADANIA NA KARTY GRAFICZNE_______________________________
        static bool bgup = true;
        auto group = hud.getGroupOrDefault(bggroup);
        if (group->offset.y == ztgk::game::window_size.y) {
            bgup = false;
        } else if (group->offset.y == 0) {
            bgup = true;
        }
        if (bgup) {
            group->offset.y++;
        } else {
            group->offset.y--;
        }
        zmtxt->content = std::format("Ten tekst jest zmienny! {}", Time::Instance().LastFrame());
        auto s = sin(Time::Instance().LastFrame());
        auto c = cos(Time::Instance().LastFrame());
        static auto ogsprsize = zmspr->size;
        zmspr->size = ogsprsize * glm::vec2(c,s);
        zmtxt->color = { s, c, s + c / 2, 1.0f };
        zmspr->color = { s, c, s + c / 2, 1.0f };
        //____________________________________________________________________________________________________

        // End frame and swap buffers (double buffering)
        file_logger->info("End frame");
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
    auto sink = make_shared<ImGuiSpdlogSink>();
    sink->set_pattern("[%H:%M:%S.%e] [%l] %v"); // remove the full date (and logger name since it's null anyway)
    spdlog::get("")->sinks().push_back(sink);

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

    scene.systemManager.addSystem(&lightSystem);
    scene.systemManager.addSystem(&renderSystem);
    scene.systemManager.addSystem(&signalQueue);
    primitives.Init();
    PBRPrimitives.Init();
    pbrSystem.Init();
    bloomSystem.Init(camera.saved_display_w, camera.saved_display_h);

    Color myColor = {255, 32, 21, 0};  // This defines your color.

    Material whiteMaterial = Material(myColor);
    cubeModel = new Model(PBRPrimitives.cubeVAO, whiteMaterial,vector<GLuint>(PBRPrimitives.cubeIndices,PBRPrimitives.cubeIndices + 36));
    quadModel = new Model(PBRPrimitives.quadVAO,whiteMaterial,vector<GLuint>(PBRPrimitives.quadIndices,PBRPrimitives.quadIndices + 6));

    hud.init();
    scene.systemManager.addSystem(&hud);
}

void load_enteties() {
    model.loadModel();
    tileModel.loadModel();
    Entity *gameObject = scene.addEntity("asteroid");
    gameObject->transform.setLocalPosition({-0, 0, 0});
    const float scale = 10;
    gameObject->transform.setLocalScale({scale, scale, scale});
    gameObject->addComponent(make_unique<Render>(cubeModel));
    gameObject->addComponent(std::make_unique<BoxCollider>(gameObject, glm::vec3{1.0f, 1.0f, 1.0f}));
    for (unsigned int i = 0; i < 2; ++i) {gameObject = scene.addEntity(gameObject, "asteroid");
        gameObject->addComponent(make_unique<Render>(&model));
        gameObject->transform.setLocalScale({scale, scale, scale});
        gameObject->transform.setLocalPosition({5, 0, 0});
        gameObject->transform.setLocalScale({0.2f, 0.2f, 0.2f});
        gameObject->addComponent(std::make_unique<BoxCollider>(gameObject, glm::vec3{1.0f + i + 1, 1.0f, 1.0f}));
    }
    //gameObject = scene.addEntity("Dir light");
    //gameObject->addComponent(new DirLight(DirLightData(glm::vec4(glm::vec3(255),1), glm::vec4(1))));
   // gameObject = scene.addEntity("Point Light");
  //  gameObject->addComponent(new PointLight(PointLightData(glm::vec4(glm::vec3(255),1),glm::vec4(0), 1.0f, 1.0f, 1.0f)));
    gameObject = scene.addEntity("Spot Light");
    gameObject->addComponent(make_unique<SpotLight>(SpotLightData(glm::vec4(glm::vec3(255),1), glm::vec4(0), glm::vec4(1),glm::cos(glm::radians(12.5f)),glm::cos(glm::radians(15.0f)),1.0f,0.09f,0.032f)));
    lightSystem.Init();

    /*
    gridEntity = scene.addEntity("Grid");
    // size modelu = 5.0 przy skali 0.01; true size -> 500
    Grid * grid = new Grid(100, 100, 5.0f, gridEntity);
    gridEntity->addComponent(grid);
    // 0.10 to faktyczna wielkość, 0.11 jest żeby nie prześwitywały luki, jak będzie rozpierdalać select to można zmienić

    grid->RenderTiles(&scene, 0.011f, &tileModel);
     */

    auto ehud = scene.addEntity("HUD DEMO");
    auto ebg = scene.addEntity(ehud, "Background");
    bggroup = hud.addGroup(glm::vec3(0, 0, 10));
    auto bgelem = scene.addEntity(ebg, "Puni1");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(10, 0), glm::vec2(100, 100), ztgk::color.WHITE, bggroup, "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni2");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(100, 0), glm::vec2(100, 100), ztgk::color.WHITE, bggroup, "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni3");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(250, 0), glm::vec2(20, 100), ztgk::color.WHITE, bggroup, "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni4");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(600, 0), glm::vec2(500, 100), ztgk::color.WHITE, bggroup, "res/textures/puni.png"));
    bgelem = scene.addEntity(ebg, "Puni5");
    bgelem->addComponent(make_unique<Sprite>(glm::vec2(1500, 0), glm::vec2(100, 500), ztgk::color.WHITE, bggroup, "res/textures/puni.png"));

    auto efg = scene.addEntity(ehud, "Foreground");
    auto fgelem = scene.addEntity(efg, "Fixed");
    fgelem->addComponent(make_unique<Text>("Ten tekst jest staly!", ztgk::game::window_size / 5));
    zmgroup = hud.addGroup();
    fgelem = scene.addEntity(efg, "Variable Text");
    auto tx = Text("Ten tekst jest zmienny!", glm::vec2(ztgk::game::window_size.x * 0.5 - 300, ztgk::game::window_size.y * 0.5 ));
    tx.groupID = zmgroup;
    fgelem->addComponent(make_unique<Text>( tx ));
    zmtxt = fgelem->getComponent<Text>();
    fgelem = scene.addEntity(efg, "Animated Sprite");
    auto spr = Sprite("res/textures/puni.png");
    spr.groupID = zmgroup;
    fgelem->addComponent(make_unique<Sprite>( spr ));
    zmspr = fgelem->getComponent<Sprite>();
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
    Time::Instance().Update();
    deltaTime = Time::Instance().DeltaTime();
}


void input() {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    processInput(window);
}

void update() {
    scene.updateScene();
    lightSystem.Update(deltaTime);
    signalQueue.update();
}

void render() {

    lightSystem.PushDepthMapsToShader(&pbrSystem.pbrShader);
    lightSystem.PushDepthMapsToShader(&pbrSystem.pbrInstanceShader);

    glViewport(0, 0, camera.saved_display_w, camera.saved_display_h); // Needed after light generation

    bloomSystem.BindBuffer();
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    file_logger->info("Cleared.");

    pbrSystem.PrebindPBR(&camera);
    pbrSystem.RenderBackground();
    file_logger->info("Set up PBR.");

    pbrSystem.pbrShader.use();

    renderSystem.DrawScene(&pbrSystem.pbrShader);

    file_logger->info("Rendered AsteroidsSystem.");

    bloomSystem.BlurBuffer();
    bloomSystem.Render();

    hud.draw();
}





void imgui_begin() {
    ImGuiIO &io = ImGui::GetIO();
    
    // Start the Dear ImGui frame
    if (!captureMouse) {
        io.MouseDrawCursor = true;
    } else {
        io.MouseDrawCursor = false;
    };

    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
  
    
}

void imgui_render() {


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
    ImGui::Text("%s", std::format("High @ {:.3f}", max_timestamp).c_str());
    ImGui::Text("%s", std::format("Low @ {:.3f}", min_timestamp).c_str());
    if (ImGui::Button("Clear")) {
        fps_max = -1;
        max_timestamp = 0;
        fps_min = 1000000;
        min_timestamp = 0;
    }

    //lightSystem.showLightTree();
    ImGui::End();
    scene.showImGuiDetails(&camera);

    ztgk::console.imguiWindow();

   // bloomSystem .showImguiOptions();
}

void imgui_end() {
    ImGui::Render();
  
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
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
        ImGui::GetIO().MousePos = ImVec2(0,0);
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

    static float uixpos{ 1920/2 };
    static float uiypos{ 1080/2 };

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
    signalQueue += MouseScrollSignalData::signal({xoffset, yoffset}, "Forwarding GLFW event.");

    camera.ProcessMouseScroll(static_cast<float>(yoffset), deltaTime);
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    signalQueue += MouseButtonSignalData::signal(button, action, mods, "Forwarding GLFW event.");
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    signalQueue += KeySignalData::signal(key, scancode, action, mods, "Forwarding GLFW event.");
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void end_frame() {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
    glfwSwapBuffers(window);
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
