#include <iostream>
#include "AllegroBase.h"
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include "Circle.h"
#include "Square.h"
#include "SquareWithCircle.h"
#include "CollisionManager.h"
#include "SizeableSquare.h"
#include "SizeableCircle.h"
#include "MoveableTriangle.h"
#include "FigureFactory.h"
#include <fstream>


const int FPS = 60;
const int SCREEN_W = 1800;
const int SCREEN_H = 1200;
const float TRIANGLE_SIZE = 50;

const int MAX = 50;
const int START = 40;
class ScreenSaver
{
private:
    std::list <Figure*> fArray;
    std::ofstream of;

public:

    static ScreenSaver& getInstance()
    {
        static ScreenSaver instance;

        return instance;
    }

    ScreenSaver(ScreenSaver const&) = delete;
    void operator=(ScreenSaver const&) = delete;

    void Draw()
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        std::for_each(std::begin(fArray), std::end(fArray), [=](Figure* p) { p->Draw(); });
        al_flip_display();
    }

    void Next()
    {
        std::for_each(std::begin(fArray), std::end(fArray), [=](Figure* p) { p->Move(); p->speed.x *= 1.0001; p->speed.y *= 1.0001; });
        CollisionManager::getInstance().Update();
    }
    
    void Add(Figure *f)
    {
        fArray.push_back(f);
        CollisionManager::getInstance().Add(*f);
    }

    void Reset()
    {
        std::for_each(std::begin(fArray), std::end(fArray), [=](Figure* p) { if (p != &MoveableTriangle::getInstance()) delete p; });
        fArray.clear();
        CollisionManager::getInstance().Reset();
    }

    void PrintAll()
    {
        std::for_each(std::begin(fArray), std::end(fArray), [=](Figure* p) { std::cout << p->ToString() << std::endl; });
    }

    void SaveToFile()
    {
        of.open("C:\\Users\\user\\Desktop\\last_save.txt", std::ios::out | std::ios::trunc);

        std::for_each(std::begin(fArray), std::end(fArray), [=](Figure* p) { of << p->ToString() << std::endl; });

        of.close();
    }
    

private:
    ScreenSaver()
    {
        Reset();
    }
    ~ScreenSaver()
    {
        Reset();
    }

};

class AllegroApp : public AllegroBase
{
private:
    int lastPress;

public:
    
    //C : \Users\user\Desktop\

    virtual void Fps()
    {
        if (!MoveableTriangle::getInstance().IsAlive())
        {
            Reset();
            std::cout << "Game Over" << std::endl;
            return;
            
        }
        ScreenSaver::getInstance().Next();

        double dx = 0, dy = 0;
        if (IsPressed(ALLEGRO_KEY_UP))
        {
            dy = -100;
        }
        if (IsPressed(ALLEGRO_KEY_DOWN))
        {
            dy = +100;
        }
        if (IsPressed(ALLEGRO_KEY_LEFT))
        {
            dx = -100;
        }
        if (IsPressed(ALLEGRO_KEY_RIGHT))
        {
            dx = +100;
        }
        if (IsPressed(ALLEGRO_KEY_LSHIFT))
        {
            dy *= 2;
            dx *= 2;
        }
        if (IsPressed(ALLEGRO_KEY_SPACE) && lastPress == 0)
        {
            Reset();
            lastPress = 60;
            return;
        }
        if (IsPressed(ALLEGRO_KEY_P) && lastPress == 0)
        {
            ScreenSaver::getInstance().PrintAll();
            lastPress = 60;
        }
        /*if (IsPressed(ALLEGRO_KEY_W) && lastPress == 0)
        {
            std::string tmp;

            std::cin >> tmp;
            try 
            { 
                ScreenSaver::getInstance().Add(FigureFactory::getInstance().CreateFromString(tmp));
            }
            catch (...) 
            { 
                std::cout << "Invalid String" << std::endl;
            }
            

            lastPress = 60;
        }*/
        if (IsPressed(ALLEGRO_KEY_L) && lastPress == 0)
        {
            std::cout << CreateFileDialog() << std::endl;
            pressedKeys_[12] = false;
            lastPress = 60;
        }
        if (IsPressed(ALLEGRO_KEY_S) && lastPress == 0)
        {
            ScreenSaver::getInstance().SaveToFile();
        }

        MoveableTriangle::getInstance().MoveBy(dx, dy);
        if (lastPress > 0)
        {
            lastPress--;
        }
    }

