#include "AudioManager.h"
#include "spdlog/spdlog.h"

AudioManager::AudioManager() : globalVolume(MIX_MAX_VOLUME) {
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
    if(!(Mix_Init(flags) & flags)) {
        spdlog::error("IN AUDIO MANAGER INIT - SDL_mixer MP3 initialization failed: {}", Mix_GetError());
        return false;
    }

    return true;
}

void AudioManager::close() {
    for (auto& sound : soundMap) {
        Mix_FreeChunk(sound.second);
    }
    soundMap.clear();

    Mix_CloseAudio();
    SDL_Quit();
}

bool AudioManager::loadSound(const std::string& filePath, const std::string& soundKey) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (!sound) {
        spdlog::error("IN AUDIO MANAGER LOAD SOUND : Failed to load sound: {}", Mix_GetError());
        return false;
    }

    soundMap[soundKey] = sound;
    return true;
}

void AudioManager::playSound(const std::string& soundKey, int loops) {
    if (soundKey.empty()) {
        spdlog::warn("IN AUDIO MANAGER PLAY SOUND : Sound key is empty. No action taken.");
        return;
    }
    Mix_PlayChannel(-1, soundMap[soundKey], loops);
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
        spdlog::warn("IN AUDIO MANAGER SET VOLUME | FOR SOUND {} | Volume must be between 0 - 128. Clamping to 0.", soundKey);
        volume = 0;
    }
    if (volume > 128) {
        spdlog::warn("IN AUDIO MANAGER SET VOLUME | FOR SOUND {} | Volume must be between 0 - 128. Clamping to 128.", soundKey);
        volume = 128;
    }
    if (soundKey.empty()) {
        spdlog::warn("IN AUDIO MANAGER SET VOLUME : Sound key is empty. No action taken.");
        return;
    }
    Mix_VolumeChunk(soundMap[soundKey], volume);
}

void AudioManager::setGlobalVolume(int volume) {
    if (volume < 0) {
        spdlog::warn("IN AUDIO MANAGER SET GLOBAL VOLUME : Volume must be between 0 - 128. Clamping to 0.");
        volume = 0;
    }
    if (volume > 128) {
        spdlog::warn("IN AUDIO MANAGER SET GLOBAL VOLUME : Volume must be between 0 - 128. Clamping to 128.");
        volume = 128;
    }
    this->globalVolume = volume;
    Mix_Volume(-1, volume);
}
