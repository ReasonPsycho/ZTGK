#include "AudioManager.h"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <mpg123.h>
#include <random>
#include "Speaker.h"
#include <algorithm> // for std::find
#include "imgui.h"

AudioManager::AudioManager() {
    name= "AudioManager";
    componentTypes = { std::type_index(typeid(Speaker)) };
}

AudioManager::~AudioManager() {
    close();
}

bool AudioManager::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        spdlog::error("IN AUDIO MANAGER INIT - SDL initialization failed: {}", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        spdlog::error("IN AUDIO MANAGER INIT - SDL_mixer initialization failed: {}", Mix_GetError());
        return false;
    }

    int flags = MIX_INIT_MP3;
    int initialized = Mix_Init(flags);
    if ((initialized & flags) != flags) {
        spdlog::error("IN AUDIO MANAGER INIT - SDL_mixer MP3 initialization failed: {}", Mix_GetError());
        return false;
    }

    spdlog::info("SDL_mixer initialized successfully with MP3 support.");

    setAmbientQueue();

    return true;
}

void AudioManager::close() {
    for (auto& sound : soundMap) {
        Mix_FreeChunk(sound.second);
    }
    soundMap.clear();

    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

bool AudioManager::loadSound(const std::string& filePath, const std::string& soundKey) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (!sound) {
        spdlog::error("IN AUDIO MANAGER LOAD SOUND: Failed to load sound from {}: {}", filePath, Mix_GetError());
        return false;
    }

    soundMap[soundKey] = sound;
    return true;
}

void AudioManager::playSound(const std::string& soundKey, int loops, int panning) {
    if (soundKey.empty()) {
        spdlog::warn("IN AUDIO MANAGER PLAY SOUND: Sound key is empty. No action taken.");
        return;
    }
    if (soundMap.find(soundKey) == soundMap.end()) {
        spdlog::warn("IN AUDIO MANAGER PLAY SOUND: Sound key {} not found. No action taken.", soundKey);
        return;
    }

    int channel = Mix_PlayChannel(-1, soundMap[soundKey], loops);
    if (channel == -1) {
        spdlog::error("IN AUDIO MANAGER PLAY SOUND: Unable to play sound: {}", Mix_GetError());
        return;
    }

    // If panning is provided, set the panning
    if (panning >= 0 && panning <= 255) {
        Uint8 left = static_cast<Uint8>((255 - panning) * 2.55);
        Uint8 right = static_cast<Uint8>(panning * 2.55);
        Mix_SetPanning(channel, left, right);
    } else {
        if(panning != -1)
            spdlog::warn("IN AUDIO MANAGER PLAY SOUND: Panning value must be between 0 - 255. Ignoring panning.");
        // Reset panning to default (centered) if panning is not provided
        Mix_SetPanning(channel, 255, 255);
    }
}

void AudioManager::stopSound(const std::string& soundKey) {
    if (soundKey.empty()) {
        Mix_HaltChannel(-1);
    } else {
        for (int i = 0; i < Mix_AllocateChannels(-1); ++i) {
            if (Mix_GetChunk(i) == soundMap[soundKey]) {
                Mix_HaltChannel(i);
            }
        }
    }
}

void AudioManager::pauseSound(const std::string& soundKey) {
    if (soundKey.empty()) {
        Mix_Pause(-1);
    } else {
        for (int i = 0; i < Mix_AllocateChannels(-1); ++i) {
            if (Mix_GetChunk(i) == soundMap[soundKey]) {
                Mix_Pause(i);
            }
        }
    }
}

void AudioManager::resumeSound(const std::string& soundKey) {
    if (soundKey.empty()) {
        Mix_Resume(-1);
    } else {
        for (int i = 0; i < Mix_AllocateChannels(-1); ++i) {
            if (Mix_GetChunk(i) == soundMap[soundKey]) {
                Mix_Resume(i);
            }
        }
    }
}

void AudioManager::setSoundVolume(const std::string& soundKey, int volume) {
    if (volume < 0) {
        spdlog::warn("IN AUDIO MANAGER SET VOLUME | FOR SOUND {}: Volume must be between 0 - 128. Clamping to 0.", soundKey);
        volume = 0;
    }
    if (volume > 128) {
        spdlog::warn("IN AUDIO MANAGER SET VOLUME | FOR SOUND {}: Volume must be between 0 - 128. Clamping to 128.", soundKey);
        volume = 128;
    }
    if (soundKey.empty()) {
        spdlog::warn("IN AUDIO MANAGER SET VOLUME: Sound key is empty. No action taken.");
        return;
    }
    Mix_VolumeChunk(soundMap[soundKey], volume);
}

