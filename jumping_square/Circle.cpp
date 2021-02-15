#include "Circle.h"

Circle::Circle(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass) :
	Figure(s1, s2, pos, size, speed, time, color, mass)
{

}

void Circle::Draw()
{
	al_draw_circle(pos.x + (side.x / 2), pos.y + (side.y / 2), side.x / 2, al_map_rgb(color.r, color.g, color.b), 1);
}

Circle::~Circle()
{

}

Circle::Circle()
{

}


float* Circle::GetCenter()
{
	float* a = new float[2]{ pos.x + side.x / 2.0f, pos.y + side.y / 2.0f };

	return a;
}

float Circle::GetRadius()
{
	return side.x / 2.0f;
}

std::string Circle::ToString()
{

	std::ostringstream os;

	os << "class=Circle;" << Figure::ToString();

	return os.str();
}

FigureType Circle::GetType()
{
	return tCircle;
}
