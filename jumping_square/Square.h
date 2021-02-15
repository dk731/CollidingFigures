#pragma once
#include "Figure.h"
class Square : virtual public Figure
{

public:

	virtual void Draw();

	virtual ~Square();

	virtual float* GetCenter();
	virtual float GetRadius();
	
	virtual std::string ToString();

	virtual FigureType GetType();


protected:
	friend class FigureFactory;
	Square(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, float mass);


};

