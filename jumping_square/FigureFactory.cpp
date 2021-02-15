#include "FigureFactory.h"


Figure* FigureFactory::CreateRandomSquare()
{
    GenerateRandSpeed(100, 40 , 100, 40);
    //GenerateRandSpeed(100, 30, 1, 5);

    return new Square(p1, p2, Point(rand() % (int)(p2.x - p1.x - randSide), rand() % (int)(p2.y - p1.y - randSide)), Point(randSide, randSide), randSpeed, time_step, randomColor, randSide * randSide / 100);
    
}

Figure* FigureFactory::CreateRandomCircle()
{
    
    GenerateRandSpeed(130, 20, 70, 50);
    //GenerateRandSpeed(100, 30, 1, 5);

    return new Circle(p1, p2, Point(rand() % (int)(p2.x - p1.x - randSide), rand() % (int)(p2.y - p1.y - randSide)), Point(randSide, randSide), randSpeed, time_step, randomColor, (randSide / 2.0f * randSide / 2.0f) * PI / 100);
}

Figure* FigureFactory::CreateRandomSquareWithCircle()
{
    GenerateRandSpeed(50, 30, 60, 60);
    //GenerateRandSpeed(100, 30, 1, 5);
    return new SquareWithCircle(p1, p2, Point(rand() % (int)(p2.x - p1.x - randSide), rand() % (int)(p2.y - p1.y - randSide)), Point(randSide, randSide), randSpeed, time_step, randomColor, randSide * randSide / 100);
}

Figure* FigureFactory::CreateRandomSizableSquare()
{
    GenerateRandSpeed(20, 30, 40, 30);
    //GenerateRandSpeed(5, 5, 1, 5);

    return new SizeableSquare(p1, p2, Point(rand() % (int)(p2.x - p1.x - randSide), rand() % (int)(p2.y - p1.y - randSide)), Point(randSide, randSide), randSpeed, time_step, randomColor, rand() % 3000 + 1000);
}

Figure* FigureFactory::CreateRandomSizableCircle()
{
    GenerateRandSpeed(25, 20, 20, 30);
    //GenerateRandSpeed(5, 5, 1, 5);

    return new SizeableCircle(p1, p2, Point(rand() % (int)(p2.x - p1.x - randSide), rand() % (int)(p2.y - p1.y - randSide)), Point(randSide, randSide), randSpeed, time_step, randomColor, rand() % 3000 + 1000);
}



void FigureFactory::GenerateRandSpeed(int max_speed, int minSpeed , int size, int min_size)
{

    float rand_dir = (rand() % 100 / 100.0f) * 2 * PI;
    randSpeed.x = cos(rand_dir) * (rand() % max_speed + minSpeed);
    randSpeed.y = sin(rand_dir) * (rand() % max_speed + minSpeed);
    randSide = rand() % size + min_size;
    randomColor.RandomColor();
}


Point FigureFactory::ReadPoint(std::string s)
{
    Point tmpPoint;

    tmpPoint.x = std::stof(s.substr(0, s.find(",")));

    tmpPoint.y = std::stof(s.substr(s.find(",") + 1, s.find(";") - s.find(",") - 1));
    return tmpPoint;
}

RgbColor FigureFactory::ReadColor(std::string s)
{
    RgbColor color;

    color.r = std::stof(s.substr(0, s.find(",")));

    s = s.substr(s.find(",") + 1);

    color.g = std::stof(s.substr(0, s.find(",")));

    s = s.substr(s.find(",") + 1);

    color.b = std::stof(s.substr(0, s.find(";")));

    return color;
}





void FigureFactory::ReadFigure(std::string s)
{

    std::string tmp;

    tmp = s.substr(s.find("pos=") + 4);
    Point tmpPoint = ReadPoint(tmp);
    fA.pos.x = tmpPoint.x;
    fA.pos.y = tmpPoint.y;


    tmp = s.substr(s.find("speed=") + 6);
    tmpPoint = ReadPoint(tmp);
    fA.speed.x = tmpPoint.x;
    fA.speed.y = tmpPoint.y;


    tmp = s.substr(s.find("p1=") + 3);
    tmpPoint = ReadPoint(tmp);
    fA.p1.x = tmpPoint.x;
    fA.p1.y = tmpPoint.y;


    tmp = s.substr(s.find("p2=") + 3);
    tmpPoint = ReadPoint(tmp);
    fA.p2.x = tmpPoint.x;
    fA.p2.y = tmpPoint.y;


    tmp = s.substr(s.find("side=") + 5);
    tmpPoint = ReadPoint(tmp);
    fA.size.x = tmpPoint.x;
    fA.size.y = tmpPoint.y;


    tmp = s.substr(s.find("mass=") + 5);
    fA.mass = std::stof(tmp.substr(0, tmp.find(";")));


    tmp = s.substr(s.find("time_step=") + 10);
    fA.time_step = std::stoi(tmp.substr(0, tmp.find(";")));


    tmp = s.substr(s.find("color=") + 6);
    RgbColor tmpColor;
    tmpColor = ReadColor(tmp);
    fA.color.r = tmpColor.r;
    fA.color.g = tmpColor.g;
    fA.color.b = tmpColor.b;

}

