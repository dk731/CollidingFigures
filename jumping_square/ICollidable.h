#pragma once
class Figure;

class ICollidable
{
public:

	virtual float* GetCenter() = 0;
	virtual float GetRadius() = 0;
	
	virtual void CollisionEnter(Figure *f, bool b) = 0;


};