void AudioManager::setGlobalVolume(int volume) {
    if (volume < 0) {
        spdlog::warn("IN AUDIO MANAGER SET GLOBAL VOLUME: Volume must be between 0 - 128. Clamping to 0.");
        volume = 0;
    }
    if (volume > 128) {
        spdlog::warn("IN AUDIO MANAGER SET GLOBAL VOLUME: Volume must be between 0 - 128. Clamping to 128.");
        volume = 128;
    }
    Mix_Volume(-1, volume);
}

bool AudioManager::isSoundPlaying(const std::string& soundKey) {
    if (soundKey.empty()) {
        spdlog::warn("IN AUDIO MANAGER IS SOUND PLAYING: Sound key is empty. No action taken.");
        return false;
    }
    for (int i = 0; i < Mix_AllocateChannels(-1); ++i) {
        if (Mix_GetChunk(i) == soundMap[soundKey]) {
            return Mix_Playing(i) == 1;
        }
    }
    return false;
}

void AudioManager::playAmbientMusic() {
    if (soundQueue.empty()) {
        setAmbientQueue();
    }

    std::vector<std::string> keys = {"ambient1", "ambient2", "ambient3", "ambient4"};
    for (auto& key : keys) {
        if (isSoundPlaying(key)) {
            return;
        }
    }

    playSound(soundQueue.front(), -1);
    soundQueue.pop();
}

void AudioManager::setVolumeForGroup(const std::string& groupName, int volume) {
    if (volume < 0) {
        spdlog::warn("IN AUDIO MANAGER SET GLOBAL VOLUME: Volume must be between 0 - 128. Clamping to 0.");
        volume = 0;
    }
    if (volume > 128) {
        spdlog::warn("IN AUDIO MANAGER SET GLOBAL VOLUME: Volume must be between 0 - 128. Clamping to 128.");
        volume = 128;
    }

    std::vector<std::string> keys;
    for (auto& sound : soundMap) {
        if (sound.first.find(groupName) != std::string::npos) {
            keys.push_back(sound.first);
        }
    }

    for (auto& key : keys) {
        setSoundVolume(key, volume);
    }
}

void AudioManager::setAmbientQueue() {
    std::vector<int> randomNumbers = {1, 2, 3, 4};
    std::shuffle(randomNumbers.begin(), randomNumbers.end(), std::mt19937(std::random_device()()));

    soundQueue.emplace("ambient" + std::to_string(randomNumbers[0]));
    soundQueue.emplace("ambient" + std::to_string(randomNumbers[1]));
    soundQueue.emplace("ambient" + std::to_string(randomNumbers[2]));
    soundQueue.emplace("ambient" + std::to_string(randomNumbers[3]));
}

void AudioManager::playRandomSoundFromGroup(const std::string& groupName, int padding) {
    std::vector<std::string> keys;
    for (auto& sound : soundMap) {
        if (sound.first.find(groupName) != std::string::npos) {
            keys.push_back(sound.first);
        }
    }

    if (keys.empty()) {
        spdlog::warn("IN AUDIO MANAGER PLAY SOUND FROM GROUP: No sounds found for group {}", groupName);
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, keys.size() - 1);
    int random_number = dis(gen);

    playSound(keys[random_number], 0, padding);
}

void AudioManager::addComponent(void *component) {
    speakers.push_back(static_cast<Speaker*>(component));
}

void AudioManager::removeComponent(void *component) {
    auto it = std::find(speakers.begin(), speakers.end(), (Speaker*)component);
    if (it != speakers.end()) {
        speakers.erase(it);
    }

}

const std::type_index *AudioManager::getComponentTypes() {
    return componentTypes.data();
}

void AudioManager::showImGuiDetailsImpl(Camera *camera) {
    ImGui::Text("Audio Manager");
    ImGui::Text("Speakers: %zu", speakers.size());
    ImGui::Text("SoundMap: %zu", soundMap.size());
}

void AudioManager::UpdateImpl() {
    for (Speaker* speaker: speakers)
        speaker->Update();

}

