
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

#include "ECS/Render/Text.h"

#include "Utils/ImGuiSpdlogSink.h"

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

BoxCollider *boxCollider;

Text text = {};


shared_ptr<spdlog::logger> file_logger;
const Color& white = {0, 0, 0, 0};
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

void init_text();

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
    spdlog::info("Initialized project.");
    file_logger->info("Initialized project.");

    init_systems();
    spdlog::info("Initialized textures and vertices.");
    file_logger->info("Initialized textures and vertices.");

    load_enteties();
    spdlog::info("Initialized entities.");
    file_logger->info("Initialized entities.");

    init_imgui();
    spdlog::info("Initialized ImGui.");
    file_logger->info("Initialized ImGui.");

    init_camera();
    spdlog::info("Initialized camera and viewport.");
    file_logger->info("Initialized camera and viewport.");

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDepthFunc(GL_LEQUAL);

    signalQueue.init();
    spdlog::info("Initialized signal queue.");
    file_logger->info("Initialized signal queue.");

    init_time();

    spdlog::info("Initialized system timer.");
    file_logger->info("Initialized system timer.");

    init_text();
    spdlog::info("Initialized text renderer.");

    spdlog::info("Initialized game clock.");
    file_logger->info("Initialized game clock.");


#pragma endregion Init
//_______________________________NA POTRZEBY ZADANIA NA KARTY GRAFICZNE_______________________________
    float lastTextx = 500;
    float lastTexty = 500;

    int signx = 1;
    int signy = 1;

    float textx = 0;
    float texty = 0;

    int number = 0;

//____________________________________________________________________________________________________
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        //Setting up things for the rest of functionalities (ex. update_delta time)
        before_frame();
        signalQueue.update();

        // Process I/O operations here
        input();

        // Update game objects' state here
        update();


        // OpenGL rendering code here
        render();

        // Draw ImGui
        imgui_begin();
        imgui_render(); // edit this function to add your own ImGui controls
        imgui_end(); // this call effectively renders ImGui

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
}

void load_enteties() {
    model.loadModel();
    tileModel.loadModel();
    Entity *gameObject = scene.addEntity("asteroid");
    gameObject->transform.setLocalPosition({-0, 0, 0});
    const float scale = 5;
    gameObject->transform.setLocalScale({scale, scale, scale});
    gameObject->addComponent(make_unique<Render>(cubeModel));

    //create new cube model that will fit exactly to the size of the BoxCollider added to the asteroid

    gameObject->addComponent(std::make_unique<BoxCollider>(gameObject, glm::vec3{5.0f, 5.0f, 5.0f}, cubeModel));
    for (unsigned int i = 0; i < 2; ++i) {gameObject = scene.addEntity(gameObject, "asteroid");
        gameObject->addComponent(make_unique<Render>(&model));
        gameObject->transform.setLocalScale({scale, scale, scale});
        gameObject->transform.setLocalPosition({5, 0, 0});
        gameObject->transform.setLocalScale({0.2f, 0.2f, 0.2f});
        gameObject->addComponent(std::make_unique<BoxCollider>(gameObject, glm::vec3{1.0f + i + 1, 1.0f, 1.0f}, cubeModel));
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

void init_text() {
    text.init();
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
//    for (Collider *collider: scene.getColliders()) {
//        collider->render->draw(pbrSystem.pbrShader);
//    }
    file_logger->info("Rendered AsteroidsSystem.");

    bloomSystem.BlurBuffer();
    bloomSystem.Render();

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


    
    ImGui::Begin("Debug menu");
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%.2f", 1.0f / deltaTime);
    ImGui::Text(buffer);

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

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Convert mouse position to world coordinates
        float mouseX = (2.0f * xpos) / display_w - 1.0f;
        float mouseY = 1.0f - (2.0f * ypos) / display_h;
        float mouseZ = 1.0f;

        glm::vec3 ray_nds = glm::vec3(mouseX, mouseY, mouseZ);
        glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);

        glm::mat4 invProjMat = glm::inverse(camera.GetProjectionMatrix());
        glm::vec4 ray_eye = invProjMat * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

        glm::mat4 invViewMat = glm::inverse(camera.GetViewMatrix());
        glm::vec4 ray_world = invViewMat * ray_eye;
        ray_world = glm::normalize(ray_world);

        // Create ray from mouse position
        spdlog::info("Mouse position: ({}, {}, {})", ray_world.x, ray_world.y, ray_world.z);
        Ray ray = Ray(camera.Position, glm::vec3(ray_world), &scene);
        //Ray ray = Ray(camera.Position, camera.Front, &scene);
        if(ray.getHitEntity() != nullptr){
            spdlog::info("Hit entity: {}", ray.getHitEntity()->name);
        }
        else{
            spdlog::info("No hit entity");
        }
    }
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
