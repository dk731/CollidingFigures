#include "Point.h"


Point::Point()
{
	x = 0; 
	y = 0;
}

Point::Point(float xx, float yy) :
	x(xx),
	y(yy)
{

}

Point::Point(float xx):
	x(xx),
	y(xx)
{

}