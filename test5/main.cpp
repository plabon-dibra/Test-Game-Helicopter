#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "Src\Window\Window.h"
#include "Src\Rect\Rect.h"
#include "Sound.h"
#include "Text.h"
#define ull unsigned long long int


///Decleared Functions
int  check(int x,int y,int Height,int Width);
int check2(int x, int y,int Height,int Width);
std::string toString(ull n);
ull toInteger(std::string s);



///Structure Decleared for creating Abstacles
struct abstacle
{
    int x,pos_y1,pos_y2;
} a[6];





int main(int argc,char *argv[])///main function
{
    std::ifstream ifile;
    std::ofstream ofile;
    std::string s_name="",myText[10],text2,name_easyHighScore="",name_mediumHighScore="",name_hardHighScore="";
    ull easyHighScore=0,mediumHighScore=0,hardHighScore=0,v_score=0;
    int indx=0,startTime,lastTime,Width=1366,Height=768;
    bool Quit=false;
    SDL_Event evnt,ev,event;









    ///Reading HighScore from text
    ifile.open("Assets/myHighScore.txt");
    if(ifile.fail())std::cout<<"Failed to Read HighScore.\n";
    else
    {
        while(getline(ifile,text2))
        {
            myText[indx++]=text2;
        }
    }
    ifile.close();










    ///Importing to Game ->Highscore
    if(indx!=0)
    {
        name_easyHighScore=myText[0];
        name_mediumHighScore=myText[1];
        name_hardHighScore=myText[2];


        ///converting to integer from string value
        easyHighScore=toInteger(myText[3]);
        mediumHighScore=toInteger(myText[4]);
        hardHighScore=toInteger(myText[5]);
    }

//    std::cout<<"Easy    : "<<name_easyHighScore<<"   "<<easyHighScore<<std::endl;
//    std::cout<<"Medium  : "<<name_mediumHighScore<<"   "<<mediumHighScore<<std::endl;
//    std::cout<<"Hard    : "<<name_hardHighScore<<"   "<<hardHighScore<<std::endl;








    Window window("Helicopter Game",Width,Height);   ///initialize window







    ///getting images
    Rect heli1=Rect(window,100,100,HeliWidth,HeliHeight,"Assets/Images/heli1.png");
    Rect heli2=Rect(window,100,100,HeliWidth,HeliHeight,"Assets/Images/heli2.png");

    Rect welcome=Rect(window,0,0,Width,Height,"Assets/Images/Welcome.png");
//    Rect background=Rect(window,0,0,Width,Height,"Assets/Images/back.png");
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







    ///text
    Text t_highScore,t_score,name,message1;
    Text t_easy_highScore,t_Medium_highScore,t_Hard_highScore,t_easy,t_medium,t_hard;


    message1.createText(window,"Enter Your Name: ",36);
    message1.drawText(window,Width/5,Height/2);   ///Displaying massage in window
    SDL_RenderPresent(window._renderer);
    SDL_RenderClear(window._renderer);








    ///Getting Name
    SDL_Event e;
    SDL_StartTextInput();
    bool name_is_running=true;
    while(name_is_running&&!Quit)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                Quit=true;
                break;
            case SDL_TEXTINPUT:
                s_name+=e.text.text;
//                std::cout<<s_name<<std::endl;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.scancode)
                {
                case SDL_SCANCODE_BACKSPACE:///Pressed BackSpace
                    if(!s_name.empty())
                        s_name.pop_back();
                    break;
                case SDL_SCANCODE_RETURN:///Pressed Enter
                    if(!s_name.empty())
                        name_is_running=false;
                    break;
                }
            }
        }
        message1.drawText(window,Width/5,Height/2);///Displaying Massage
        if(!s_name.empty())
        {
            name.createText(window,s_name,36);
            name.drawText(window,Width/5+350,Height/2);///Displaing Name
        }
        SDL_RenderPresent(window._renderer);
        SDL_RenderClear(window._renderer);
    }
    SDL_StopTextInput();
















    /// Sound
    bool soundFlag=false;
    Sound sound,heliSound,bomb;
    sound.addMusic("Assets/Sounds/backsound.mp3"); ///addding music
    bomb.addMusic("Assets/Sounds/bomb.mp3"); ///addding music
    heliSound.addMusic("Assets/Sounds/heliSound.mp3"); ///addding music











    ///Displaying Welcome image
    if(!Quit)
    {
        welcome.draw();   ///welcome image display
        SDL_RenderPresent(window._renderer);
        SDL_RenderClear(window._renderer);
        SDL_Delay(2000);///2 seconds Delay
    }






    int speed=2,v_level=1,v_up=6,v_down=4;///initially Medium Level
    float v_delay=5;  ///initially Delay 5 ms for Medium Level


