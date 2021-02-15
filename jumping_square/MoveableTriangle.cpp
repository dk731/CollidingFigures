#include "MoveableTriangle.h"

MoveableTriangle& MoveableTriangle::getInstance()
{
	static MoveableTriangle instance; 
								 
	return instance;
}


void MoveableTriangle::Draw()
{


	color = RgbColor(255, 255, 255);
	if (imune > 0)
	{
		imune -= time_step;
		color = RgbColor(255, 0, 0);
	}
	al_draw_filled_circle(pos.x + side.x / 2.0f, pos.y + side.y * 2.0f / 3, 2 / 3.0f * side.y, al_premul_rgba(152, 195, 242, health / (float)startHp * 255));
	al_draw_filled_triangle(pos.x + side.x / 2, pos.y, pos.x + side.x, pos.y + side.y, pos.x, pos.y + side.y, al_map_rgb(color.r, color.g, color.b));

	

	
	score++;
}

float* MoveableTriangle::GetCenter()
{
	
	float* a = new float[2]{ pos.x + side.x / 2.0f, pos.y + GetRadius() };


	return a;
}

float MoveableTriangle::GetRadius()
{
	return ((side.x * 1.73205f) / 3.0f);
}
void MoveableTriangle::MoveBy(float dx, float dy)
{

	speed.x = dx;
	speed.y = dy;
	
	Move();

}
void MoveableTriangle::CollisionEnter(Figure *f, bool b)
{
	if (imune <= 0)
	{
		health--;
		imune = 500;
	}

	float* f1 = GetCenter(), * f2 = f->GetCenter();
	float r1 = GetRadius(), r2 = f->GetRadius();

	Point a(f1[0] - f2[0], f1[1] - f2[1]);

	Point tmpOffset = (Point(f1[0], f1[1]) - Point(f2[0], f2[1])).Normalized();

	tmpOffset.x = tmpOffset.x * (a.GetLengh() - r1 - r2) / 2.0f;
	tmpOffset.y = tmpOffset.y * (a.GetLengh() - r1 - r2) / 2.0f;

	if (b) { tmpOffset.Invert(); }
	pos += tmpOffset;

}
void MoveableTriangle::Init(Point s1, Point s2, Point pos, Point size, int time, int health, int imune, int score, int bestScore, int startHp)
{
	Figure::Init(s1, s2, pos, size, Point(1, 1), time, RgbColor(255, 255, 255));
	this->health = health;

	this->imune = imune;

	this->score = score;

	this->bestScore = bestScore;

	this->mass = 100000;

	this->bestScore = std::max(score, bestScore);

	this->startHp = startHp;

}

bool MoveableTriangle::IsAlive()
{
	return health > 0;
}

std::string MoveableTriangle::ToString()
{

	std::ostringstream os;


	os  << "class=MoveableTriangle;" << Figure::ToString() 
		<< "health=" << health << ";"
		<< "imune=" << imune << ";"
		<< "score=" << score << ";"
		<< "bestScore=" << bestScore << ";"
		<< "startHp=" << startHp << ";?";

	return os.str();

	return os.str();
}

FigureType MoveableTriangle::GetType()
{
	return tMoveableTriangle;
}

MoveableTriangle::MoveableTriangle() :
	bestScore(0),
	startHp(0)
{

}


