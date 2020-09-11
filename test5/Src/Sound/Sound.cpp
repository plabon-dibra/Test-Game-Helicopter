#include "Sound.h"
#include<iostream>
Sound::Sound()
{
    SDL_Init(SDL_INIT_AUDIO);
    if(Mix_OpenAudio(22050,AUDIO_S16SYS,2,4096)!=0)
    {
        std::cout<<"Couldn't open audio."<<std::endl;
        exit(-1);
    }
}

Sound::~Sound()
{
    SDL_Quit();
    Mix_Quit();
}

void Sound::addSounds(const char* path)
{
    Mix_Chunk* tmp=Mix_LoadWAV(path); ///loading sounds
    if(tmp!=nullptr)
    {
        m_Sounds.push_back(tmp);
        std::cout<<m_Sounds.size()-1<<". sound loaded: "<<path<<"\n";
    }
    else
    {
        std::cout<<"Couldn't add audio."<<std::endl;
    }
    Mix_FreeChunk(tmp);
    tmp=nullptr;
}

void Sound::playSound(const int chose) const
{
    if(chose>m_Sounds.size()-1)
    {
        std::cout<<"Out of sound range!\n";
        return ;
    }
    Mix_PlayChannel(-1,m_Sounds[chose],0);
}


void Sound::addMusic(const char* path)
{
    m_music = Mix_LoadMUS(path);
}

void Sound::playMusic(int kotobar)
{
    Mix_PlayMusic(m_music,kotobar);
}

void Sound::pauseMusic()
{
    Mix_PauseMusic();
}

void Sound::resumeMusic()
{
    Mix_ResumeMusic();
}

void Sound::stopMusic()
{
    Mix_HaltMusic();
}

