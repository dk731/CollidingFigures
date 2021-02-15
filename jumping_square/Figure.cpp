#include "Figure.h"



Point::Point(float xx, float yy) :
	x(xx),
	y(yy)
{

}

Point::Point() :
	x(0),
	y(0)
{

}

Point::Point(float xx) :
	x(xx),
	y(xx)
{

}

Point Point::Normalized()
{
	float len = GetLengh();

	return Point(x / len, y / len);
}

void Point::Invert()
{
	x = -x;
	y = -y;
}

float Point::GetLengh()
{
	return sqrt(x * x + y * y);
}



RgbColor::RgbColor(int rr, int gg, int bb) :
		r(rr),
		g(gg),
		b(bb)
{

}
RgbColor::RgbColor() :
		r(0),
		g(0),
		b(0)
{

}

void RgbColor::RandomColor()
{

	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

}




void Figure::Move()
{
	pos.x += speed.x * time_step / 1000.0f;
	pos.y += speed.y * time_step / 1000.0f;
	bool tmp = false;

	if (pos.x <= p1.x || pos.x + side.x >= p2.x)
	{
		if (pos.x <= p1.x)
		{
			pos.x = p1.x;
		}
		if (pos.x + side.x >= p2.x)
		{
			pos.x = p2.x - side.x;
		}
		speed.x = -speed.x;
	}
	if (pos.y <= p1.y || pos.y + side.y >= p2.y)
	{
		if (pos.y <= p1.y)
		{
			pos.y = p1.y;
		}
		if (pos.y + side.y >= p2.y)
		{
			pos.y = p2.y - side.y;
		}	
		speed.y = -speed.y;
	}
}

std::string Figure::ToString()
{

	std::ostringstream os;

	os	<< "pos=" << pos.x << "," << pos.y << ";"
		<< "side=" << side.x << "," << side.y << ";"
		<< "mass=" << mass << ";"
		<< "speed=" << speed.x << "," << speed.y << ";"
		<< "p1=" << p1.x << "," << p1.y << ";"
		<< "p2=" << p2.x << "," << p2.y << ";"
		<< "color=" << color.r << "," << color.g << "," << color.b << ";"
		<< "time_step=" << time_step << ";?";

	return os.str();

}

Figure::Figure(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass) :
	pos(pos.x, pos.y),
	side(size.x, size.y),
	time_step(time),
	p1(s1.x, s1.y),
	p2(s2.x, s2.y),
	speed(speed.x, speed.y),
	color(color.r, color.g, color.b),
	mass(mass)
{
	

}

Figure::~Figure()
{

}

void Figure::CollisionEnter(Figure* f, bool b)
{

}



void Figure::Init(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color)
{
	p1.x = s1.x;
	p1.y = s1.y;
	p2.x = s2.x;
	p2.y = s2.y;
	Figure::pos = pos;
	side = size;
	Figure::speed = speed;
	time_step = time;
	Figure::color = color;
}



Figure::Figure()
{

}
