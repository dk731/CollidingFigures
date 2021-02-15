#include "SizeableFigure.h"

SizeableFigure::SizeableFigure(Point s1, Point s2, Point pos, Point size, Point speed, int time, RgbColor color, int step_time) :
	Figure(s1, s2, pos, size, speed, time, color, 1000000),
	step_time(step_time),
	curently_in_step(false),
	bol(false),
	cur_step_time(0),
	size_icc(0)
{
	start_side = side;
}

void SizeableFigure::InitSizeable(Point step_destination, Point decc, Point start_side, float size_icc, int step_time, int cur_step_time, bool curently_in_step, bool bol)
{

	this->step_destination.x = step_destination.x;
	this->step_destination.y = step_destination.y;

	this->decc.x = decc.x;
	this->decc.y = decc.y;

	this->start_side.x = start_side.x;
	this->start_side.y = start_side.y;

	this->size_icc = size_icc;

	this->step_time = step_time;

	this->cur_step_time = cur_step_time;

	this->curently_in_step = curently_in_step;

	this->bol = bol;

}

void SizeableFigure::Move()
{

	if (!curently_in_step)
	{
		InitStep();
		bol = true;
	}

	if (cur_step_time < step_time / 2.0f)
	{
		pos.x -= size_icc / 2.0f;
		pos.y -= size_icc / 2.0f;
		side.x += size_icc;
		side.y += size_icc;

	}
	else if (cur_step_time < step_time)
	{
		if (bol)
		{
			decc = step_destination - pos;
			decc.x = decc.x / (step_time / 2.0f) * time_step;
			decc.y = decc.y / (step_time / 2.0f) * time_step;

			bol = false;
		}
		pos.x += decc.x;
		pos.y += decc.y;
		side.x -= size_icc;
		side.y -= size_icc;

	}
	else
	{
		curently_in_step = false;
		pos = step_destination;
	}

	if (pos.x + side.x > p2.x)
	{
		pos.x = p2.x - side.x;
	}
	else if (pos.x < p1.x)
	{
		pos.x = p1.x;
	}

	if (pos.y + side.y > p2.y)
	{
		pos.y = p2.y - side.y;
	}
	else if (pos.y < p1.y)
	{
		pos.y = p1.y;
	}

	cur_step_time += time_step;
}

std::string SizeableFigure::ToString()
{
	std::ostringstream os;


	os << Figure::ToString()
		<< "step_time=" << step_time << ";"
		<< "curently_in_step=" << curently_in_step << ";"
		<< "bol=" << bol << ";"
		<< "step_destination=" << step_destination.x << "," << step_destination.y << ";"
		<< "decc=" << decc.x << "," << decc.y << ";"
		<< "start_side=" << start_side.x << "," << start_side.y << ";"
		<< "cur_step_time=" << cur_step_time << ";"
		<< "size_icc=" << size_icc << ";?";


	return os.str();

}

void SizeableFigure::CollisionEnter(Figure *f, bool b)
{

	float* f1 = GetCenter(), * f2 = f->GetCenter();
	float r1 = GetRadius(), r2 = f->GetRadius();

	Point a(f1[0] - f2[0], f1[1] - f2[1]);

	Point tmpOffset = (Point(f1[0], f1[1]) - Point(f2[0], f2[1])).Normalized();

	tmpOffset.x = tmpOffset.x * (a.GetLengh() - r1 - r2) / 2.0f;
	tmpOffset.y = tmpOffset.y * (a.GetLengh() - r1 - r2) / 2.0f;

	if (b) { tmpOffset.Invert(); }

	pos += tmpOffset;
	step_destination += tmpOffset;

}


void SizeableFigure::InitStep()
{
	side.x = start_side.x;
	side.y = start_side.y;

	float step_range = speed.x;



	float direction = rand() % 1000 / 1000.0f * 2 * PI;
	Point offset = Point((float)cos(direction) * step_range, (float)sin(direction) * step_range);

	size_icc = ((std::max(ABS(offset.x), ABS(offset.y)) * 2) / (step_time / 2.0f)) * time_step;

	if (pos.x + side.x + std::max(ABS(offset.x), ABS(offset.y)) < p2.x && pos.x - std::max(ABS(offset.x), ABS(offset.y)) > p1.x)
	{
		offset.x = -offset.x;
	}
	if (pos.y + side.y + std::max(ABS(offset.x), ABS(offset.y)) < p2.y && pos.y - std::max(ABS(offset.x), ABS(offset.y)) > p1.y)
	{
		offset.y = -offset.y;
	}

	step_destination = pos + offset;

	size_icc = ((std::max(ABS(offset.x), ABS(offset.y)) * 2) / (step_time / 2.0f)) * time_step;

	cur_step_time = 0;
	curently_in_step = true;
}

float SizeableFigure::ABS(float a)
{
	if (a < 0)
	{
		return -a;
	}
	return a;
}
