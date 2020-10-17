#include "Rect.h"
#include<SDL_image.h>
#include<iostream>
Rect::Rect(const Window &window, int x, int y, int w, int h, int r, int g, int b, int a) : Window(window), _w(w),_h(h),_x(x),_y(y),_r(r),_g(g),_b(b),_a(a)
{

}


Rect::~Rect()
{
    SDL_DestroyTexture(_texture);
}


void Rect::draw()const
{
    SDL_Rect destination= {_x,_y,_w,_h};  ///rectangle's position and size
    if(_texture)
    {
        SDL_SetRenderDrawColor(_renderer,0,0,0,0); /// rendering color as black
        SDL_RenderCopy(_renderer,_texture,nullptr,&destination); ///displaying picture
    }
    else
    {
        SDL_SetRenderDrawColor(_renderer,_r,_g,_b,_a);
        SDL_RenderFillRect(_renderer,&destination); ///displaying rectangle with colored
    }
}


Rect::Rect(const Window &window, int x, int y, int w, int h, const std::string& image_path): Window(window), _w(w),_h(h),_x(x),_y(y)
{
    SDL_Surface* surface = IMG_Load(image_path.c_str());///loading images
    if(!surface)std::cout<<"Failed to load image. Error :"<<IMG_GetError()<<std::endl;

    _texture = SDL_CreateTextureFromSurface(_renderer,surface); ///creating texture from surface to render

    if(!_texture)std::cout<<"Failed to create texture.Error :"<<SDL_GetError()<<std::endl;

    SDL_FreeSurface(surface);
}

int  Rect::pollEvents(bool flag)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        return 2;
        break;

    case SDL_KEYDOWN:///key pressed

        switch(event.key.keysym.scancode)
        {
        case SDL_SCANCODE_ESCAPE:///pressed Escape
//            std::cout<<"Pressed Eacape\n"<<std::endl;
            return 2;
            break;
        }


        switch(event.key.keysym.sym)
        {
        case SDLK_UP:
            btn[0]=1;
            break;
        case SDLK_DOWN:
            btn[1]=1;
            break;
        case SDLK_ESCAPE:
            return 2;
            break;
        case SDLK_s:
            return 1;
            break;
        }

        break;
    case SDL_KEYUP:///key released
        switch(event.key.keysym.sym)
        {
        case SDLK_UP:
            btn[0]=0;
            break;
        case SDLK_DOWN:
            btn[1]=0;
            break;
        }
        break;
    }
    return 0;

}

bool Rect::collision(int x, int y1,int y2,int heli_x,int heli_y,int Height)
{
    if(heli_y<50||heli_y>Height-100)
        return 1;

    if((heli_x+HeliWidth)>=x && (heli_x<(x+Distance)))
        if(heli_y<=y1  ||  heli_y+_h>=y2)
            return 1;

    return 0;
}
