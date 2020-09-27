#include "Text.h"
#include<iostream>
Text::Text()
{
    if(TTF_Init()==-1)
        printf("TTF init Error: %s\n",TTF_GetError());
    //ctor
}

Text::~Text()
{
    //dtor
//    SDL_Quit();
//    TTF_Quit();
}
void Text::createText(const Window &window,std::string s,int size)
{
//    printf("Creating text\n");

    font=TTF_OpenFont("georgiai.ttf",size);
    if(font==nullptr)
        printf("Font error  %s\n",TTF_GetError());
    surface=TTF_RenderText_Solid(font,s.c_str(),color);
    if(surface==nullptr)
        std::cout<<"Error Surface :"<<TTF_GetError()<<std::endl;
    texture=SDL_CreateTextureFromSurface(window._renderer,surface);
     if(texture==nullptr)
        std::cout<<"Error texture :"<<TTF_GetError()<<std::endl;
    SDL_FreeSurface(surface);
    surface=nullptr;
}



void Text::drawText(const Window &window,int x, int y)
{
   textRect.x=x;
   textRect.y=y;
   SDL_QueryTexture(texture,NULL,NULL,&textRect.w,&textRect.h);
   SDL_RenderCopy(window._renderer,texture,NULL,&textRect);
}











