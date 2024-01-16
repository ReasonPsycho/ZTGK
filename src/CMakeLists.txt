# Add source files
file(GLOB_RECURSE SOURCE_FILES
        *.c
        *.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        *.h
        *.hpp)

# Search for the assets files
file(GLOB_RECURSE ASSETS_FILES
        ${CMAKE_SOURCE_DIR}/res/*.*)

set_source_files_properties(${ASSETS_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${ASSETS_FILES})


# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${ASSETS_FILES}
        modelLoading/Shader.cpp
        modelLoading/Shader.h
        modelLoading/Texture.cpp
        modelLoading/Texture.h
        modelLoading/Mesh.cpp
        modelLoading/Mesh.h
        Camera.cpp
        Camera.h
        modelLoading/Model.cpp
        modelLoading/Model.h
        AsteroidsSystem.cpp
        AsteroidsSystem.h
        modelLoading/ComputeShader.cpp
        modelLoading/ComputeShader.h
        PBRSystem.cpp
        PBRSystem.h
        Enitity.cpp
        Enitity.h
        Systems/LightSystem/ILight.h
        Systems/LightSystem/Lights/DirLight.cpp
        Systems/LightSystem/Lights/DirLight.h
        Systems/LightSystem/Lights/PointLight.cpp
        Systems/LightSystem/Lights/PointLight.h
        Systems/LightSystem/Lights/SpotLight.cpp
        Systems/LightSystem/Lights/SpotLight.h
        Systems/LightSystem/ILight.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_compile_definitions(${PROJECT_NAME} PRIVATE LIBRARY_SUFFIX="")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        ${glad_SOURCE_DIR}
        ${stb_image_SOURCE_DIR}
        ${imgui_SOURCE_DIR})


target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} stb_image)
target_link_libraries(${PROJECT_NAME} assimp)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} imguizmo)
target_link_libraries(${PROJECT_NAME} spdlog)
target_link_libraries(${PROJECT_NAME} glm::glm)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC NOMINMAX)
endif()
