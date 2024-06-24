#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include "spdlog/spdlog.h"
#include <queue>
#include "ECS/System.h"
#include "Speaker.h"
#include <typeindex> // Ensure you have this included

/**
 * @class AudioManager
 * @brief Manages audio operations such as loading, playing, pausing, stopping, and setting volume for sounds.
 */
class AudioManager : public System {
public:
    AudioManager();
    ~AudioManager() override;

    void addComponent(void *component) override;
    void removeComponent(void *component) override;
    const std::type_index *getComponentTypes() override;
    int getNumComponentTypes() override { return 1; }

    void UpdateImpl() override;
    void showImGuiDetailsImpl(Camera *camera) override;
    void registerComponents() override {}

    bool init();
    void close();

    bool loadSound(const std::string& filePath, const std::string& soundKey);
    void playSound(const std::string& soundKey, int loops = 0, int panning = -1);
    void stopSound(const std::string& soundKey = "");
    void pauseSound(const std::string& soundKey = "");
    void resumeSound(const std::string& soundKey = "");
    void setSoundVolume(const std::string& soundKey, int volume);
    void setGlobalVolume(int volume);
    bool isSoundPlaying(const std::string& soundKey);
    void setVolumeForGroup(const std::string& groupName, int volume);
    void playAmbientMusic();
    void playRandomSoundFromGroup(const std::string& groupName, int padding = -1);

    std::vector<Speaker*> speakers;

private:
    std::array<std::type_index, 1> componentTypes = {
            std::type_index(typeid(Speaker))
    };

    void setAmbientQueue();
    std::unordered_map<std::string, Mix_Chunk*> soundMap; // Map of sound keys to their corresponding Mix_Chunk objects.
    std::queue<std::string> soundQueue; // Queue of sound keys to play
};

#endif // AUDIOMANAGER_H
