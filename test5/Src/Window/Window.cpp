#include "Window.h"
#include<SDL_image.h>
#include<iostream>

Window::Window()
{

}

Window::Window(const std::string& title, int width, int height): m_title(title),_width(width),_height(height)
{
    _closed= !init();
}



Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}




void Window::clear()const
{
    SDL_Rect rect={0,0,Width,50};
    SDL_Rect rect2={0,Height-50,Width,50};
    SDL_SetRenderDrawColor(_renderer,102,0,102,255);
    SDL_RenderFillRect(_renderer,&rect);
    SDL_SetRenderDrawColor(_renderer,64,64,64,255);
    SDL_RenderFillRect(_renderer,&rect2);
    SDL_RenderPresent(_renderer);
    SDL_SetRenderDrawColor(_renderer,51,153,255,255);
    SDL_RenderClear(_renderer);
}




bool Window::init()
{
    if(SDL_Init(SDL_INIT_VIDEO)!= 0)
    {
        std::cerr<<"Failed to initialize SDL.\n";
        return 0;
    }

    if(IMG_Init(IMG_INIT_PNG & IMG_INIT_JPG))
    {
        std::cerr<<"Failed to initialize SDL_Image.\n";
        return false;
    }

    if(TTF_Init()<0)
        std::cout<<"Failed to initialize ttf.  Error "<<TTF_GetError()<<std::endl;


    _window = SDL_CreateWindow(m_title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,_width,_height,0);///creating window

    if(_window ==nullptr)
    {
        std::cerr<<"Failed to create window.\n";
        return 0;
    }
    _renderer =SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED); ///creating renderer
    if(_renderer==nullptr)
    {
        std::cerr<<"Failed to create renderer.\n";
        return 0;
    }
    return true;
}

