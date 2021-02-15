#pragma once
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "ICollidable.h"
#include "Constants.h"
#include "ISerializable.h"
#include <algorithm>
#include <list>
#include <sstream>
#include <iostream>
#define PI 3.14159265


struct Point
{

	float x, y;

	Point(float xx, float yy);

	Point();

	Point(float xx);

	Point Normalized();

	void Invert();
	float GetLengh();

	inline Point operator+(Point a) {
		return Point(a.x + x, a.y + y);
	}

	inline Point operator-(Point a) {
		return Point(x - a.x, y - a.y);
	}

	inline Point operator/(float a) {
		return Point(x / a, y / a);
	}

	inline void operator+=(Point a) {

		x += a.x;
		y += a.y;

	}

	inline void operator-=(Point a) {

		x -= a.x;
		y -= a.y;

	}

	inline Point operator*(Point a) {

		return Point(x * a.x, y * a.y);

	}


	float Dot(Point a)
	{

		return x * a.x + y * a.y;

	}
};

struct RgbColor
{
	int r, g, b;

	RgbColor(int rr, int gg, int bb);

	RgbColor();

	void RandomColor();
};


enum FigureType
{
	tSquare,
	tCircle,
	tSquareWithCircle,
	tSizeableSquare,
	tSizeableCircle,
	tMoveableTriangle
};


class Figure : public ICollidable, public ISerializable
{
public:

	float mass = 0;

	Point pos, side, speed, p1, p2;
	RgbColor color;

	int time_step = 0;

	Figure(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass);

	virtual void Draw() = 0;

	virtual void Move();

	virtual std::string ToString();

	Figure();

	virtual ~Figure();
	
	virtual void CollisionEnter(Figure* f, bool b);

	virtual void Init(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color);

	virtual FigureType GetType() = 0;


};
