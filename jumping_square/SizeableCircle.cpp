#include "SizeableCircle.h"


std::string SizeableCircle::ToString()
{
	std::ostringstream os;

	os << "class=SizeableCircle;" << SizeableFigure::ToString();

	return os.str();
}

FigureType SizeableCircle::GetType()
{
	return tSizeableCircle;
}



SizeableCircle::SizeableCircle(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, int step_time) :
	SizeableFigure(s1, s2, pos, size, speed, time, color, step_time),
	Circle(s1, s2, pos, size, speed, time, color, 1000000),
	Figure(s1, s2, pos, size, speed, time, color, 1000000)
{

}
