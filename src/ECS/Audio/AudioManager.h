#ifndef AUDIOMANAGER_H 
#define AUDIOMANAGER_H 
 
#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h> 
#include <string> 
#include <unordered_map> 
#include "spdlog/spdlog.h" 
#include <queue> 
 
/** 
 * @class AudioManager 
 * @brief Manages audio operations such as loading, playing, pausing, stopping, and setting volume for sounds. 
 */ 
class AudioManager { 
public: 
    /** 
     * @brief Constructor for AudioManager. 
     */ 
    AudioManager(); 
 
    /** 
     * @brief Destructor for AudioManager. 
     */ 
    ~AudioManager(); 
 
    /** 
     * @brief Initializes the audio system. 
     * @return True if initialization is successful, false otherwise. 
     */ 
    bool init(); 
 
    /** 
     * @brief Closes the audio system and frees resources. 
     */ 
    void close(); 
 
    /** 
     * @brief Loads a sound from a file. 
     * @param filePath The path to the sound file. 
     * @param soundKey The key to associate with the loaded sound. 
     * @return True if the sound is loaded successfully, false otherwise. 
     */ 
    bool loadSound(const std::string& filePath, const std::string& soundKey); 
 
    /** 
     * @brief Plays a sound. 
     * @param soundKey The key of the sound to play. 
     * @param loops Number of times to loop the sound. -1 means infinite loop. 
     */ 
    void playSound(const std::string& soundKey, int loops = 0); 
 
    /** 
     * @brief Stops a sound. 
     * @param soundKey The key of the sound to stop. If empty, stops all sounds. 
     */ 
    void stopSound(const std::string& soundKey = ""); 
 
    /** 
     * @brief Pauses a sound. 
     * @param soundKey The key of the sound to pause. If empty, pauses all sounds. 
     */ 
    void pauseSound(const std::string& soundKey = ""); 
 
    /** 
     * @brief Resumes a sound. 
     * @param soundKey The key of the sound to resume. If empty, resumes all sounds. 
     */ 
    void resumeSound(const std::string& soundKey = ""); 
 
    /** 
     * @brief Sets the volume for a specific sound. 
     * @param soundKey The key of the sound to set volume for. 
     * @param volume The volume level (0 to 128). 
     */ 
    void setSoundVolume(const std::string& soundKey, int volume); 
 
    /** 
     * @brief Sets the global volume for all sounds. 
     * @param volume The global volume level (0 to 128). 
     */ 
    void setGlobalVolume(int volume); 
 
    bool isSoundPlaying(const std::string& soundKey); 
 
    void setVolumeForGroup(const std::string& groupName, int volume); 
 
    void playAmbientMusic(); 
 
    void playRandomSoundFromGroup(const std::string& groupName); 
 
private: 
    std::unordered_map<std::string, Mix_Chunk*> soundMap; ///< Map of sound keys to their corresponding Mix_Chunk objects. 
 
    std::queue<std::string> soundQueue; ///< Queue of sound keys to play 
 
    void setAmbientQueue(); 
}; 
 
#endif // AUDIOMANAGER_H 
