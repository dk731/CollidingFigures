#pragma once

#include "SizeableFigure.h"
#include "Circle.h"

class SizeableCircle : public SizeableFigure, public Circle
{

public :
	virtual std::string ToString();
	virtual FigureType GetType();
	

private:
	SizeableCircle(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, int step_time);
	friend class FigureFactory;



};