    virtual void Draw()
    {
        ScreenSaver::getInstance().Draw();
    }


    virtual void FileOpenEvent(std::string a)
    {

        lastPress = 0;
        ScreenSaver::getInstance().Reset();
        FigureFactory::getInstance().Init(Point(0, 0), Point(SCREEN_W, SCREEN_H), FPS);

        MoveableTriangle::getInstance().Init(Point(0, 0),
            Point(SCREEN_W, SCREEN_H),
            Point(SCREEN_W / 2.0f, SCREEN_H / 2.0f),
            Point(TRIANGLE_SIZE, sqrt((TRIANGLE_SIZE * TRIANGLE_SIZE) - ((TRIANGLE_SIZE / 2.0f) * (TRIANGLE_SIZE / 2.0f)))),
            1 / 60.0 * 1000,
            5,
            0,
            0,
            MoveableTriangle::getInstance().bestScore, 5);

        std::ifstream fs(a);
        std::string tmpString;
        int i = 1;
        if (fs.is_open())
        {
            while (std::getline(fs, tmpString))
            {
                try
                {
                    ScreenSaver::getInstance().Add(FigureFactory::getInstance().CreateFromString(tmpString));
                }
                catch (...)
                {
                    std::cout << "Invalid String at line : " << i << std::endl;
                }
                i++;
            }
            fs.close();
        }
        else std::cout << "Unable to open file";
    }


    void Reset()
    {
        lastPress = 0;
        ScreenSaver::getInstance().Reset();
        FigureFactory::getInstance().Init(Point(0, 0), Point(SCREEN_W, SCREEN_H), FPS);

        MoveableTriangle::getInstance().Init(Point(0, 0), 
            Point(SCREEN_W, SCREEN_H), 
            Point(SCREEN_W / 2.0f, SCREEN_H / 2.0f), 
            Point(TRIANGLE_SIZE, sqrt((TRIANGLE_SIZE * TRIANGLE_SIZE) - ((TRIANGLE_SIZE / 2.0f) * (TRIANGLE_SIZE / 2.0f)))), 
            1 / 60.0 * 1000, 
            5, 
            0, 
            0, 
            MoveableTriangle::getInstance().bestScore, 5);

        ScreenSaver::getInstance().Add(&MoveableTriangle::getInstance());

        for (int i = 0; i < START; ++i)
        {
            int randd = rand() % 5;

            int randSide = rand() % 50 + 30;

            switch (randd) {
            case 0:
                ScreenSaver::getInstance().Add(FigureFactory::getInstance().CreateRandomCircle());
                break;
            case 1:
                ScreenSaver::getInstance().Add(FigureFactory::getInstance().CreateRandomSquare());
                break;
            case 2:
                ScreenSaver::getInstance().Add(FigureFactory::getInstance().CreateRandomSquareWithCircle());
                break;
            case 3:
                ScreenSaver::getInstance().Add(FigureFactory::getInstance().CreateRandomSizableSquare());
                break;
            case 4:
                ScreenSaver::getInstance().Add(FigureFactory::getInstance().CreateRandomSizableCircle());
                break;
            }
        }
    }


    AllegroApp() :
        AllegroBase()
    {
        Reset();
    }

    virtual ~AllegroApp()
    {

    }


    


};

int main(int argc, char** argv)
{

    srand(time(NULL));
    AllegroApp ap;
    if (!ap.Init(SCREEN_W, SCREEN_H, FPS))
    {
        return 1;
    }

    ap.Run();
    

    return 0;
}
