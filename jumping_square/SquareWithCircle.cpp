#include "SquareWithCircle.h"
#include "Square.h"



SquareWithCircle::SquareWithCircle(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass) :
	Figure(s1, s2, pos, size, speed, time, color, mass),
	Square(s1, s2, pos, size, speed, time, color, mass)
{
	
	RgbColor randomColor;
	randomColor.RandomColor();
	

	InitCircle(side / 2.5f, 
		Point(rand() % (int)(SquareWithCircle::side.x - myCircle.side.x) + SquareWithCircle::pos.x, 
			rand() % (int)(SquareWithCircle::side.y - myCircle.side.y) + SquareWithCircle::pos.y),
		SquareWithCircle::pos,
		SquareWithCircle::pos + SquareWithCircle::side,
		Point(speed.x + rand() % 20 + 30, speed.y + rand() % 20 + 30),
		time,
		randomColor);
}

void SquareWithCircle::Move()
{

	myCircle.p1 = pos + 1;
	myCircle.p2 = pos + side - 1;
	Square::Move();
	myCircle.Move();
}

void SquareWithCircle::Draw()
{
	Square::Draw();
	myCircle.Draw();	
}

SquareWithCircle::~SquareWithCircle()
{
}

void SquareWithCircle::InitCircle(Point size, Point pos, Point p1, Point p2, Point speed, int time_step, RgbColor color)
{
	myCircle.mass = 0;
	myCircle.side.x = size.x;
	myCircle.side.y = size.y;

	myCircle.color.r = color.r;
	myCircle.color.g = color.g;
	myCircle.color.b = color.b;

	myCircle.pos.x = pos.x;
	myCircle.pos.y = pos.y;

	myCircle.speed.x = speed.x;
	myCircle.speed.y = speed.y;


	myCircle.p1 = pos;
	myCircle.p2 = SquareWithCircle::pos + SquareWithCircle::side;
	myCircle.time_step = time_step;

}

std::string SquareWithCircle::ToString()
{
	
	std::ostringstream os;


	os << "class=SquareWithCircle;" << Figure::ToString() << ";"
		<< "myCircle=" << myCircle.ToString();


	return os.str();

}

FigureType SquareWithCircle::GetType()
{
	return tSquareWithCircle;
}