stage1:
    sound.playMusic(-1);  ///infinite loop
    if(!soundFlag)
        sound.pauseMusic();   ///paused music


    window._closed=0;
    heli1._y=Height/3;








    ///Creating Text to show Highscore
    std::string  s1="Easy         : "+name_easyHighScore;
    std::string  s2="Medium   : "+name_mediumHighScore;
    std::string  s3="Hard        : "+name_hardHighScore;

    t_easy.createText(window,s1,50);
    t_medium.createText(window,s2,50);
    t_hard.createText(window,s3,50);
    t_easy_highScore.createText(window,toString(easyHighScore),50);
    t_Medium_highScore.createText(window,toString(mediumHighScore),50);
    t_Hard_highScore.createText(window,toString(hardHighScore),50);








    void t_highScoreDraw(const Window &window,Text &t_easy,Text &t_medium,Text &t_hard,Text &t_easy_highScore,Text &t_Medium_highScore,Text &t_Hard_highScore);///decleared function






/// test
//    t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
//    SDL_RenderPresent(window._renderer);
//    SDL_RenderClear(window._renderer);
//    SDL_Delay(5000);











    ///Menu Choice
    int run =1,n=0,m=0,M=0,Mm=0;
    event=evnt;
    while(run==1&&!Quit)
    {
//        std::cout<<"Run END=>run="<<run<<"   n="<<n<<"   ,m="<<m<<"   M="<<M<<"   Mm="<<Mm<<std::endl;
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:///Exit
            Quit=true;
            break;
        case SDL_MOUSEBUTTONDOWN: ///on mouse click
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                int x = event.button.x; /// mouse x position
                int y = event.button.y; /// mouse y position
                if(M==0)
                {
                    n=check(x,y,Height,Width);  ///check mouse position
//                    std::cout<<"Clicked N= " <<n<<std::endl;
                    if(n!=0)///Entering page 2
                    {
                        M=1;
                        m=1;
                    }
                    if(n==1)run=2;///play
                    else if(n==6)Quit=true;  ///exit
                }
                else if(M==1)
                {
                    m=check2(x,y,Height,Width);
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
                    int mm=check2(x,y,Height,Width); ///check on clicked
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
                n=check(x,y,Height,Width);
            }
            else if(M==1)m=check2(x,y,Height,Width);
            else if(M==2)
            {
                int mm=check2(x,y,Height,Width);
                if(mm==2)m=2;
                else m=Mm;
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
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
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
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
                break;
            case 5:
                settingBack.draw();
                break;
            }
            break;




        case 3:///On page 2 (colored)
//            std::cout<<"case3"<<std::endl;
            if(n==3)levelEasy.draw();
            else if(n==5)settingOn.draw();
            else if(n==4)
            {
                highscore.draw();
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
            }
            else if(n==2)instruction.draw();

            break;
        case 4:
//            std::cout<<"case4"<<std::endl;
            if(n==3)
                levelMedium.draw();
            else if(n==5)
                settingOff.draw();
            else if(n==4)
            {
                highscore.draw();
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
            }
            else if(n==2)
                instruction.draw();
            break;
        case 5:
//            std::cout<<"case5"<<std::endl;
            if(n==3)levelHard.draw();
            else if(n==5)setting.draw();///not changed
            else if(n==4)
            {
                highscore.draw();
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
            }
            else if(n==2)instruction.draw();

            break;



        case 6:///On Page2 clicked
//        std::cout<<"case6  n= "<<n<<std::endl;
            if(n==3)
            {
                ///Level Easy
                v_level=0;
                v_delay=6;
                speed=2;
                v_up=6;
                v_down=4;
                levelEasy.draw();
            }
            else if(n==5)
            {
                soundFlag=true;
                sound.resumeMusic();///music On
                settingOn.draw();
            }
            else if(n==4)
            {
                highscore.draw();
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
            }
            else if(n==2)instruction.draw();

            break;
        case 7:
//            std::cout<<"case7"<<std::endl;
            if(n==3)
            {
                ///Level Medium
                v_level=1;
                v_delay=5;
                speed=2;
                v_up=6;
                v_down=4;
                levelMedium.draw();
            }
            else if(n==5)
            {
                soundFlag=false;
                sound.pauseMusic();///music off
                settingOff.draw();
            }
            else if(n==4)
            {
                highscore.draw();
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
            }
            else if(n==2)instruction.draw();

            break;
        case 8:
//            std::cout<<"case8"<<std::endl;
            if(n==3)
            {
                ///Level Hard
                v_up=6;
                v_down=4;
                v_level=2;
                v_delay=4;
                speed=2;
                levelHard.draw();
            }
            else if(n==5)setting.draw();
            else if(n==4)
            {
                highscore.draw();
                t_highScoreDraw(window,t_easy,t_medium,t_hard,t_easy_highScore,t_Medium_highScore,t_Hard_highScore);
            }
            else if(n==2)instruction.draw();


            break;
        }
        SDL_RenderPresent(window._renderer);
        SDL_RenderClear(window._renderer);

