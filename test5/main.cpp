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
    Rect heli1=Rect(window,100,100,160,80,"Assets/Images/heli1.png");
    Rect heli2=Rect(window,100,100,160,80,"Assets/Images/heli2.png");

    Rect welcome=Rect(window,0,0,Width,Height,"Assets/Images/Welcome.png");
    Rect background=Rect(window,0,0,Width,Height,"Assets/Images/back.png");

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
    Sound sound;
    sound.addMusic("Assets/Sounds/backsound.mp3");
    sound.playMusic(-1);  ///infinite loop
    sound.pauseMusic();   ///paused music




    welcome.draw();   ///welcome image display
    SDL_RenderPresent(window._renderer);
    SDL_RenderClear(window._renderer);
    SDL_Delay(2000);///2 second Delay



    int run =1,n=0,m=0,M=0,Mm=0;
    float v_level=LEVEL_EASY;  ///initially  Easy level

    SDL_Event event;
    while(run==1)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
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
                    if(n!=0)
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
                    if(m==2)
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
                v_level=LEVEL_EASY;
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
                v_level=LEVEL_MEDIUM;
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
                v_level=LEVEL_HARD;
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
    }


    if(v_level==LEVEL_EASY)
        heli1.heli_d=100;
    else if(v_level==LEVEL_MEDIUM)
        heli1.heli_d=130;
    else
        heli1.heli_d=150;


    if(run==0)
        return 0;
    int s=0,v=0;









    ///creating obstacles
    std::vector < std::pair<int,int> >vec;
    vec.push_back({0,120});
    vec.push_back({150,320});
    vec.push_back({290,410});
    vec.push_back({430,550});
    vec.push_back({580,700});
    time_t t;
    srand((unsigned) time(&t));

    int prob;
    for(int i=0; i<5; i++)
    {
        prob=rand()%5;
        a[i].pos_y1=vec[prob].first;
        a[i].pos_y2=vec[prob].second;
    }
    a[0].x=600;









    ///play
    bool f=false;
    while(!window.isclosed())
    {
        if(v==0)
        {
            v=heli1.pollEvents();
            if(v==1)s=0;
            if(v==2)window.close();
        }
        else
        {
            s=heli1.pollEvents();
            if(s==1)v=0;
            if(s==2)window.close();
        }

        ///Game start/resume/pause   press-> s
        if(v==true)heli1._y++;



        heli2._x=heli1._x;
        heli2._y=heli1._y;



        ///collision
        if(heli1.collision(0,0,0,heli1._x,heli1._y))
        {
            window.close();
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


    std::cout<<"Thank you!"<<std::endl;
    return 0;
}