void FigureFactory::ReadSizeableFigure(std::string s)
{

    std::string tmp;

    tmp = s.substr(s.find("step_destination=") + 17);
    Point tmpPoint = ReadPoint(tmp);
    sFa.step_destination.x = tmpPoint.x;
    sFa.step_destination.y = tmpPoint.y;


    tmp = s.substr(s.find("decc=") + 5);
    tmpPoint = ReadPoint(tmp);
    sFa.decc.x = tmpPoint.x;
    sFa.decc.y = tmpPoint.y;


    tmp = s.substr(s.find("start_side=") + 11);
    tmpPoint = ReadPoint(tmp);
    sFa.start_side.x = tmpPoint.x;
    sFa.start_side.y = tmpPoint.y;


    tmp = s.substr(s.find("curently_in_step=") + 17);
    sFa.curently_in_step = tmp[0] == '1';


    tmp = s.substr(s.find("bol=") + 4);
    sFa.bol = tmp[0] == '1';

    tmp = s.substr(s.find("step_time=") + 10);
    sFa.step_time = std::stoi(tmp.substr(0, tmp.find(";")));

    tmp = s.substr(s.find("cur_step_time=") + 14);
    sFa.cur_step_time = std::stoi(tmp.substr(0, tmp.find(";")));

    tmp = s.substr(s.find("size_icc=") + 9);
    sFa.size_icc = std::stof(tmp.substr(0, tmp.find(";")));

}

void FigureFactory::ReadMoveableTriangle(std::string s)
{

    std::string tmp;

    tmp = s.substr(s.find("health=") + 7);
    mTa.health = std::stoi(tmp.substr(0, tmp.find(";")));


    tmp = s.substr(s.find("imune=") + 6);
    mTa.imune = std::stoi(tmp.substr(0, tmp.find(";")));


    tmp = s.substr(s.find("score=") + 6);
    mTa.score = std::stoi(tmp.substr(0, tmp.find(";")));


    tmp = s.substr(s.find("bestScore=") + 10);
    mTa.bestScore = std::stoi(tmp.substr(0, tmp.find(";")));

    tmp = s.substr(s.find("startHp=") + 8);
    mTa.startHp = std::stoi(tmp.substr(0, tmp.find(";")));
}



void FigureFactory::Init(Point s1, Point s2, int fps)
{

    p1.x = s1.x;
    p1.y = s1.y;

    p2.x = s2.x;
    p2.y = s2.y;
    
    time_step = 1 / (float)fps * 1000;
    
}



Figure* FigureFactory::CreateFromString(std::string ss)
{

    std::string class_name = ss.substr(ss.find("class=") + 6, ss.find(";") - 6);


    if (class_name == "Square")
    {
        ReadFigure(ss);
        return new Square(fA.p1, fA.p2, fA.pos, fA.size, fA.speed, fA.time_step, fA.color, fA.mass);
    }
    else if (class_name == "Circle")
    {
        ReadFigure(ss);
        return new Circle(fA.p1, fA.p2, fA.pos, fA.size, fA.speed, fA.time_step, fA.color, fA.mass);
    }
    else if (class_name == "SquareWithCircle")
    {
        ReadFigure(ss.substr(0, ss.find("?") - 1));
        SquareWithCircle* tmp = new SquareWithCircle(fA.p1, fA.p2, fA.pos, fA.size, fA.speed, fA.time_step, fA.color, fA.mass);
        ReadFigure(ss.substr(ss.find("myCircle=class=Circle") + 21));
        tmp->InitCircle(fA.size, fA.pos, fA.p1, fA.p2, fA.speed, fA.time_step, fA.color);
        return tmp;
    }
    else if (class_name == "SizeableSquare")
    {
        ReadFigure(ss);
        ReadSizeableFigure(ss);

        SizeableSquare *tmp = new SizeableSquare(fA.p1, fA.p2, fA.pos, fA.size, fA.speed, fA.time_step, fA.color, sFa.step_time);

        tmp->InitSizeable(sFa.step_destination, sFa.decc, sFa.start_side, sFa.size_icc, sFa.step_time, sFa.cur_step_time, sFa.curently_in_step, sFa.bol);

        return tmp;
    }
    else if (class_name == "SizeableCircle")
    {
        ReadFigure(ss);
        ReadSizeableFigure(ss);

        SizeableSquare* tmp = new SizeableSquare(fA.p1, fA.p2, fA.pos, fA.size, fA.speed, fA.time_step, fA.color, sFa.step_time);

        tmp->InitSizeable(sFa.step_destination, sFa.decc, sFa.start_side, sFa.size_icc, sFa.step_time, sFa.cur_step_time, sFa.curently_in_step, sFa.bol);

        return tmp;
    }
    else if (class_name == "MoveableTriangle")
    {
        ReadFigure(ss);
        ReadMoveableTriangle(ss);

        MoveableTriangle::getInstance().Init(fA.p1, fA.p2, fA.pos, fA.size, fA.time_step, mTa.health, mTa.imune, mTa.score, mTa.bestScore, mTa.startHp);
        return &MoveableTriangle::getInstance();
    }

    throw "!";

    return nullptr;

}

FigureFactory::FigureFactory()
{
}
