#include "Sound.h"
#include<iostream>
Sound::Sound()
{
    SDL_Init(SDL_INIT_AUDIO);
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,4096)!=0)
    {
        std::cout<<"Couldn't open audio,Error: "<<Mix_GetError()<<std::endl;
        exit(-1);
    }
}

Sound::~Sound()
{
    SDL_Quit();
    Mix_Quit();
}

void Sound::addMusic(const char* path)
{
    m_music = Mix_LoadMUS(path);
    if(m_music==nullptr)
        std::cout<<"Failed to Add Music,Error: "<<Mix_GetError()<<std::endl;
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


