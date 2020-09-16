#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "Src\Window\Window.h"
#include "Src\Rect\Rect.h"
#include "Sound.h"


int  check(int x,int y)
{
    int  n=0,x1=440,x2=770;
    if(x>=x1&&x<=x2)
    {
        if(y>=233&&y<=300)n=1;
        else if(y>=323&&y<=377)n=2;
        else if(y>=408&&y<=458)n=3;
        else if(y>=480&&y<=518)n=4;
        else if(y>=554&&y<=593)n=5;
        else if(y>=627&&y<=670)n=6;
    }
    return n;
}
int check2(int x, int y)
{
    int m=1;
    int x1=440,x2=775;
    if(x>=975&&y>=600)
        m=2;
    else if(x>=x1&&x<=x2 && y>=270&&y<=360)
        m=3;
    else if(x>=x1&&x<=x2 && y>=385&&y<=480)
        m=4;
    else if(x>=x1&&x<=x2 && y>=505&&y<=571)
        m=5;

    return m;
}

struct abstacle
{
    int x,value;
    int pos_y1,pos_y2;
} a[6];

int main(int argc,char *argv[])
{
    Window window("Helicopter Game",Width,Height);   ///initialize window

    ///getting images
    Rect heli1=Rect(window,100,100,HeliWidth,HeliHeight,"Assets/Images/heli1.png");
    Rect heli2=Rect(window,100,100,HeliWidth,HeliHeight,"Assets/Images/heli2.png");

    Rect welcome=Rect(window,0,0,Width,Height,"Assets/Images/Welcome.png");
    Rect background=Rect(window,0,0,Width,Height,"Assets/Images/back.png");
    Rect gameOver=Rect(window,0,0,Width,Height,"Assets/Images/gameOver.jpg");
    Rect wall=Rect(window,100,0,20,Height,"Assets/Images/wall.jpg");

    Rect menu=Rect(window,0,0,Width,Height,"Assets/Images/Menu/menu.jpg");
    Rect playMenu=Rect(window,0,0,Width,Height,"Assets/Images/Menu/playMenu.jpg");
    Rect instructionMenu=Rect(window,0,0,Width,Height,"Assets/Images/Menu/instructionMenu.jpg");
    Rect levelMenu=Rect(window,0,0,Width,Height,"Assets/Images/Menu/levelMenu.jpg");
    Rect highscoreMenu=Rect(window,0,0,Width,Height,"Assets/Images/Menu/highScoreMenu.jpg");
    Rect settingMenu=Rect(window,0,0,Width,Height,"Assets/Images/Menu/settingMenu.jpg");
    Rect quitMenu=Rect(window,0,0,Width,Height,"Assets/Images/Menu/quitMenu.jpg");

    Rect instruction=Rect(window,0,0,Width,Height,"Assets/Images/General/instruction.jpg");
    Rect level=Rect(window,0,0,Width,Height,"Assets/Images/General/level.jpg");
    Rect highscore=Rect(window,0,0,Width,Height,"Assets/Images/General/highScore.jpg");
    Rect setting=Rect(window,0,0,Width,Height,"Assets/Images/General/setting.jpg");

    Rect instructionBack=Rect(window,0,0,Width,Height,"Assets/Images/MenuBack/instructionBack.jpg");
    Rect levelBack=Rect(window,0,0,Width,Height,"Assets/Images/MenuBack/levelBack.jpg");
    Rect highscoreBack=Rect(window,0,0,Width,Height,"Assets/Images/MenuBack/highScoreBack.jpg");
    Rect settingBack=Rect(window,0,0,Width,Height,"Assets/Images/MenuBack/settingBack.jpg");

    Rect levelEasy=Rect(window,0,0,Width,Height,"Assets/Images/General/levelEasy.jpg");
    Rect levelMedium=Rect(window,0,0,Width,Height,"Assets/Images/General/levelMedium.jpg");
    Rect levelHard=Rect(window,0,0,Width,Height,"Assets/Images/General/levelHard.jpg");

    Rect settingOn=Rect(window,0,0,Width,Height,"Assets/Images/General/settingOn.jpg");
    Rect settingOff=Rect(window,0,0,Width,Height,"Assets/Images/General/settingOff.jpg");





    /// Sound
    bool soundFlag=true;
    Sound sound,heliSound,bomb;
    sound.addMusic("Assets/Sounds/backsound.mp3"); ///addding music
    bomb.addMusic("Assets/Sounds/bomb.mp3"); ///addding music
    heliSound.addMusic("Assets/Sounds/heliSound.mp3"); ///addding music

    welcome.draw();   ///welcome image display
    SDL_RenderPresent(window._renderer);
    SDL_RenderClear(window._renderer);
    SDL_Delay(2000);///2 second Delay

    SDL_Event evnt,ev,event;


stage1:
    sound.playMusic(-1);  ///infinite loop
    sound.pauseMusic();   ///paused music

    window._closed=0;
    heli1._y=Height/3;
    int run =1,n=0,m=0,M=0,Mm=0,speed=1;
    float v_level=5;  ///initially
    event=evnt;
    while(run==1)
    {
//        std::cout<<"Run END=>run="<<run<<"   n="<<n<<"   ,m="<<m<<"   M="<<M<<"   Mm="<<Mm<<std::endl;
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:///Exit
            run=0;
            break;
        case SDL_MOUSEBUTTONDOWN: ///on mouse click
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                int x = event.button.x; /// mouse x position
                int y = event.button.y; /// mouse y position
                if(M==0)
                {
                    n=check(x,y);  ///check mouse position
//                    std::cout<<"Clicked N= " <<n<<std::endl;
                    if(n!=0)///Entering page 2
                    {
                        M=1;
                        m=1;
                    }
                    if(n==1)       ///play
                        run=2;
                    else if(n==6)  ///exit
                        run=0;
                }
                else if(M==1)
                {
                    m=check2(x,y);
                    if(m==2)///Back to main menu
                    {
                        M=0;
                        m=0;
                    }
                    else if(m>=3)
                    {
                        if(n==5&&m==5 ||n==4)
                            break;
                        else
                        {
                            M=2;
                            m+=3;
                            Mm=m;
                        }
                    }
                }
                else
                {
                    int mm=check2(x,y); ///check on clicked
                    if(mm==2) ///back to main menu
                    {
                        M=0;
                        m=0;
                        n=0;
                    }
                    else if(m>=3)
                    {
                        if(n==5&&m==5)
                            break;
                        else
                        {
                            M=2;
                            m=mm+3;
                            Mm=m;
                        }
                    }
                }
            }
            break;

        case SDL_MOUSEMOTION: ///mouse position
            int x = event.motion.x;
            int y = event.motion.y;
//            std::cout<<"mouse: x = "<<x<<" ,y = "<<y<<"\n";
            if(M==0)
            {
                m=0;
                n=check(x,y);
            }
            else if(M==1)
            {
                m=check2(x,y);
            }
            else if(M==2)
            {
                int mm=check2(x,y);
                if(mm==2)
                    m=2;
                else
                    m=Mm;
            }
            break;
        }


        switch(m)
        {
        case 0:///main menu
            switch(n)
            {
            case 0:
                menu.draw();
                break;
            case 1:
                playMenu.draw();
                break;
            case 2:
                instructionMenu.draw();
                break;
            case 3:
                levelMenu.draw();
                break;
            case 4:
                highscoreMenu.draw();
                break;
            case 5:
                settingMenu.draw();
                break;
            case 6:
                quitMenu.draw();
                break;
            }
            break;


        case 1:/// page 2
            switch(n)
            {
            case 2:
//                std::cout<<"case1->2"<<std::endl;
                instruction.draw();
                break;
            case 3:
                level.draw();
                break;
            case 4:
                highscore.draw();
                break;
            case 5:
                setting.draw();
                break;
            }
            break;

        case 2:///Back colored page 2
//            std::cout<<"case2"<<std::endl;
            switch(n)
            {
            case 2:
                instructionBack.draw();
                break;
            case 3:
                levelBack.draw();
                break;
            case 4:
                highscoreBack.draw();
                break;
            case 5:
                settingBack.draw();
                break;
            }
            break;




        case 3:///On page 2 (colored)
//            std::cout<<"case3"<<std::endl;
            if(n==3)
                levelEasy.draw();
            else if(n==5)
                settingOn.draw();
            else if(n==4)
                highscore.draw();
            else if(n==2)
                instruction.draw();
            break;
        case 4:
//            std::cout<<"case4"<<std::endl;
            if(n==3)
                levelMedium.draw();
            else if(n==5)
                settingOff.draw();
            else if(n==4)
                highscore.draw();
            else if(n==2)
                instruction.draw();
            break;
        case 5:
//            std::cout<<"case5"<<std::endl;
            if(n==3)
                levelHard.draw();
            else if(n==5)
                setting.draw();///not changed
            else if(n==4)
                highscore.draw();
            else if(n==2)
                instruction.draw();
            break;




        case 6:///On Page2 clicked
//        std::cout<<"case6  n= "<<n<<std::endl;
            if(n==3)
            {
                ///Level Easy
                v_level=5;
                levelEasy.draw();
            }
            else if(n==5)
            {

                soundFlag=true;
                sound.resumeMusic();///music On
                settingOn.draw();
            }
            else if(n==4)
                highscore.draw();
            else if(n==2)
                instruction.draw();
            break;
        case 7:
//            std::cout<<"case7"<<std::endl;
            if(n==3)
            {
                ///Level Medium
                v_level=4.5;
                levelMedium.draw();
            }
            else if(n==5)
            {
                soundFlag=false;
                sound.pauseMusic();///music off
                settingOff.draw();
            }
            else if(n==4)
                highscore.draw();
            else if(n==2)
                instruction.draw();
            break;
        case 8:
//            std::cout<<"case8"<<std::endl;
            if(n==3)
            {
                ///Level Hard
                v_level=5;
                speed=2;
                levelHard.draw();
            }
            else if(n==5)
                setting.draw();
            else if(n==4)
                highscore.draw();
            else if(n==2)
                instruction.draw();
            break;
        }
        SDL_RenderPresent(window._renderer);
        SDL_RenderClear(window._renderer);

