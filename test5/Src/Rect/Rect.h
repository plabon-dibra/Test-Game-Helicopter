#ifndef RECT_H
#define RECT_H
#include<string>
#include "../Window/Window.h"
#define HeliHeight 60
#define HeliWidth 120
#define Distance 20
#define ArrayDistance 240

class Rect:public Window {
    public:
        Rect(const Window &window, int x,int y,int w,int h,int r,int g,int b,int a);
        Rect(const Window &window, int x,int y,int w,int h,const std::string &image_path);
        ~Rect();
        void draw()const;/// to display
        int pollEvents(bool flag);
        int  _x,_y;
        bool btn[2]={0};
        bool collision(int x, int y1,int y2,int heli_x,int heli_y,int Height);
    private:
        int _w,_h;
        int _r,_g,_b,_a;
        SDL_Texture *_texture=nullptr;
};

#endif // RECT_H
