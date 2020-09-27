#ifndef TEXT_H
#define TEXT_H
#include<SDL_ttf.h>
#include<string>
#include<../Window/Window.h>

class Text:public Window{
    public:
        Text();
        ~Text();
        void createText(const Window &window,std::string s,int size);
        void drawText(const Window &window,int x,int y);

    private:
        TTF_Font* font=nullptr;
        SDL_Color color={255,0,0,255};
        SDL_Surface *surface=nullptr;
        SDL_Texture *texture=nullptr;
        SDL_Rect textRect;
};

#endif // TEXT_H
