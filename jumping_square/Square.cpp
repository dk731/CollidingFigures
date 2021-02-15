#include "Square.h"
#include <iostream>


Square::Square(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass):
	Figure(s1, s2, pos, size, speed, time, color, mass)
{

}


void Square::Draw()
{
	al_draw_rectangle(pos.x, pos.y, pos.x + side.x, pos.y + side.y, al_map_rgb(color.r, color.g, color.b), 1);
}

Square::~Square()
{
}

float* Square::GetCenter()
{
	float *a = new float[2]{pos.x + side.x / 2.0f, pos.y + side.y / 2.0f};

	return a;
}

float Square::GetRadius()
{
	return sqrt((side.x * side.x) + (side.y * side.y)) / 2.0f;
}

std::string Square::ToString()
{
	std::ostringstream os;

	os << "class=Square;" << Figure::ToString();

	return os.str();
}

FigureType Square::GetType()
{
	return tSquare;
}




