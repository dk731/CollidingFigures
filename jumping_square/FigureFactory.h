#pragma once
#include "Figure.h"
#include "Square.h"
#include "Circle.h"
#include "SizeableCircle.h"
#include "SizeableSquare.h"
#include "SquareWithCircle.h"
#include "MoveableTriangle.h"

class FigureFactory 
{

public:
    Point p1, p2, randSpeed;
    int time_step;
    int randSide;
    RgbColor randomColor;

    struct FigureArgs
    {
        Point pos, speed, p1, p2, size;
        float mass;
        int time_step;
        RgbColor color;
    } fA;

    struct SizeableFigureArgs
    {
        Point step_destination, start_side, decc;
        bool curently_in_step, bol;
        int cur_step_time, step_time;
        float size_icc;
        
    } sFa;


    struct MoveableTriangleArgs
    {
        int health, imune, score, bestScore, startHp;
    } mTa;

    static FigureFactory& getInstance()
    {
        static FigureFactory    instance; 
                           
        return instance;
    }

    FigureFactory(FigureFactory const&) = delete;
    void operator=(FigureFactory const&) = delete;

    Figure* CreateRandomSquare();
    Figure* CreateRandomCircle();
    Figure* CreateRandomSquareWithCircle();
    Figure* CreateRandomSizableSquare();
    Figure* CreateRandomSizableCircle();
    Point ReadPoint(std::string s);
    RgbColor ReadColor(std::string s);

    void ReadFigure(std::string s);
    void ReadSizeableFigure(std::string s);
    void ReadMoveableTriangle(std::string s);


    

    void GenerateRandSpeed(int max_speed, int minSpeed, int size, int min_size);

    void Init(Point s1, Point s2, int fps);

    Figure* CreateFromString(std::string ss);

private:
	FigureFactory();

};

