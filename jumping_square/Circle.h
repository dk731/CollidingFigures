#pragma once
#include "Figure.h"
class Circle : virtual public Figure
{

public:
	virtual void Draw();
	virtual ~Circle();

	virtual float* GetCenter();
	virtual float GetRadius();

	Circle();

	virtual std::string ToString();

	virtual FigureType GetType();

protected:
	friend class FigureFactory;
	Circle(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass);

};

