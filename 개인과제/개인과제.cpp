#include <iostream>
#include <bangtal.h>
#include <ctime>

using namespace bangtal;
using namespace std;

class character
{
private:
    int hp=0;
    int atk=0;
    string name="name";
public:
    void setHp(int h) { hp = h; }
    void setAtk(int a) { hp = a; }
    void hit(int k) { hp = hp - k; }
    character(const string& n) : name(n) { };
};


int main()
{
    srand((unsigned)time(0));

    int hp = 4;                 //플레이어 hp 
    int atk = 1;                //플레이어 atk

    int mobhp = 3;              //몬스터 hp

    character p1("player1");
    p1.setHp(1);
    p1.setAtk(1);

    character mob("monster");
    mob.setHp(2);
    mob.setAtk(1);

    int i = 0;                       //i가 0일때는 몬스터가 멀리 있는경우, i=1일때는 몬스터와 싸우고 있는 경우, -1은 몬스터가 없을때
    int b = 0;                    // boots =0 no boots, boots=1 already have boots
    int d = 0;                    //d=0 no dodge d=1 dodge in progress
    int count = 0;                 //num of monsters killed
    int p = -1;                     //-1 not found 0 far 1 nearby 2 passed
    int numPotion = 0;                  // number of potions

    auto scene1 = Scene::create("Stage 1", "Images/nightsky.png");
    auto GameOver = Scene::create("Game Over", "Images/GameOver.png");

   auto Lwall = Object::create("Images/LeftWall.png", scene1, 0, 0);
    Lwall->setScale(2.5);

    auto Lwall2 = Object::create("Images/LeftWall.png", scene1, 275, 267);
    Lwall2->setScale(0.75);

    auto Rwall = Object::create("Images/RightWall.png", scene1, 1010, 20);
    Rwall->setScale(2.5);

    auto Rwall2 = Object::create("Images/RightWall.png", scene1, 927, 277);
    Rwall2->setScale(0.75); 

    auto atkButton = Object::create("Images/attack.png", scene1, 1050, 50);
    atkButton->setScale(0.5);

    auto goButton = Object::create("Images/go.png", scene1, 950, 50);
    goButton->setScale(0.5);

    auto MHeart1 = Object::create("Images/heart.png", scene1, 570, 500);
    MHeart1->setScale(0.07);
    MHeart1->hide();

    auto MHeart2 = Object::create("Images/heart.png", scene1, 605, 500);
    MHeart2->setScale(0.07);
    MHeart2->hide();

    auto MHeart3 = Object::create("Images/heart.png", scene1, 640, 500);
    MHeart3->setScale(0.07);
    MHeart3->hide();

    auto MHeart4 = Object::create("Images/heart.png", scene1, 675, 500);
    MHeart4->setScale(0.07);
    MHeart4->hide();

    auto skeleton = Object::create("Images/skeleton.png", scene1, 500, 300);
    skeleton->setScale(2);
    MHeart1->show();                             //몬스터 하트 세팅                        
    MHeart2->show();
    MHeart3->show();

    auto Heart1 = Object::create("Images/heart.png", scene1, 50, 10);
    Heart1->setScale(0.1);

    auto Heart2 = Object::create("Images/heart.png", scene1, 100, 10);
    Heart2->setScale(0.1);

    auto Heart3 = Object::create("Images/heart.png", scene1, 150, 10);
    Heart3->setScale(0.1);

    auto Heart4 = Object::create("Images/heart.png", scene1, 200, 10);
    Heart4->setScale(0.1);

    auto portal = Object::create("Images/portal.png", scene1, 910, 335);
    portal->setScale(0.2);
    portal->hide();

    auto boots = Object::create("Images/boots.png", scene1, 630, 105);
    boots->setScale(0.2);
    boots->hide();

    auto dodge = Object::create("Images/dodge.png", scene1, 950, 145);
    dodge->setScale(0.15);
    dodge->hide();

    auto potion = Object::create("Images/potion.png", scene1, 300, 10);
    potion->setScale(0.1);
    potion->hide();

    auto timer = Timer::create(0.1);

    time_t start_time;
    timer->start();
    start_time = time(NULL);


    boots->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
        {
            boots->pick();
            dodge->show();
            hp = 3;
            Heart1->show();
            Heart2->show();
            Heart3->show();
            showMessage("이제 회피 버튼을 사용할 수 있습니다.");
            b = 1;
            return true;
        });

    goButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
        {
            
            if (p == 1)
            {
                portal->hide();                                   //포탈 지나침 
                portal->locate(scene1, 910, 335);
                portal->setScale(0.2);
                p = -1;
            }
            if (p == 0)
            {
                portal->locate(scene1, 1010, 235);
                portal->setScale(0.3);
                p = 1;
            }
            if (i == 0)
            {
                skeleton->setScale(4);                     //몬스터 커짐
                skeleton->locate(scene1, 350, 150);

                showMessage("몬스터가 공격합니다!");

                if (hp == 4 && d==0)                                 //플레이어 hp 시스템
                {
                    Heart4->hide();
                    hp = hp - 1;
                    i = 1;

                }
                else if (hp == 3 && d == 0)
                {
                    Heart3->hide();
                    hp = hp - 1;
                    i = 1;

                }
                else if (hp == 2 && d == 0)
                {
                    Heart2->hide();
                    hp = hp - 1;
                    i = 1;

                }
                else if (hp == 1 && d == 0)
                {
                    Heart1->hide();
                    showMessage("체력이 더 이상 없습니다!");
                    hp = hp - 1;
                    i = 1;

                }
                else if (hp==0 && d == 0)
                {
                    GameOver->enter();
                    showMessage("몬스터에게 죽었습니다.");
                    i = 1;

                }

                if (d == 1)
                {
                        showMessage("도망치는데 성공했습니다!");
                        skeleton->hide();
                        MHeart1->hide();
                        MHeart2->hide();
                        MHeart3->hide();
                        i = -1;
                        d = 0;
                }
                return true;
            }

            if (i == -1)
            {
                showMessage("앞으로 움직입니다.");
                switch (rand() % 4)
                {
                case 0:
                    showMessage("멀리서 몬스터가 보입니다");
                    skeleton->show();
                    mobhp = 3;
                    MHeart1->show();                             //몬스터 하트 세팅                        
                    MHeart2->show();
                    MHeart3->show();
                    i = 0;
                case 1:
                    if (b == 0)
                    {
                        showMessage("날개달린 신발이 보입니다");                          //문 만들고 scene2 새로운 몬스터 및 맵 만들기 (어떤 아이템 만들까?)
                        boots->show();
                    }
                case 2:
                    if (p==-1)
                    {
                        showMessage("포털이 보입니다");
                        portal->show();
                        p = 0;
                    }
                case 3:
                    switch (rand() % 10)
                    {
                    case 0:
                        break;
                    case 1:
                        showMessage("포션을 찾았다! 위급할때 사용하자");
                        potion->show();
                        numPotion = numPotion + 1;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                        break;
                    case 9:
                        break;
                    }
                }

            }
        });

    atkButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
        {
            
            if (i == 1)
            {
                skeleton->locate(scene1, 380, 170);                          //몬스터 후퇴
                skeleton->setScale(3.5);

                showMessage("몬스터를 공격했습니다!");
                
                i = 0;
                if (mobhp == 3)                                 //몬스터 hp 시스템
                {
                    MHeart3->hide();
                    mobhp = mobhp - atk;
                }
                else if (mobhp == 2)
                {
                    MHeart3->hide();
                    MHeart2->hide();
                    mobhp = mobhp - atk;
                }
                else if (mobhp <= 1)
                {
                    MHeart3->hide();
                    MHeart2->hide();
                    MHeart1->hide();
                    mobhp = mobhp - atk;
                    skeleton->hide();
                    showMessage("몬스터를 처치했습니다!");
                    //atk = atk + 1;
                    count++;
                    i = -1;
                }
              
                return true;
            }
        });

    dodge->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
        {

            if (i == 1)
            {
                skeleton->locate(scene1, 380, 170);                          //몬스터 후퇴
                skeleton->setScale(3.5);

                showMessage("회피할 준비를 합니다!");

                i = 0;
                d = 1;
                return true;
            }

           
        });

    portal->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
        {
            if (p == 0)
            {
                showMessage("포탈이 너무 멀리 있습니다. 좀 더 가까이 가보세요");
            }
            if (p == 1)
            {
                auto end_time = time(NULL);
                int title = 0;
                title = difftime(end_time, start_time) / count - 3;
                string result = "결과:" + to_string(title) + "등급";
                if (title == 5)
                {
                    string result = "결과:" + to_string(title)+"S랭크";
                }
                else
                {
                    string result = "결과:" + to_string(title)+"S랭크 달성 실패";
                }

                string print = to_string(count) + "마리 죽이고 탈출하는데" + to_string(difftime(end_time, start_time)) +"초 걸림." + result.c_str();
                showMessage(print.c_str());
                GameOver->enter();
            }
            return true;
        });

    potion->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
        {
            hp = 3;
            Heart1->show();
            Heart2->show();
            Heart3->show();
            showMessage("체력이 회복되었다!");
            numPotion = numPotion - 1;
            potion->hide();
            return true;
        });

    startGame(scene1);
}