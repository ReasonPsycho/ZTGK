#ifndef SCRUB_SQUAD_SPEAKER_H
#define SCRUB_SQUAD_SPEAKER_H

#include "ECS/Component.h"
#include <string>

class Speaker : public Component {
public:
    Speaker();
    ~Speaker() override = default;

    std::string name;
    int volume;
    int panning;

    void PlaySound(std::string soundName, int loops = 0);
    void SetPanning(int panning);
    void SetVolume(int volume);
    void showImGuiDetailsImpl(Camera *camera) override;
    void PlayRandomSoundFromGroup(std::string groupName);
    void UpdateImpl() override;

private:
    Camera* camera;
    int calculatePanning();
    int calculateVolume();
};

#endif // SCRUB_SQUAD_SPEAKER_H
