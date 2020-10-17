#include "Text.h"
Text::Text()
{
    //ctor
    if(TTF_Init()==-1)
        printf("TTF init Error: %s\n",TTF_GetError());
}

Text::~Text()
{
    //dtor
}
void Text::createText(const Window &window,std::string s,int size)
{
    font=TTF_OpenFont("georgiai.ttf",size);
    if(font==nullptr)
        printf("Font error  %s\n",TTF_GetError());
    surface=TTF_RenderText_Solid(font,s.c_str(),color);
    if(surface==nullptr)
        printf("Error Surface  : %s\n",TTF_GetError());
    texture=SDL_CreateTextureFromSurface(window._renderer,surface);
     if(texture==nullptr)
             printf("Error texture  : %s\n",TTF_GetError());


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











