#pragma once
#include "Figure.h"

class MoveableTriangle : public Figure
{

public:

	int health = 5;
	int imune = 0; 
	int score = 0;
	int bestScore;
	int startHp;

	static MoveableTriangle& getInstance();

	virtual void Draw();
	virtual float* GetCenter();
	virtual float GetRadius();

	void MoveBy(float dx, float dy);

	virtual void CollisionEnter(Figure *f, bool b);

	MoveableTriangle(MoveableTriangle const&) = delete;
	void operator=(MoveableTriangle const&) = delete;

	virtual void Init(Point s1, Point s2, Point pos, Point size, int time, int health, int imune, int score, int bestScore, int startHp);

	bool IsAlive();

	virtual std::string ToString();

	virtual FigureType GetType();

private:
	
	MoveableTriangle();
	virtual ~MoveableTriangle() {};

};

