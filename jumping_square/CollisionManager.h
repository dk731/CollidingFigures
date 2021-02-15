#pragma once
#include "Figure.h"
#include "SizeableFigure.h"
#include "SizeableSquare.h"
#include <algorithm> 


class CollisionManager
{

public:
	std::list <Figure*> figureList;
	int size;

	static CollisionManager& getInstance();

	

	void Add(Figure &a);
	void Reset();

	virtual void Update();

	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;

	

private:
	CollisionManager();
	virtual ~CollisionManager();

};



