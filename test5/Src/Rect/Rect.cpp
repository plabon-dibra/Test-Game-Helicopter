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
    if(!surface)
    {
        std::cerr<<"Failed to create surface.\n";
    }
    _texture = SDL_CreateTextureFromSurface(_renderer,surface); ///creating texture from surface to render
    if(!_texture)
    {
        std::cerr<<"Failed to create texture.\n";
    }
    SDL_FreeSurface(surface);
}

int  Rect::pollEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        return 2;
    case SDL_KEYDOWN:///on mouse clicked
        switch(event.key.keysym.sym)
        {
        case SDLK_UP:
            _y-=heli_d;
            break;
        case SDLK_DOWN:
            _y+=40;
            break;
        case SDLK_ESCAPE:
           return 2;
            break;
        case SDLK_s:///pressed s
            return 1;
            break;
        }
        break;

    default:
        break;
    }
    return 0;
}

bool Rect::collision(int x, int y1,int y2,int heli_x,int heli_y)
{
   if(heli_y<0||heli_y+_h>Height)
    return 1;

   if((heli_x+HeliWidth)>=x && (heli_x<(x+Distance)))
   {
       if(heli_y<=y1  ||  heli_y>=y2)
          return 1;
   }

   return 0;
}
