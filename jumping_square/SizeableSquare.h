#pragma once

#include "SizeableFigure.h"
#include "Square.h"
#include <algorithm>

class SizeableSquare : public SizeableFigure, public Square
{

public:
	virtual std::string ToString();

	virtual FigureType GetType();

protected:
	SizeableSquare(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, int step_time);
	friend class FigureFactory;

};