//        std::cout<<"Run END=>run="<<run<<"   n="<<n<<"   ,m="<<m<<"   M="<<M<<"   Mm="<<Mm<<std::endl;

    }
    if(run==0)
        return 0;









    ///creating obstacles
    std::vector < std::pair<int,int> >vec;
    vec.push_back({0,240});
    vec.push_back({200,380});
    vec.push_back({300,480});
    vec.push_back({400,580});
    vec.push_back({490,700});
    time_t t;
    srand((unsigned) time(&t));

    int prob;
    for(int i=0; i<5; i++)
    {
        prob=rand()%5; ///random function
        std::cout<<"Prob "<<prob<<std::endl;
        a[i].pos_y1=vec[prob].first;
        a[i].pos_y2=vec[prob].second;
    }
    a[0].x=700;









    ///play
    bool f=false;
    int s=0,v=1;

    sound.stopMusic();
    heliSound.playMusic(-1);
    while(!window.isclosed())
    {
        if(v==0)
        {
            v=heli1.pollEvents(0);
            if(v==1)s=0;
            if(v==2)window.close();
        }
        else
        {
            s=heli1.pollEvents(1);
            if(s==1)v=0;
            if(s==2)window.close();
        }

        ///Game start/resume/pause   press-> s
        if(v==1)heli1._y++;



        heli2._x=heli1._x;
        heli2._y=heli1._y;


//        ///background
//        background.draw();


        int vv=0,ffff=0;
        for(int i=0; i<5; i++)
        {
            wall._x= a[0].x+vv;
            wall._y= a[i].pos_y1-Height;
            wall.draw();
            wall._y= a[i].pos_y2;
            wall.draw();



            ///collision
            if(heli1.collision(a[i].x+vv,a[i].pos_y1,a[i].pos_y2,heli1._x,heli1._y))
            {
                gameOver.draw();
                SDL_RenderPresent(window._renderer);
                SDL_RenderClear(window._renderer);
                window.close();
                soundFlag=false;
                ffff=1;
                heliSound.stopMusic();
                bomb.playMusic(1);
                SDL_Delay(1000);
                break;
            }
            if(ffff==1)
                break;

            vv+=450;
        }
        if(ffff==1)
            break;


        if(v==1)
            a[0].x-=speed;

        a[1].x=a[0].x+450;


        srand((unsigned) time(&t));

        if(a[0].x<1)
        {
            for(int i=1; i<5; i++)
            {
                a[i-1]=a[i];
            }

            prob=rand()%5; ///random function
            std::cout<<prob<<std::endl;
            a[4].pos_y1=vec[prob].first;
            a[4].pos_y2=vec[prob].second;
        }




        /// flying heli
        if(f==false)
        {
            heli1.draw();
            f=true;
        }
        else
        {
            heli2.draw();
            f=false;
        }

        window.clear();
        SDL_Delay(v_level);
    }
    bomb.stopMusic();


    int r=1;
    ev=evnt;
    while(r==1)
    {
//        std::cout<<"Running 1"<<std::endl;
        SDL_PollEvent(&ev);
        switch(ev.type)
        {
        case SDL_KEYDOWN:
            switch(ev.key.keysym.sym)
            {
            case SDLK_KP_ENTER: ///pressed KeyPad Enter
                r=0;
                goto stage1;///play again  (Go to MainMenu)
                break;
            }
            switch(ev.key.keysym.scancode)
            {
            case SDL_SCANCODE_RETURN:///pressed enter
//                std::cout<<"Pressed Enter"<<std::endl;
                r=0;
                goto stage1;///play again   (Go to MainMenu)
                break;
            }
            break;
        case SDL_QUIT:
            r=0;
            break;
        }
    }

    std::cout<<"Thank you! "<<std::endl;
    return 0;
}
