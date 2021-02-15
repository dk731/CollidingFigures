#include "CollisionManager.h"
#include <iostream>


CollisionManager::CollisionManager()
{

}

CollisionManager& CollisionManager::getInstance()
{
	static CollisionManager    instance; // Guaranteed to be destroyed.
								  // Instantiated on first use.
	return instance;
}

void CollisionManager::Add(Figure &a)
{
	figureList.push_back(&a);
}

void CollisionManager::Reset()
{
	figureList.clear();
}

void CollisionManager::Update()
{

	for (auto& i : figureList) {
		for (auto& j : figureList) {
			if (i == j) { continue; }

			float *f1 = i->GetCenter(), *f2 = j->GetCenter();
			float r1 = i->GetRadius(), r2 = j->GetRadius();

			Point a(f1[0] - f2[0], f1[1] - f2[1]);
			if (a.GetLengh() < r1 + r2)
			{

				FigureType t1 = i->GetType(), t2 = j->GetType();

				Point c1(f1[0], f1[1]), c2(f2[0], f2[1]);


				Point vec1 = c1 - c2;

				Point tmpOffset = vec1.Normalized() * ((vec1.GetLengh() - r1 - r2)) ;

				i->pos -= tmpOffset;
				j->pos += tmpOffset;

				if (t1 == tSizeableCircle || t1 == tSizeableSquare)
				{
					dynamic_cast<SizeableFigure*>(i)->step_destination += tmpOffset;
				}

				if (t2 == tSizeableCircle || t2 == tSizeableSquare)
				{
					dynamic_cast<SizeableFigure*>(j)->step_destination += tmpOffset;
				}


				Point tgp1, tgp2, l;
				float sproj1, sproj2;

				sproj1 = vec1.Dot(i->speed) / vec1.GetLengh();
				sproj2 = vec1.Dot(j->speed) / vec1.GetLengh();

				tgp1 = i->speed - (vec1.Normalized() * sproj1);
				tgp2 = j->speed - (vec1.Normalized() * sproj2);


				float s1, s2;

				s1 = ((2 * j->mass * sproj2) + ( (i->mass - j->mass) * sproj1)) / (i->mass + j->mass);

				s2 = ((2 * i->mass * sproj1) + ( (j->mass - i->mass) * sproj2)) / (i->mass + j->mass);


				if (t1 < tSizeableSquare)
				{
					i->speed = ( vec1.Normalized() * s1) + tgp1;
				}

				if (t2 < tSizeableSquare)
				{
					j->speed = (vec1.Normalized() * s2) + tgp2;
				}


				j->CollisionEnter(i, true);
				i->CollisionEnter(j, false);
	
			}


			delete[] f1;
			delete[] f2;

			f1 = nullptr;
			f2 = nullptr;

		}
	}

}
CollisionManager::~CollisionManager()
{

	for (auto& j : figureList) {
		delete j;
	}
}
