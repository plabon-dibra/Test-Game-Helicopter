#ifndef WINDOW_H
#define WINDOW_H
#include<string>
#include<SDL_mixer.h>
#include<SDL.h>
#include<SDL_ttf.h>

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
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer=nullptr;
        bool _closed=false;
        int _width;
        int _height;

    private:
        std::string m_title;

};

#endif // WINDOW_H
