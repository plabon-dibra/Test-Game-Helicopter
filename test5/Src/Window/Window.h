#ifndef WINDOW_H
#define WINDOW_H
#include<string>
#include<SDL_mixer.h>
#include<SDL.h>
#include<SDL_ttf.h>
#define Height 700
#define Width 1200
class Window
{
    public:
        Window();
        Window(const std::string &title,int width,int height);
        ~Window();
        void clear()const;
        inline bool isclosed()const{return _closed;}
        bool init();///initialization everything
        void close(){_closed=true;};
        SDL_Window* _window =nullptr;
        SDL_Renderer* _renderer=nullptr;

    private:
        std::string m_title;
        int _width=Width;
        int _height=Height;
        bool _closed=false;
};

#endif // WINDOW_H
