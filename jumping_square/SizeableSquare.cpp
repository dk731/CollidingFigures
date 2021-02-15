#include "SizeableSquare.h"


std::string SizeableSquare::ToString()
{
	std::ostringstream os;


	os << "class=SizeableSquare;" << SizeableFigure::ToString();


	return os.str();
}

FigureType SizeableSquare::GetType()
{
	return tSizeableSquare;
}

SizeableSquare::SizeableSquare(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, int step_time) :
	SizeableFigure(s1, s2, pos, size, speed, time, color, step_time),
	Square(s1, s2, pos, size, speed, time, color, 1000000),
	Figure(s1, s2, pos, size, speed, time, color, 1000000)
{

}







