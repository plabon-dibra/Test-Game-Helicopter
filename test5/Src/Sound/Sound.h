#ifndef SOUND_H
#define SOUND_H
#include<SDL_mixer.h>
#include<vector>
#include<SDL.h>

class Sound
{
public:
    Sound();
    ~Sound();
    void addSounds(const char* path);
    void addMusic(const char* path);
    void playMusic(int kotobar);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void playSound(const int chose)const;

private:
    std::vector<Mix_Chunk*>m_Sounds;
    Mix_Music* m_music;
};

#endif // SOUND_H