//        std::cout<<"Run END=>run="<<run<<"   n="<<n<<"   ,m="<<m<<"   M="<<M<<"   Mm="<<Mm<<std::endl;
    }










    ///creating obstacles
    std::vector < std::pair<int,int> >vec;
    vec.push_back({0,220});
    vec.push_back({Height/3-90,Height/3+90});
    vec.push_back({Height/2-90,Height/2+90});
    vec.push_back({Height-300,Height-120});
    vec.push_back({Height-220,Height});
    time_t t;
    srand((unsigned) time(&t));///starting Random Function from t time.

    int prob;
    for(int i=0; i<5; i++)
    {
        prob=rand()%5; ///random function
//        std::cout<<"Prob "<<prob<<std::endl;
        a[i].pos_y1=vec[prob].first;
        a[i].pos_y2=vec[prob].second;
    }
    a[0].x=Width/2 - 100;










    bool f=false,score_flag=true;;
    heli1.btn[0]=0;
    heli1.btn[1]=0;
    int s=0,v=1,wall_distance=450;
    v_score=0;





    if(v_level==1)a[0].x=Width/2+200;

    if(v_level==2)
    {
        wall_distance=460;
        a[0].x=Width/2+200;
    }











    ///Getting Ready to Play
    int countFly=0;
    if(!Quit)
    {
        if(soundFlag)
        {
            sound.stopMusic();
            heliSound.playMusic(-1);///helicopter sound
        }

        while(!window.isclosed())///play
        {
            if(v==0)
            {
                v=heli1.pollEvents(0);
                if(v==1)s=0;
                if(v==2)
                {
                    window.close();
                    Quit=true;
                    window.clear();
                    break;
                }
            }
            else
            {
                s=heli1.pollEvents(1);
                if(s==1)v=0;
                if(s==2)
                {
                    Quit=true;
                    window.close();
                    window.clear();
                    break;
                }
            }

            if(Quit==true)
                break;

            ///Game start/resume/pause   press-> s
            if(v==1)heli1._y++;









            /// flying heli
            if(f==false)
            {
                heli1.draw();
                countFly++;
                if(countFly==18)
                {
                    f=true;
                    countFly=0;
                }
            }
            else
            {
                heli2.draw();
                countFly++;
                if(countFly==18)
                {
                    f=false;
                    countFly=0;
                }
            }










            ///By controlling keyboard button UP and Down
            if(v==1&&heli1.btn[0])heli1._y-=v_up;
            else if(v==1&&heli1.btn[1])heli1._y+=v_down;





            heli2._x=heli1._x;
            heli2._y=heli1._y;





            ///Update Score
            if(heli1._x>a[0].x&&score_flag==true)
            {
                v_score++;
                score_flag=false;
            }







            ///Moving Wall
            int vv=0,ffff=0;
            for(int i=0; i<5; i++)
            {
                wall._x= a[0].x+vv;
                wall._y= a[i].pos_y1-Height;
                wall.draw();
                wall._y= a[i].pos_y2;
                wall.draw();




                ///collision
                if(heli1.collision(a[i].x+vv,a[i].pos_y1,a[i].pos_y2,heli1._x,heli1._y,Height))
                {
                    switch(v_level)
                    {
                    case 0:
                        if(easyHighScore<v_score)
                        {
                            easyHighScore=v_score;
                            name_easyHighScore=s_name;
                        }
                        break;
                    case 1:
                        if(mediumHighScore<v_score)
                        {
                            mediumHighScore=v_score;
                            name_mediumHighScore=s_name;
                        }
                        break;
                    case 2:
                        if(hardHighScore<v_score)
                        {
                            hardHighScore=v_score;
                            name_hardHighScore=s_name;
                        }
                        break;
                    }
                    gameOver.draw();
                    t_score.drawText(window,Width/2-50,80);
                    SDL_RenderPresent(window._renderer);
                    SDL_RenderClear(window._renderer);
                    window.close();
                    ffff=1;
                    if(soundFlag)
                    {
                        heliSound.stopMusic();
                        bomb.playMusic(1);
                    }
                    SDL_Delay(1000);
                    break;
                }

                if(ffff==1)break;

                vv+=wall_distance;
            }
            if(ffff==1)break;



            if(v==1)a[0].x-=speed;


            a[1].x=a[0].x+wall_distance;


            srand((unsigned) time(&t));







            ///Creating New Random Wall
            if(a[0].x<1)
            {
                for(int i=1; i<5; i++)a[i-1]=a[i];


                prob=rand()%5; ///random function
//              std::cout<<prob<<std::endl;
                a[4].pos_y1=vec[prob].first;
                a[4].pos_y2=vec[prob].second;

                score_flag=true;
            }







            ///Displaying Score
            std::string s_score="Score : ";
            s_score+=toString(v_score);
            t_score.createText(window,s_score,50);
            t_score.drawText(window,Width/2-50,55);




            window.clear();
            SDL_Delay(v_delay);
        }
        if(soundFlag)
           bomb.stopMusic();
    }










    ///By Pressing 'ENTER' to return Back to Main Menu
    int r=1;
    ev=evnt;
    while(r==1&&!Quit)
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
            Quit=true;
            break;
        }
    }











    ///Saving Current Highscore
    ofile.open("Assets/myHighScore.txt");
    if(ofile.fail())
    {
        std::cout<<"Failed to save file.\n";
    }
    else
    {
        std::cout<<"Saved."<<std::endl;
        ofile<<name_easyHighScore<<"\n"<<name_mediumHighScore<<"\n"<<name_hardHighScore<<"\n";
        ofile<<easyHighScore<<"\n"<<mediumHighScore<<"\n"<<hardHighScore<<"\n";
    }
    ofile.close();






    std::cout<<"Thank you! "<<std::endl;
    return 0;
}




