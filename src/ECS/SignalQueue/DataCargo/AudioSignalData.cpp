//
// Created by cheily on 21.03.2024.
//

#include "AudioSignalData.h"
#include "../Signal.h"

AudioSignalData::AudioSignalData(const std::string &filepath, const std::string & message) : SignalData(message), filepath(filepath) {}

Signal AudioSignalData::signal(const std::string &filepath, const std::string & message) {
    return {Signal::signal_types.audio_signal, std::make_shared<AudioSignalData>(filepath, message)};
}
