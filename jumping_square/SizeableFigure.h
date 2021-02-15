#pragma once
#include "Figure.h"


class SizeableFigure : virtual public Figure
{

public:
	int step_time;
	bool curently_in_step, bol;
	Point step_destination, decc, start_side;
	int cur_step_time;
	float size_icc;

	SizeableFigure(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, int step_time);
	
	void InitSizeable(Point step_destination, Point decc, Point start_side, float size_icc, int step_time, int cur_step_time, bool curently_in_step, bool bol);

	virtual void Move();

	virtual std::string ToString();

	virtual void CollisionEnter(Figure* f, bool b);


private:
	void InitStep();

	float ABS(float a);

};