void t_highScoreDraw(const Window &window,Text &t_easy,Text &t_medium,Text &t_hard,Text &t_easy_highScore,Text &t_Medium_highScore,Text &t_Hard_highScore)
{
    t_easy.drawText(window,200,300);
    t_medium.drawText(window,200,450);
    t_hard.drawText(window,200,600);

    t_easy_highScore.drawText(window,900,300);
    t_Medium_highScore.drawText(window,900,450);
    t_Hard_highScore.drawText(window,900,600);

    return ;
}




int  check(int x,int y,int Height,int Width)
{
    int  n=0,x1=Width/2 - 150;
    int x2=Width/2 + 200;
    if(x>=x1&&x<=x2)
    {
        if(y>=265&&y<=325)n=1;       //265-325
        else if(y>=360&&y<=410)n=2;  //360-410
        else if(y>=450&&y<=500)n=3;  //450-500
        else if(y>=525&&y<=575)n=4;  //525-575
        else if(y>=605&&y<=655)n=5;  //605-655
        else if(y>=685&&y<=735)n=6;  //685-735
    }
    return n;
}




int check2(int x, int y,int Height,int Width)
{
    int m=1,x1=Width/2 - 150,x2=Width/2 + 200;
    if(x>=Width-270&&y>=Height-125)m=2;  ///310,435,570----325,465
    else if(x>=x1&&x<=x2 && y>=305&&y<=390)m=3;
    else if(x>=x1&&x<=x2 && y>=435&&y<=525)m=4;
    else if(x>=x1&&x<=x2 && y>=570&&y<=625)m=5;

    return m;
}



std::string toString(ull n)
{
    std::string s="";
    if(n==0)return "0";
    while(n!=0)
    {
        int m=n%10;
        switch(m)
        {
        case 0:
            s+="0";
            break;
        case 1:
            s+="1";
            break;
        case 2:
            s+="2";
            break;
        case 3:
            s+="3";
            break;
        case 4:
            s+="4";
            break;
        case 5:
            s+="5";
            break;
        case 6:
            s+="6";
            break;
        case 7:
            s+="7";
            break;
        case 8:
            s+="8";
            break;
        case 9:
            s+="9";
            break;
        }
        n/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}



ull toInteger(std::string s)
{
    ull n=0,m=0;
    for(int i=0; i<s.size(); i++)
    {
        switch(s[i])
        {
        case '0':
            m=0;
            break;
        case '1':
            m=1;
            break;
        case '2':
            m=2;
            break;
        case '3':
            m=3;
            break;
        case '4':
            m=4;
            break;
        case '5':
            m=5;
            break;
        case '6':
            m=6;
            break;
        case '7':
            m=7;
            break;
        case '8':
            m=8;
            break;
        case '9':
            m=9;
            break;
        }
        n=n*10+m;
    }
    return n;
}


