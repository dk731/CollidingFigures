#pragma once
#include "Circle.h"
#include "Square.h"


class SquareWithCircle : public Square
{


public:
	Circle myCircle;
	virtual void Move();

	virtual void Draw();

	virtual ~SquareWithCircle();

	void InitCircle(Point size, Point pos, Point p1, Point p2, Point speed, int time_step, RgbColor color);


	virtual std::string ToString();

	virtual FigureType GetType();

private:
	friend class FigureFactory;
	SquareWithCircle(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass);


	


};

