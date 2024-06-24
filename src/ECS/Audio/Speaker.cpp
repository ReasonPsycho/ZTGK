#include "Speaker.h"
#include "imgui.h"
#include "ECS/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ECS/Utils/Globals.h"

Speaker::Speaker() {
    name = "Speaker";
    volume = 128;
    panning = 128;
    camera = ztgk::game::camera;
}

void Speaker::showImGuiDetailsImpl(Camera* camera) {
    ImGui::Text("Speaker");
    // Add ImGui controls for volume and other properties if needed
}

void Speaker::PlaySound(std::string soundName, int loops) {
    auto audioManager = ztgk::game::audioManager;

    int calculatedVolume = calculateVolume();
    audioManager->setSoundVolume(soundName, calculatedVolume);
    audioManager->playSound(soundName, loops, panning);
}

void Speaker::SetVolume(int volume) {
    this->volume = volume;
    // Update the volume in the AudioManager if needed
}

void Speaker::SetPanning(int panning) {
    this->panning = panning;
}

void Speaker::PlayRandomSoundFromGroup(std::string groupName) {
    auto audioManager = ztgk::game::audioManager;

    int calculatedVolume = calculateVolume();
    audioManager->setVolumeForGroup(groupName, calculatedVolume);
    audioManager->playRandomSoundFromGroup(groupName, panning);
}

void Speaker::UpdateImpl() {
    panning = calculatePanning();
    volume = calculateVolume();
}

int Speaker::calculatePanning() {
    // Calculate direction from camera to speaker entity
    glm::vec3 speakerPosition = parentEntity->transform.getLocalPosition();
    glm::vec3 cameraPosition = camera->Position;

    glm::vec3 direction = glm::normalize(speakerPosition - cameraPosition);

    // Calculate the right vector for the camera
    glm::vec3 cameraRight = glm::normalize(glm::cross(camera->Front, camera->Up));

    // Calculate the dot product between the camera's right vector and the direction vector
    float rightComponent = glm::dot(cameraRight, direction);

    // Map the right component to the panning value (0 to 255)
    // Assuming rightComponent is in the range [-1, 1], normalize it to [0, 1]
    float normalizedRightComponent = (rightComponent + 1.0f) / 2.0f;

    int panningValue = static_cast<int>(normalizedRightComponent * 255);

    return panningValue;
}


int Speaker::calculateVolume() {
    // Get the positions
    glm::vec3 speakerPosition = parentEntity->transform.getLocalPosition();
    glm::vec3 cameraPosition = camera->Position;

    // Calculate the distance between the speaker and the camera
    float distance = glm::distance(speakerPosition, cameraPosition);

    // Define the maximum distance where the volume will be 0
    float maxDistance = 100.0f; // You can adjust this value as needed

    // Normalize the distance to the range [0, 1]
    float normalizedDistance = glm::clamp(distance / maxDistance, 0.0f, 1.0f);

    // Invert the normalized distance to get the volume attenuation
    float volumeFactor = 1.0f - normalizedDistance;

    // Map the volume factor to the range [0, 128]
    int calculatedVolume = static_cast<int>(volumeFactor * 128);

    return calculatedVolume;
}