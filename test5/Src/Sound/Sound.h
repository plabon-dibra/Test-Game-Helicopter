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
    void addMusic(const char* path);
    void playMusic(int kotobar);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();

private:
    Mix_Music* m_music=nullptr;
};

#endif // SOUND_H
