cmake_minimum_required(VERSION 3.4.1)
project(Scrub_Squad)
set(CMAKE_CXX_STANDARD 23)

IF (WIN32)
    message(NOTICE "\n")
    message(NOTICE "********************** IMPORTANT NOTICE ****************************\n")
    message(NOTICE "Make sure you have enabled Developer Mode in your system settings!")
    message(NOTICE "To enable Developer Mode go to Settings -> Update & Security -> For developers -> Developer Mode ON")
    message(NOTICE "\n********************************************************************")
    message(NOTICE "\n")
ENDIF ()

if (!MSVC)
    message(NOTICE "\n")
    message(NOTICE "********************** IMPORTANT NOTICE ****************************\n")
    message(NOTICE "It's highly recommended to use MSVC as compiler!")
    message(NOTICE "\n********************************************************************")
    message(NOTICE "\n")
endif ()


if(DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")


set(OpenGL_GL_PREFERENCE GLVND) # this might be helpfull for linux IDK
cmake_policy(SET CMP0072 NEW) # for GLVND

add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1") # supress warnings XDE

# ---- Main project's files ----
# Add source files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/res)


# Gather source and header files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp") #SIDE note u need to rerun CMAKE each time u add class manually since it doesn't need to change to add file.
file(GLOB_RECURSE HEADER_FILES "src/*.h")

# Search for the assets files
file(GLOB_RECURSE ASSETS_FILES "res/*.*")

# Group files for easier navigation in IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES} ${HEADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${ASSETS_FILES})

#enable rc for the icon
enable_language("RC")
# Define the startup executable for the project
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${ASSETS_FILES} resources.rc)
# Treat asset files as headers (prevents them from being compiled)
set_source_files_properties(${ASSETS_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

find_package(OpenGL  REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED) #TODO remove on build compilation docking
find_package(unofficial-imguizmo CONFIG REQUIRED) #TODO remove on build compilation
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(freetype-gl CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Tracy CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(mpg123 CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_opengl_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::imguizmo::imguizmo)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE freetype-gl)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(${PROJECT_NAME}  PRIVATE Tracy::TracyClient)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)
target_link_libraries(${PROJECT_NAME} PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)
#Asssimp config
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE)
set(ASSIMP_BUILD_FBX_IMPORTER TRUE)

# tracey config
option( TRACY_ENABLE "" ON)
option( TRACY_ON_DEMAND "" ON)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/tracey
        ${CMAKE_CURRENT_BINARY_DIR}/tracey)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DRELEASE_BUILD)
endif()

if (MSVC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC NOMINMAX)
endif ()


